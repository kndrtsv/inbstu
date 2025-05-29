#ifndef COURSEWORK_APPINTERFACE_H
#define COURSEWORK_APPINTERFACE_H

#include <vector>
#include <map>
#include "Transaction.h"
#include "Category.h"
#include "Report.h"
#include "Recommendation.h"

class FinanceApp {
public:
    void run();

private:
    std::vector<Transaction*> manualInput;

    void showMenu();
    void inputData();
    void viewCategories();
    void viewReport();
    void viewRecommendations();
    void viewAllHistory();
    void viewAndSetLimits();
    void cleanupManual();
};

#endif //COURSEWORK_APPINTERFACE_H