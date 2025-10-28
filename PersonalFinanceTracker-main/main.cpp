#include <iostream>            // I/O streams
#include <vector>              // std::vector
#include <string>              // std::string
#include <algorithm>           // std::transform
#include <cctype>              // ::tolower, isdigit
#include <limits>              // numeric limits 
#include <sstream>             // std::stringstream
#include "Transaction.h"       // Transaction class
#include "FinanceManager.h"    // FinanceManager class

// Helper to get a valid integer between min and max
int getValidInt(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number between " << min << " and " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Helper to get a valid double >= min
double getValidDouble(double min, const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number >= " << min << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Validate YYYY-MM-DD
bool isValidDate(const std::string& s) {
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
    for (int i : {0,1,2,3,5,6,8,9})
        if (!std::isdigit(s[i])) return false;

    int month = std::stoi(s.substr(5, 2));
    int day = std::stoi(s.substr(8, 2));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}


// Prompt until a valid date
std::string getValidDate(const std::string& prompt) {
    std::string date;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);
        if (isValidDate(date)) return date;
        std::cout << "Enter date as YYYY-MM-DD. MM must be between 1-12 and DD between 1-31.\n";
    }
}

// Validate YYYY-MM
bool isValidMonth(const std::string& s) {
    if (s.size() != 7 || s[4] != '-') return false;
    for (int i : {0,1,2,3,5,6})
        if (!std::isdigit(s[i])) return false;

    int monthNum = std::stoi(s.substr(5, 2));
    return monthNum >= 1 && monthNum <= 12;
}


// Prompt until a valid month
std::string getValidMonth(const std::string& prompt) {
    std::string month;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, month);
        if (isValidMonth(month)) return month;
        std::cout << "Enter month as YYYY-MM. MM must be between 1-12.\n";
    }
}

// Prompt until type is "income" or "expense"
std::string getValidType() {
    std::string type;
    while (true) {
        std::cout << "Enter transaction type (income/expense): ";
        std::getline(std::cin, type);
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "income" || type == "expense") return type;
        std::cout << "Type must be 'income' or 'expense'.\n";
    }
}

// Prompt user to choose a category from a list
std::string getValidCategory(const std::vector<std::string>& cats, const std::string& prompt) {
    int choice;
    while (true) {
        std::cout << prompt << "\n";
        for (size_t i = 0; i < cats.size(); ++i)
            std::cout << i + 1 << ". " << cats[i] << "\n";
        choice = getValidInt(1, (int)cats.size(), "Enter choice: ");
        return cats[choice - 1];
    }
}

int main() {
    std::vector<Transaction> transactions;    // in-memory list
    FinanceManager manager;                 // manager instance
    int choice;

    // Predefined categories
    const std::vector<std::string> expenseCategories = {
        "Bills","Charity","Eating Out","Entertainment","Expenses","Family",
        "Finances","General","Gifts","Groceries","Holidays","Personal Care",
        "Savings","Shopping","Transfers","Transport"
    };
    const std::vector<std::string> incomeCategories = {
        "Salary","Freelance","Investments","Gifts","Other"
    };

    do {
        // Main menu
        std::cout << "\n============================\n";
        std::cout << "  PERSONAL FINANCE TRACKER\n";
        std::cout << "============================\n";
        std::cout << "1. Add Transaction\n";
        std::cout << "2. View All Transactions (this session)\n";
        std::cout << "3. View Saved Transactions (from file)\n";
        std::cout << "4. Set Monthly Budget\n";
        std::cout << "5. Filter Transactions by Category\n";
        std::cout << "6. Filter Transactions by Date\n";
        std::cout << "7. Filter Transactions by Amount\n";
        std::cout << "8. Generate Monthly Report\n";
        std::cout << "9. Show Monthly Expense Bar Chart\n";
        std::cout << "10. Exit\n";

        choice = getValidInt(1, 10, "Enter your choice: ");

        if (choice == 1) {
            // Add and save
            std::string type = getValidType();
            double amount = getValidDouble(0.0, "Enter amount: ");
            std::string category = getValidCategory(
                type == "expense" ? expenseCategories : incomeCategories,
                "Select a " + type + " category:"
            );
            std::string date = getValidDate("Enter date (YYYY-MM-DD): ");

            Transaction t(type, amount, category, date);
            transactions.push_back(t);
            manager.saveTransactionToFile(t);
            std::cout << "Transaction added.\n";
            
            // Check budget
            if (type == "expense") {
                std::string month = date.substr(0, 7);
                double total = manager.getMonthlyExpenseTotal(month);
                double budget = manager.getMonthlyBudget(month);
                if (budget > 0 && total > budget) {
                    std::cout << "Budget of $" << budget
                              << " exceeded for " << month << ".\n";
                }
            }
            // Display session transactions
        } else if (choice == 2) {
            if (transactions.empty()) {
                std::cout << "No transactions recorded.\n";
            } else {
                std::cout << "\nTransactions (this session):\n";
                for (auto& t : transactions) t.display();
            }

        } else if (choice == 3) {
            manager.loadTransactionsFromFile();  // Load from disk

        } else if (choice == 4) {
            // Set monthly budget
            std::string month = getValidMonth("Enter month for budget (YYYY-MM): ");
            double budget = getValidDouble(0.0, "Enter budget amount: ");
            manager.setMonthlyBudget(month, budget);

        } else if (choice == 5) {
            // Filter by category
            std::string cat = getValidCategory(expenseCategories, "Select a category to filter:");
            manager.filterTransactionsByCategory(cat);

        } else if (choice == 6) {
            // Filter by date
            std::string date = getValidDate("Enter date (YYYY-MM-DD): ");
            manager.filterTransactionsByDate(date);

        } else if (choice == 7) {
            // Filter by amount
            double amt = getValidDouble(0.0, "Enter amount to filter by: ");
            int ft = getValidInt(1, 2,
                "1. >= amount\n2. <= amount\nEnter choice: ");
            manager.filterTransactionsByAmount(amt, ft == 1);

        } else if (choice == 8) {
            // Monthly report
            std::string month = getValidMonth("Enter month for report (YYYY-MM): ");
            manager.generateMonthlyReport(month);

        } else if (choice == 9) {
            // Expense chart
            std::string month = getValidMonth("Enter month for chart (YYYY-MM): ");
            manager.showExpenseBarChart(month);

        }
    } while (choice != 10);

    return 0;   // Exit
}
