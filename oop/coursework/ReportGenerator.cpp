#include "ReportGenerator.h"

void ReportGenerator::generate(const std::vector<Transaction*>& data) {
    calculate(data);
    print();
}

Report ReportGenerator::getReport() const {
    return report;
}