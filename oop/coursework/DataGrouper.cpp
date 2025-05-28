#include "DataGrouper.h"

DataGrouper::DataGrouper(std::unique_ptr<GroupingStrategy> strategy)
        : strategy(std::move(strategy)) {}

void DataGrouper::setStrategy(std::unique_ptr<GroupingStrategy> strategy) {
    strategy = std::move(strategy);
}

std::vector<Category> DataGrouper::group(const std::vector<Transaction*>& data) {
    return strategy->group(data);
}
