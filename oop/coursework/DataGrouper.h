#ifndef COURSEWORK_DATAGROUPER_H
#define COURSEWORK_DATAGROUPER_H

#include <memory>
#include <vector>
#include "GroupingStrategy.h"
#include "Category.h"
#include "Transaction.h"

class DataGrouper {
private:
    std::unique_ptr<GroupingStrategy> strategy;
public:
    explicit DataGrouper(std::unique_ptr<GroupingStrategy> strategy);
    void setStrategy(std::unique_ptr<GroupingStrategy> strategy);
    std::vector<Category> group(const std::vector<Transaction*>& data);
};

#endif //COURSEWORK_DATAGROUPER_H