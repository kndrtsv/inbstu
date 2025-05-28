#ifndef COURSEWORK_TRANSACTION_FACTORY_H
#define COURSEWORK_TRANSACTION_FACTORY_H

#include <string>
#include "transaction.h"

class TransactionFactory {
public:
    static Transaction* create(double amount, const std::string& date, const std::string& description, const std::string& category, Transaction::Type type) {
        if (type == Transaction::INCOME)
            return new Income(amount, date, description, category);
        else
            return new Expense(amount, date, description, category);
    }
};
#endif //COURSEWORK_TRANSACTION_FACTORY_H