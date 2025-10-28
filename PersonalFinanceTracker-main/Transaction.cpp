#include "Transaction.h"
#include <iostream>

// Constructor implementation: sets up a transaction using an initialization list.
Transaction::Transaction(std::string type, double amount, std::string category, std::string date)
    : type(type), amount(amount), category(category), date(date) {}

// Getter for transaction type.
std::string Transaction::getType() const {
    return type;
}

// Getter for transaction amount.
double Transaction::getAmount() const {
    return amount;
}

// Getter for transaction category.
std::string Transaction::getCategory() const {
    return category;
}

// Getter for transaction date.
std::string Transaction::getDate() const {
    return date;
}

// Display method: Prints the transaction details to the console.
void Transaction::display() const {
    std::cout << date << " | " << type << " | " << category << " | $" << amount << std::endl;
}
