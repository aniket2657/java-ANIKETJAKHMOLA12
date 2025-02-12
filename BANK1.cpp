#include <iostream>
#include <vector>
#include <stdexcept> // For exception handling
using namespace std;

class InsufficientBalance : public exception {
public:
    const char* what() const noexcept override {
        return "Insufficient balance for the transaction.";
    }
};

class Bank {
private:
    int accNo;
    int balance;
    string userId;
    string pass;
public:
    Bank(string userId, string pass, int accNo, int balance) {
        this->userId = userId;
        this->pass = pass;
        this->accNo = accNo;
        this->balance = balance;
    }
    
    void getDetails() {
        cout << "User ID = " << userId << endl;
        cout << "Account No = " << accNo << endl;
        cout << "Balance = " << balance << endl;
    }
    
    string getUserId() { return userId; }
    string getPass() { return pass; }
    int getBalance() { return balance; }
    int getAccountNumber() { return accNo; }

    void depositMoney(int amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        cout << amount << " deposited successfully!\n";
    }

    void withdrawMoney(int amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }
        if (balance < amount) {
            throw InsufficientBalance();
        }
        balance -= amount;
        cout << amount << " withdrawn successfully!\n";
    }

    void transferMoney(Bank& receiver, int amount) {
        if (amount <= 0) {
            cout << "Invalid amount. Transaction failed.\n";
            return;
        }
        if (balance < amount) {
            throw InsufficientBalance();
        }
        balance -= amount;
        receiver.balance += amount;
        cout << amount << " transferred successfully to Account No: " << receiver.getAccountNumber() << endl;
    }
};

// Find account by account number
int findAccountByNumber(vector<Bank>& accounts, int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accNo) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Bank> accounts;
    int choice;

    while (true) {
        cout << "\nEnter 1 to create an account\n"
             << "Enter 2 to login\n"
             << "Enter 3 to exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int accNo, balance;
                string userId, pass, temp;
                cout << "Create your User ID: ";
                cin >> userId;
                cout << "Create your Password: ";
                cin >> pass;
                cout << "Confirm Password: ";
                cin >> temp;

                while (temp != pass) {
                    cout << "Passwords do not match. Try again.\n";
                    cout << "Create your Password: ";
                    cin >> pass;
                    cout << "Confirm Password: ";
                    cin >> temp;
                }
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Initial Balance: ";
                cin >> balance;

                accounts.push_back(Bank(userId, pass, accNo, balance));
                cout << "Account created successfully!\n";
                break;
            }
            case 2: {
                string id, pass;
                cout << "Enter User ID: ";
                cin >> id;
                cout << "Enter Password: ";
                cin >> pass;

                int idx = -1;
                for (int i = 0; i < accounts.size(); i++) {
                    if (accounts[i].getUserId() == id && accounts[i].getPass() == pass) {
                        idx = i;
                        break;
                    }
                }

                if (idx == -1) {
                    cout << "No account found.\n";
                } else {
                    cout << "Login successful!\n";

                    int action;
                    while (true) {
                        cout << "\nEnter 1 to show balance\n"
                             << "Enter 2 to deposit money\n"
                             << "Enter 3 to withdraw money\n"
                             << "Enter 4 to transfer money\n"
                             << "Enter 5 to exit\n"
                             << "Enter your choice: ";
                        cin >> action;

                        switch (action) {
                            case 1:
                                cout << "Your balance: " << accounts[idx].getBalance() << endl;
                                break;
                            case 2: {
                                int amount;
                                cout << "Enter deposit amount: ";
                                cin >> amount;
                                accounts[idx].depositMoney(amount);
                                break;
                            }
                            case 3: {
                                int amount;
                                cout << "Enter withdrawal amount: ";
                                cin >> amount;
                                try {
                                    accounts[idx].withdrawMoney(amount);
                                } catch (const InsufficientBalance& e) {
                                    cout << e.what() << endl;
                                }
                                break;
                            }
                            case 4: {
                                int accNo, amount;
                                cout << "Enter recipient's account number: ";
                                cin >> accNo;
                                int recipientIdx = findAccountByNumber(accounts, accNo);

                                if (recipientIdx == -1) {
                                    cout << "Recipient account not found!\n";
                                } else {
                                    cout << "Enter amount to transfer: ";
                                    cin >> amount;
                                    try {
                                        accounts[idx].transferMoney(accounts[recipientIdx], amount);
                                    } catch (const InsufficientBalance& e) {
                                        cout << e.what() << endl;
                                    }
                                }
                                break;
                            }
                            case 5:
                                cout << "Logging out...\n";
                                goto end_login;
                            default:
                                cout << "Invalid choice. Try again.\n";
                        }
                    }
                    end_login:;
                }
                break;
            }
            case 3:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
