#ifndef COURSEWORK_TRANSACTIONHISTORYVIEWER_H
#define COURSEWORK_TRANSACTIONHISTORYVIEWER_H

#include <string>

class TransactionHistoryViewer {
public:
    void showHistoryAll();

    void showHistoryByCategory(const std::string& category);
};

#endif //COURSEWORK_TRANSACTIONHISTORYVIEWER_H