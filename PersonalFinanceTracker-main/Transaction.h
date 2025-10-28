#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// Transaction class: Represents a single financial transaction (income or expense)
class Transaction {
public:
    // Constructor: Initializes a transaction with a type, amount, category, and date.
    Transaction(std::string type, double amount, std::string category, std::string date);

    // Getter functions to return private data members.
    std::string getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;

    // Display function: Outputs the transaction details in a user-friendly way.
    void display() const;

private:
    std::string type;      // "income" or "expense"
    double amount;         // Transaction amount (should be positive ideally)
    std::string category;  // Transaction category (e.g., "Food", "Rent")
    std::string date;      // Transaction date in YYYY-MM-DD format
};

#endif
