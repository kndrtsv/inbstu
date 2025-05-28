#include "Category.h"

Category::Category(const std::string& name, double limit)
        : name(name), limit(limit) {}

Category::Category() : name(""), limit(0.0) {}

void Category::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}