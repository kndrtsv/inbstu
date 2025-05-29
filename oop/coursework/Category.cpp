#include "Category.h"
#include <iostream>

Category::Category(const std::string& name, double limit)
        : name(name), limit(limit) {}

Category::Category()
        : name(""), limit(0.0) {}

void Category::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}

std::map<std::string, Category> loadLimitFromDB() {
    std::map<std::string, Category> limits;
    sqlite3* db = nullptr;
    int rc = sqlite3_open("finance.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return limits;
    }

    const char* sql = "SELECT name, c_limit FROM category_limits;";
    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return limits;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* nameText = sqlite3_column_text(stmt, 0);
        std::string name = nameText ? reinterpret_cast<const char*>(nameText) : "";
        double limitValue = sqlite3_column_double(stmt, 1);
        limits[name] = Category(name, limitValue);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return limits;
}

bool saveLimitToDB(const std::string& categoryName, double limitValue) {
    sqlite3* db = nullptr;
    int rc = sqlite3_open("finance.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    const char* sql = "INSERT OR REPLACE INTO category_limits (name, c_limit) VALUES (?, ?);";
    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, categoryName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, limitValue);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}