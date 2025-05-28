#ifndef COURSEWORK_CATEGORYREPORTGENERATOR_H
#define COURSEWORK_CATEGORYREPORTGENERATOR_H

#include "ReportGenerator.h"

class CategoryReportGenerator : public ReportGenerator {
protected:
    void calculate(const std::vector<Transaction*>& data) override;
    void print() override;
};


#endif //COURSEWORK_CATEGORYREPORTGENERATOR_H
