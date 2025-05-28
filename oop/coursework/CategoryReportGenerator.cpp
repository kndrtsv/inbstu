#include "CategoryReportGenerator.h"
#include <iostream>

void CategoryReportGenerator::calculate(const std::vector<Transaction*>& data) {
    for (auto* transaction : data) {
        double amount = transaction->getAmount();
        if (transaction->getType() == Transaction::INCOME)
            report.totals[transaction->getCategory()] += amount;
        else
            report.totals[transaction->getCategory()] -= amount;
    }
}

void CategoryReportGenerator::print() {
    std::cout << "\nReport by categories:\n";
    for (auto& pair : report.totals) {
        std::cout << "  " << pair.first << ": " << pair.second << "\n";
    }
}