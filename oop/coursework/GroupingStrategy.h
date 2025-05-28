#ifndef COURSEWORK_GROUPINGSTRATEGY_H
#define COURSEWORK_GROUPINGSTRATEGY_H

#include <vector>
#include "Category.h"
#include "Transaction.h"

class GroupingStrategy {
public:
    virtual ~GroupingStrategy() = default;
    virtual std::vector<Category> group(const std::vector<Transaction*>& data) = 0;
};

#endif //COURSEWORK_GROUPINGSTRATEGY_H