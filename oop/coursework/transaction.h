#ifndef UNTITLED_TRANSACTION_H
#define UNTITLED_TRANSACTION_H

#include <string>

class Transaction {
public:
    enum Type { INCOME, EXPENSE };
protected:
    double amount;
    std::string date;
    std::string description;
    std::string category;
    Type type;
public:
    Transaction(double amount, const std::string& date, const std::string& description, const std::string& category, Type type)
            : amount(amount), date(date), description(description), category(category), type(type) {}

    virtual ~Transaction() = default;

    double getAmount() const {
        return amount;
    }

    std::string getCategory() const {
        return category;
    }

    Type getType() const {
        return type;
    }
};

class Income : public Transaction {
public:
    Income(double amount, const std::string& date, const std::string& description, const std::string& category)
            : Transaction(amount, date, description, category, Transaction::INCOME) {}
};

class Expense : public Transaction {
public:
    Expense(double amount, const std::string& date, const std::string& description, const std::string& category)
            : Transaction(amount, date, description, category, Transaction::EXPENSE) {}
};

#endif //UNTITLED_TRANSACTION_H