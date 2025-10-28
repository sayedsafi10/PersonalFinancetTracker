#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H
#include "Transaction.h"
#include <string>

// Manages transactions, budgets, and reports
class FinanceManager {
public:
    void saveTransactionToFile(const Transaction& transaction);             // append transaction
    void loadTransactionsFromFile();                                        // read and display all
    void setMonthlyBudget(const std::string& month, double amount);         // Set budget for specific month (e.g. "2025-04")
    double getMonthlyBudget(const std::string& month);                      // Load budget for a specific month
    double getMonthlyExpenseTotal(const std::string& month);                // Sum of expenses for the given month
    void filterTransactionsByCategory(const std::string& selectedCategory); // list by category
    void filterTransactionsByDate(const std::string& date);                 // list by date
    void filterTransactionsByAmount(double amount, bool greaterThan);       // list by amount
    void generateMonthlyReport(const std::string& month);                   // summary
    void showExpenseBarChart(const std::string& month);                     // ASCII chart        

private:
    std::string budgetMonth = ""; // last set month
    double budgetAmount = 0.0;    // last set amount
};

#endif
