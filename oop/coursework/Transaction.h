#ifndef COURSEWORK_TRANSACTION_H
#define COURSEWORK_TRANSACTION_H

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
    Transaction(double amount, const std::string& date, const std::string& description, const std::string& category, Type type);

    virtual ~Transaction() = default;

    double getAmount() const;
    std::string getCategory() const;
    Type getType() const;
};

class Income : public Transaction {
public:
    Income(double amount, const std::string& date, const std::string& description, const std::string& category);
};

class Expense : public Transaction {
public:
    Expense(double amount, const std::string& date, const std::string& description, const std::string& category);
};

#endif //COURSEWORK_TRANSACTION_H