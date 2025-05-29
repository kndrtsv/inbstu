#ifndef COURSEWORK_CATEGORY_H
#define COURSEWORK_CATEGORY_H

#include <string>
#include <vector>
#include <map>
#include "Transaction.h"
#include "sqlite3.h"

class Category {
public:
    std::string name;
    std::vector<Transaction*> transactions;
    double limit;

    Category(const std::string& name, double limit);
    Category();

    void addTransaction(Transaction* transaction);
};

std::map<std::string, Category> loadLimitFromDB();
bool saveLimitToDB(const std::string& categoryName, double limitValue);

#endif //COURSEWORK_CATEGORY_H