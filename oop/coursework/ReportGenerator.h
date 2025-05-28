#ifndef COURSEWORK_REPORTGENERATOR_H
#define COURSEWORK_REPORTGENERATOR_H

#include "Report.h"
#include "Transaction.h"
#include <vector>

class ReportGenerator {
protected:
    Report report;
public:
    void generate(const std::vector<Transaction*>& data);
    Report getReport() const;
protected:
    virtual void calculate(const std::vector<Transaction*>& data) = 0;
    virtual void print() = 0;
};

#endif //COURSEWORK_REPORTGENERATOR_H