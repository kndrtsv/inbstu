#ifndef COURSEWORK_DATAIMPORTER_H
#define COURSEWORK_DATAIMPORTER_H

#include "Transaction.h"
#include <vector>

class DataImporter {
public:
    virtual ~DataImporter() = default;
    virtual std::vector<Transaction*> importData() = 0;
};

#endif //COURSEWORK_DATAIMPORTER_H