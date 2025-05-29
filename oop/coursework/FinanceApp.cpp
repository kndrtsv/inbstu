#include "FinanceApp.h"

#include "UserInputImporter.h"
#include "DatabaseImporter.h"
#include "DataGrouper.h"
#include "CategoryGroupingStrategy.h"
#include "CategoryReportGenerator.h"
#include "RecommendationEngine.h"
#include "TransactionHistoryViewer.h"
#include "Category.h"

#include <iostream>
#include <memory>
#include <string>
#include <limits>

void FinanceApp::run() {
    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                inputData();
                break;
            }
            case 2: {
                viewCategories();
                break;
            }
            case 3: {
                viewReport();
                break;
            }
            case 4: {
                viewRecommendations();
                break;
            }
            case 5: {
                viewAllHistory();
                break;
            }
            case 6: {
                viewAndSetLimits();
                break;
            }
            case 0: {
                running = false;
                cleanupManual();
                break;
            }
            default: {
                std::cout << "Invalid option, please try again\n";
            }
        }
    }
}

void FinanceApp::showMenu() {
    std::cout << "\n=== FinanceApp Menu ===\n";
    std::cout << "1. Input transactions\n";
    std::cout << "2. View transaction categories\n";
    std::cout << "3. View category report\n";
    std::cout << "4. View recommendations\n";
    std::cout << "5. View all transaction history\n";
    std::cout << "6. View & set category limits\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}


void FinanceApp::inputData() {
    cleanupManual();
    UserInputImporter importer;
    manualInput = importer.importData();
    std::cout << "Imported " << manualInput.size() << " transactions\n";
}

void FinanceApp::viewCategories() {
    DatabaseImporter dbImporter;
    auto transactions = dbImporter.importData();

    if (transactions.empty()) {
        std::cout << "No transactions in database\n";
        return;
    }

    DataGrouper grouper(std::make_unique<CategoryGroupingStrategy>());
    auto categories = grouper.group(transactions);

    std::cout << "\nTransaction Categories:\n";
    for (const auto& category : categories) {
        std::cout << "  " << category.name
                  << ": " << category.transactions.size()
                  << " transactions\n";
    }

    std::cout << "\nEnter a category name to view its transactions or press 0 to return: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);
    if (!name.empty()) {
        std::cout << "Selected category: " << name << std::endl;
        TransactionHistoryViewer viewer;
        viewer.showHistoryByCategory(name);
    }

    for (auto* transaction : transactions) {
        delete transaction;
    }
}


void FinanceApp::viewReport() {
    DatabaseImporter dbImporter;
    auto transactions = dbImporter.importData();

    if (transactions.empty()) {
        std::cout << "No transactions in database\n";
        return;
    }

    CategoryReportGenerator generator;
    generator.generate(transactions);

    for (auto* transaction : transactions) {
        delete transaction;
    }
}

void FinanceApp::viewRecommendations() {
    DatabaseImporter dbImporter;
    auto transactions = dbImporter.importData();

    if (transactions.empty()) {
        std::cout << "No transactions in database\n";
        return;
    }

    CategoryReportGenerator generator;
    generator.generate(transactions);
    Report report = generator.getReport();

    RecommendationEngine engine;
    auto recomendations = engine.analyze(report, loadLimitFromDB());

    std::cout << "\nRecommendations:\n";
    if (recomendations.empty()) {
        std::cout << "  No recommendations. Your finances look good\n";
    } else {
        for (const auto& recomendation : recomendations) {
            std::cout << "  - " << recomendation.message << "\n";
        }
    }

    for (auto* transaction : transactions) {
        delete transaction;
    }
}


void FinanceApp::viewAllHistory() {
    TransactionHistoryViewer viewer;
    viewer.showHistoryAll();
}

void FinanceApp::viewAndSetLimits() {
    std::map<std::string, Category> limits = loadLimitFromDB();

    std::cout << "\nCurrent category limits:\n";
    for (const auto& pair : limits) {
        std::cout << "  " << pair.first << " -> " << pair.second.limit << "\n";
    }

    std::cout << "\nDo you want to update a limit? (y/n): ";
    std::string response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (response == "y") {
        std::string name;
        double newLimit;

        std::cout << "Enter category name: ";
        std::getline(std::cin, name);

        std::cout << "Enter new limit for " << name << ": ";
        std::cin >> newLimit;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (saveLimitToDB(name, newLimit)) {
            std::cout << "Limit updated successfully!\n";
        } else {
            std::cerr << "Failed to update limit\n";
        }
    }
}


void FinanceApp::cleanupManual() {
    for (auto* transaction : manualInput) {
        delete transaction;
    }
    manualInput.clear();
}