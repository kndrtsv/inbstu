#ifndef COURSEWORK_USERINPUTIMPORTER_H
#define COURSEWORK_USERINPUTIMPORTER_H

#include "DataImporter.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

class UserInputImporter : public DataImporter {
public:
    std::vector<Transaction*> importData() override;
};

#endif //COURSEWORK_USERINPUTIMPORTER_H
