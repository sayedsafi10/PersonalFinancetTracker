# PersonalFinanceTracker
- Project folder structure and source files have been successfully set up.
- Implemented the core Transaction class, which stores and displays financial records (type, amount, category, and date).
- Verified correct object creation and output using sample data.
- Added functionality to accept user input for creating a transaction (type, amount, category, date).
- Encountered an issue when compiling only one file (forgot to include the class implementation), which was resolved by correctly compiling multiple source files together.
- Implemented user input for transactions. Initial version lacked amount validation (captured during testing).
- Added basic input validation for amount field to prevent negative values. Handled using simple if-statement and early return.
- Implemented a basic loop and menu system to allow users to add and view multiple transactions. Transactions are stored in a vector during runtime.
- Implemented a method in the FinanceManager class to save each transaction to a text file (data/transactions.txt) in CSV format.
- The file stores data in the format: date,type,category,amount to ensure easy parsing later.
- Transactions are written in append mode, allowing multiple entries to be stored without overwriting previous data.
- Integrated this feature into the main menu option for adding a transaction. After a user adds a transaction, it's both stored in memory and written to the file.
- Initially forgot to check if the file opened correctly before writing. This caused the program to silently fail if the file path was invalid or if the /data/ directory didn’t exist. Fixed the issue by adding an error check.
- Introduced a new menu option allowing users to view all transactions saved to file, even across sessions.
- Transactions are stored in data/transactions.txt in a CSV format (date,type,category,amount), and this option reads and displays them back to the user. Implemented this feature in the FinanceManager class to keep file operations modular and separate from main logic.
- Used std::ifstream to read the file line by line. Used std::stringstream to split each CSV line into fields, then created a Transaction object using the extracted data. Each reconstructed transaction is then displayed using the existing display() method from the Transaction class.
- Added an option to set a monthly budget, saved to budget.txt for persistence. When an expense is added, the program checks total spending and warns if the budget is exceeded. Includes error handling for missing files and invalid (negative) input.
- Reworked the budget system to support individual months (YYYY-MM) instead of a single global value. Budgets are now saved per month in budget.txt and matched against monthly expenses. Also fixed a bug where the app would crash if an invalid or empty amount was found in the saved transaction file. Added error handling and input validation to prevent crashes and improve stability.
- Replaced manual category input with predefined lists for income and expense, using numbered menus. It prevents typos and ensures consistent data for filtering/reporting. Basic input validation is included (e.g. invalid selection), but further error handling is still needed. The program does crash and behaves unexpectedly if incorrect inputs are entered in other areas. Working on fixing this.
- Added the ability to filter transactions by category using a menu-driven selection. Reads all saved transactions and displays only those matching the selected category. Uses the same predefined list of categories to maintain consistency.
- Implemented filtering features by both transaction date and amount. Users can view only transactions that match a specific date, or all above/below a specified amount, adding to the filtering options alongside category filtering.
- Added a report generation feature that summarizes total income, total expenses, and remaining balance for a given month. User selects a month (e.g., "2025-04") and the program reads all matching transactions to calculate totals. This feature helps users understand their financial activity over time.
- Implemented an ASCII bar chart to visualize monthly expenses by category. Originally used '█' to represent bars, but this caused encoding and compiler issues. Switched to using the | character for compatibility across terminals.
- Improved input validation across the application to prevent crashes from invalid or unexpected input. Inputs like transaction type, date format, numeric values, and menu selections are now fully validated. Exit option was moved to the bottom of the menu for better user experience.
- Enhanced input validation for transaction dates to reject incorrect or unrealistic values (e.g., months > 12, days > 31). Format must match YYYY-MM-DD, and numeric ranges are now checked properly. Prevents invalid or malformed dates from being stored in the transaction file.
- ## Notes

- This project was developed using Visual Studio Code (VS Code), not Microsoft Visual Studio.  
  Therefore, `.sln` and `.vcxproj` project files are not included. Compilation was done manually via terminal using `g++` for building the executable (`main.exe`). 

