#include "CategoryGroupingStrategy.h"
#include <map>
#include <string>

std::vector<Category> CategoryGroupingStrategy::group(const std::vector<Transaction*>& data) {
    std::map<std::string, Category> categoryMap;

    for (auto* transaction : data) {
        std::string categoryName = transaction->getCategory();

        if (categoryMap.find(categoryName) == categoryMap.end()) {
            categoryMap[categoryName] = Category(categoryName, 0.0);
        }

        categoryMap[categoryName].addTransaction(transaction);
    }

    std::vector<Category> result;
    for (const auto& kv : categoryMap) {
        result.push_back(kv.second);
    }

    return result;
}