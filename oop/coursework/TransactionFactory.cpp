#include "TransactionFactory.h"

Transaction* TransactionFactory::create(double amount, const std::string& date, const std::string& description, const std::string& category, Transaction::Type type) {
    if (type == Transaction::INCOME)
        return new Income(amount, date, description, category);
    else
        return new Expense(amount, date, description, category);
}