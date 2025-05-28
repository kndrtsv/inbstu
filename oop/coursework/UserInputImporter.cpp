#include "UserInputImporter.h"
#include <vector>
#include <iostream>
#include <string>
#include "sqlite3.h"

std::vector<Transaction*> UserInputImporter::importData() {
    int n;
    std::cout << "How many transactions would you like to add? ";
    std::cin >> n;

    sqlite3* db = nullptr;
    int rc = sqlite3_open("finance.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return std::vector<Transaction*>{};
    }

    const char* sqlInsert =
            "INSERT INTO transactions (amount, date, description, category, type) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return std::vector<Transaction*>{};
    }

    for (int i = 0; i < n; ++i) {
        double amount;
        std::string date, description, category;
        int type;

        std::cout << "\nTransaction " << i + 1 << ":\n";
        std::cout << "Enter amount: ";
        std::cin >> amount;

        std::cout << "Enter date (DD-MM-YYYY): ";
        std::cin >> date;

        std::cout << "Enter description: ";
        std::cin.ignore();
        std::getline(std::cin, description);

        std::cout << "Enter category: ";
        std::getline(std::cin, category);

        std::cout << "Type (0 - income, 1 - expense): ";
        std::cin >> type;

        sqlite3_bind_double(stmt, 1, amount);
        sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 5, type);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::vector<Transaction*>{};
}