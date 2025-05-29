#include "TransactionHistoryViewer.h"
#include "DatabaseImporter.h"
#include "Transaction.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

void printTransactions(const std::vector<Transaction*>& transactions) {
    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(10) << "Type"
              << std::setw(12) << "Category"
              << std::setw(10) << "Amount"
              << "Description\n";
    std::cout << "-------------------------------------------------\n";

    for (auto* transactions : transactions) {
        std::string type = transactions->getType() == Transaction::INCOME ? "Income" : "Expense";
        std::cout << std::left
                  << std::setw(12) << transactions->getDate()
                  << std::setw(10) << type
                  << std::setw(12) << transactions->getCategory()
                  << std::setw(10) << transactions->getAmount()
                  << transactions->getDescription()
                  << "\n";
    }
}

void TransactionHistoryViewer::showHistoryAll() {
    DatabaseImporter dbImporter;
    auto transactions = dbImporter.importData();

    if (transactions.empty()) {
        std::cout << "No transactions found in the database\n";
    } else {
        std::cout << "\n=== Full transaction history ===\n";
        printTransactions(transactions);
    }

    for (auto* transactions : transactions) {
        delete transactions;
    }
}

void TransactionHistoryViewer::showHistoryByCategory(const std::string& category) {
    DatabaseImporter dbImporter;
    auto transactions = dbImporter.importData();

    if (transactions.empty()) {
        std::cout << "No transactions found in the database\n";
        return;
    }

    std::vector<Transaction*> filtered;
    std::copy_if(transactions.begin(), transactions.end(),
                 std::back_inserter(filtered),
                 [&](Transaction* transactions) {
                     return transactions->getCategory() == category;
                 });

    if (filtered.empty()) {
        std::cout << "No transactions found in category \"" << category << "\".\n";
    } else {
        std::cout << "\n=== Transaction history for category: "
                  << category << " ===\n";
        printTransactions(filtered);
    }

    for (auto* transactions : transactions) {
        delete transactions;
    }
}