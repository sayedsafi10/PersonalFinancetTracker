#include "FinanceManager.h"
#include <fstream>    // file I/O
#include <iostream>   // console output
#include <sstream>    // parsing
#include <vector>
#include <map>

// Saves a transaction to "data/transactions.txt"
void FinanceManager::saveTransactionToFile(const Transaction& transaction) {
    std::ofstream outFile("data/transactions.txt", std::ios::app);
    if (!outFile) {
        std::cout << "Error: Could not open file to save transaction.\n";
        return;
    }

    outFile << transaction.getDate() << ","
            << transaction.getType() << ","
            << transaction.getCategory() << ","
            << transaction.getAmount() << "\n";

    outFile.close();
    std::cout << "Transaction saved to file.\n";
}

// Loads and displays all transactions from the file
void FinanceManager::loadTransactionsFromFile() {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    std::string line;
    std::cout << "\nSaved Transactions:\n";

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        double amount = std::stod(amountStr);
        Transaction t(type, amount, category, date);
        t.display();
    }

    inFile.close();
}

// Sets a monthly budget for a specific month (e.g., "2025-04")
void FinanceManager::setMonthlyBudget(const std::string& month, double amount) {
    std::ofstream outFile("data/budget.txt", std::ios::app); // append
    if (!outFile) {
        std::cout << "Error: Could not save budget.\n";
        return;
    }

    outFile << month << "," << amount << "\n";
    outFile.close();

    budgetMonth = month;
    budgetAmount = amount;

    std::cout << "Budget of $" << amount << " set for " << month << ".\n";
}

// Loads budget for a specific month
double FinanceManager::getMonthlyBudget(const std::string& month) {
    std::ifstream inFile("data/budget.txt");
    if (!inFile) return 0.0;

    std::string line, fileMonth;
    double amount;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, fileMonth, ',');
        ss >> amount;

        if (fileMonth == month) {
            inFile.close();
            return amount;
        }
    }

    inFile.close();
    return 0.0;
}

// Calculates total expenses for a specific month (e.g., "2025-04")
double FinanceManager::getMonthlyExpenseTotal(const std::string& month) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) return 0.0;

    std::string line;
    double totalExpense = 0.0;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        // Only try to process valid expense lines
        if (type == "expense" && date.substr(0, 7) == month) {
            try {
                if (!amountStr.empty()) {
                    double amount = std::stod(amountStr);
                    totalExpense += amount;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Skipping invalid transaction (bad amount): " << amountStr << "\n";
            }
        }
    }

    inFile.close();
    return totalExpense;
}

// Filters transactions by category.
void FinanceManager::filterTransactionsByCategory(const std::string& selectedCategory) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    std::string line;
    bool found = false;

    std::cout << "\nTransactions in category: " << selectedCategory << "\n";

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        if (category == selectedCategory) {
            double amount = std::stod(amountStr);
            Transaction t(type, amount, category, date);
            t.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found in this category.\n";
    }

    inFile.close();
}

// Filters transactions by a specific date.
void FinanceManager::filterTransactionsByDate(const std::string& date) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    std::string line;
    bool found = false;

    std::cout << "\nTransactions on: " << date << "\n";

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tDate, type, category, amountStr;

        std::getline(ss, tDate, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        if (tDate == date) {
            double amount = std::stod(amountStr);
            Transaction t(type, amount, category, tDate);
            t.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found for this date.\n";
    }

    inFile.close();
}

// Filters transactions by less than or greater than the amount input.
void FinanceManager::filterTransactionsByAmount(double amount, bool greaterThan) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    std::string line;
    bool found = false;

    std::cout << "\nTransactions with amount ";
    std::cout << (greaterThan ? "greater than or equal to " : "less than or equal to ") << "$" << amount << ":\n";

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        if (!amountStr.empty()) {
            double amt = std::stod(amountStr);
            bool matches = greaterThan ? amt >= amount : amt <= amount;

            if (matches) {
                Transaction t(type, amt, category, date);
                t.display();
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No transactions matched the amount filter.\n";
    }

    inFile.close();
}

// Generates a summary of the transactions for chosen month.
void FinanceManager::generateMonthlyReport(const std::string& month) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    std::string line;
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        if (date.substr(0, 7) == month && !amountStr.empty()) {
            double amount = std::stod(amountStr);

            if (type == "income") {
                totalIncome += amount;
            } else if (type == "expense") {
                totalExpenses += amount;
            }
        }
    }

    inFile.close();

    std::cout << "\nSummary for " << month << "\n";
    std::cout << "-----------------------------\n";
    std::cout << "Total Income:   $" << totalIncome << "\n";
    std::cout << "Total Expenses: $" << totalExpenses << "\n";
    std::cout << "Balance:        $" << (totalIncome - totalExpenses) << "\n";
}

// Generates a ASCII bar chart for a chosen month.
void FinanceManager::showExpenseBarChart(const std::string& month) {
    std::ifstream inFile("data/transactions.txt");
    if (!inFile) {
        std::cout << "Error: Could not open transactions file.\n";
        return;
    }

    // Predefined categories for consistency
    std::vector <std::string> categories = {
        "Bills", "Charity", "Eating Out", "Entertainment", "Expenses", "Family",
        "Finances", "General", "Gifts", "Groceries", "Holidays", "Personal Care",
        "Savings", "Shopping", "Transfers", "Transport"
    };

    std::map<std::string, double> totals;
    for (const std::string& cat : categories) {
        totals[cat] = 0.0;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date, type, category, amountStr;

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');

        if (date.substr(0, 7) == month && type == "expense" && !amountStr.empty()) {
            double amount = std::stod(amountStr);
            if (totals.find(category) != totals.end()) {
                totals[category] += amount;
            }
        }
    }

    inFile.close();

    std::cout << "\nExpense Breakdown for " << month << "\n";
    std::cout << "------------------------------------------\n";

    for (const auto& pair : totals) {
        if (pair.second > 0) {
            int barLength = static_cast<int>(pair.second / 10); 
            std::cout << pair.first;
            if (pair.first.length() < 15) std::cout << std::string(15 - pair.first.length(), ' ');
            std::cout << " | " << std::string(barLength, '|') << " $" << pair.second << "\n";

        }
    }
}
