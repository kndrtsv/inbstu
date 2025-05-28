#include "DatabaseImporter.h"
#include "TransactionFactory.h"
#include "sqlite3.h"
#include <iostream>

std::vector<Transaction*> DatabaseImporter::importData() {
    std::vector<Transaction*> transactions;

    sqlite3* db = nullptr;
    int rc = sqlite3_open("finance.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return transactions;
    }

    const char* sqlSelect =
            "SELECT amount, date, description, category, type FROM transactions;";

    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return transactions;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        double amount = sqlite3_column_double(stmt, 0);

        const unsigned char* dateText = sqlite3_column_text(stmt, 1);
        std::string date = dateText ? reinterpret_cast<const char*>(dateText) : "";

        const unsigned char* descriptionText = sqlite3_column_text(stmt, 2);
        std::string description = descriptionText ? reinterpret_cast<const char*>(descriptionText) : "";

        const unsigned char* categoryText = sqlite3_column_text(stmt, 3);
        std::string category = categoryText ? reinterpret_cast<const char*>(categoryText) : "";

        int typeInt = sqlite3_column_int(stmt, 4);

        Transaction* transaction = TransactionFactory::create(
                amount, date, description, category, static_cast<Transaction::Type>(typeInt)
        );
        transactions.push_back(transaction);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return transactions;
}