#ifndef COURSEWORK_DATABASEIMPORTER_H
#define COURSEWORK_DATABASEIMPORTER_H

#include "DataImporter.h"
#include "Transaction.h"
#include <vector>

class DatabaseImporter : public DataImporter {
public:
    std::vector<Transaction*> importData() override;
};

#endif //COURSEWORK_DATABASEIMPORTER_H