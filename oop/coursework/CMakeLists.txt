cmake_minimum_required(VERSION 3.27)
project(coursework)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(coursework
        main.cpp
        sqlite3.h
        sqlite3.c
        Transaction.h
        Transaction.cpp
        TransactionFactory.h
        TransactionFactory.cpp
        DatabaseImporter.cpp
        UserInputImporter.cpp
        GroupingStrategy.h
        CategoryGroupingStrategy.cpp
        Category.cpp
        Category.h
        DataGrouper.cpp
        ReportGenerator.cpp
        CategoryReportGenerator.cpp
        RecommendationEngine.cpp
        FinanceApp.cpp
        TransactionHistoryViewer.cpp
)