#ifndef COURSEWORK_TRANSACTIONFACTORY_H
#define COURSEWORK_TRANSACTIONFACTORY_H

#include <string>
#include "Transaction.h"

class TransactionFactory {
public:
    static Transaction* create(double amount, const std::string& date, const std::string& description, const std::string& category, Transaction::Type type);
};

#endif //COURSEWORK_TRANSACTIONFACTORY_H