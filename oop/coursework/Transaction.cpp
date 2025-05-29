#include "Transaction.h"

Transaction::Transaction(double amount, const std::string& date, const std::string& description, const std::string& category, Type type)
        : amount(amount), date(date), description(description), category(category), type(type) {}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getCategory() const {
    return category;
}

Transaction::Type Transaction::getType() const {
    return type;
}

const std::string& Transaction::getDate() const {
    return date;
}

const std::string& Transaction::getDescription() const {
    return description;
}

Income::Income(double amount, const std::string& date, const std::string& description, const std::string& category)
        : Transaction(amount, date, description, category, Transaction::INCOME) {}

Expense::Expense(double amount, const std::string& date, const std::string& description, const std::string& category)
        : Transaction(amount, date, description, category, Transaction::EXPENSE) {}
