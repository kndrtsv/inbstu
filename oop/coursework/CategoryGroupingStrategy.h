#ifndef COURSEWORK_CATEGORYGROUPINGSTRATEGY_H
#define COURSEWORK_CATEGORYGROUPINGSTRATEGY_H

#include "GroupingStrategy.h"

class CategoryGroupingStrategy : public GroupingStrategy {
public:
    std::vector<Category> group(const std::vector<Transaction*>& data) override;
};

#endif //COURSEWORK_CATEGORYGROUPINGSTRATEGY_H