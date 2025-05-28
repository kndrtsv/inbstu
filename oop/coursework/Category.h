#ifndef COURSEWORK_CATEGORY_H
#define COURSEWORK_CATEGORY_H

#include <string>
#include <vector>
#include "Transaction.h"

class Category {
public:
    std::string name;
    std::vector<Transaction*> transactions;
    double limit;

    Category(const std::string& name, double limit);
    Category();

    void addTransaction(Transaction* transaction);
};

#endif //COURSEWORK_CATEGORY_H