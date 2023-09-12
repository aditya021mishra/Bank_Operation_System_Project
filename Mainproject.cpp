#include  <bits/stdc++.h>
#include <regex>
using namespace  std;

class validation {
public:
    bool check_mobile(string mb)
    {
        if(mb.length()!=10) {
            return false;
        }
        return true;
    }
    bool check_Aadhar(string adh)
    {
        if(adh.length()!=12) {
            return false;
        }
        return true;
    }
    bool check_pan(const string &pan)
    {
      regex pattern("[A-Z]{5}[0-9]{4}[A-Z]{1}");
      return regex_match(pan, pattern);
    }
};

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName, pan, adhr, mbno;
    double balance;

public:
    BankAccount(int accountNumber, string accountHolderName, string pan, string adhr, string mbno, double balance)
        : accountNumber(accountNumber), accountHolderName(accountHolderName), pan(pan), adhr(adhr), mbno(mbno), balance(balance) {}

    virtual void displayAccount() {
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolderName << endl;
        cout << "Adhar Number : " << adhr << endl;
        cout << "Mobile Number : " << mbno << endl;
        cout << "Pan Card Number : " << pan << endl;
        cout << "Balance : Rs. " << balance << endl;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited Rs." << amount << " successfully." << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn Rs." << amount << " successfully." << endl;
        } else {
            cout << "Invalid withdrawal amount." << endl;
        }
    }

};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(int accountNumber, string accountHolderName, string pan, string adhr, string mbno, double balance)
        : BankAccount(accountNumber, accountHolderName, pan, adhr, mbno, balance) {}

    void displayAccount() override {
        cout << "---------Current Account Details---------" << endl;
        BankAccount::displayAccount();
        cout << endl;
    }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int accountNumber, string accountHolderName, string pan, string adhr, string mbno, double balance)
        : BankAccount(accountNumber, accountHolderName, pan, adhr, mbno, balance) {}


    void displayAccount() override {
        cout << "---------Savings Account Details---------" << endl;
        BankAccount::displayAccount();
        cout << endl;
    }
};

int main() {

    int index = 0;
    char acc_type;
    int choice;
    map<int,int> mp;
    vector<BankAccount*> accounts;
    validation v;

    while (true) {
        cout << "------------WELCOME TO BANKING OPERATION SYSTEM------------" << endl;
        cout << "1. Create an Account: " << endl;
        cout << "2. Fund Transfer: " << endl;
        cout << "3. Deposit: " << endl;
        cout << "4. Withdraw: " << endl;
        cout << "5. Display All Accounts: " << endl;
        cout << "6. Exit: " << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int accountNumber; 
                string accountHolderName, pan, mbno, adhr;
                double balance;
                cout << "\nEnter account holder name: ";
                cin.ignore();
                getline(cin, accountHolderName);
                cout << "\nEnter your Pan number: ";
                getline(cin, pan);
                if (v.check_pan(pan)) {
                    cout << "Valid Pan Card Number." << endl;
                } else {
                    while(1) {
                        cout << "---------Invalid Pan Card Number---------" << endl;
                        cout << "---------Try Again!---------" << endl;
                        cout << "Enter your Pan number: ";
                        getline(cin, pan);
                        if (v.check_pan(pan)) {
                          cout << "Valid Pan Card Number." << endl;
                          break;
                        }
                    }
                }
                cout << "\nEnter your Adhar number: ";
                getline(cin, adhr);
                if (v.check_Aadhar(adhr)) {
                    cout << "Valid Adhar Card Number." << endl;
                } else {
                    while(1) {
                        cout << "---------Invalid Adhar Card Number---------" << endl;
                        cout << "---------Try Again!---------" << endl;
                        cout << "Enter your Adhar number: ";
                        getline(cin, adhr);
                        if (v.check_Aadhar(adhr)) {
                          cout << "Valid Adhar Card Number." << endl;
                          break;
                        }
                    }
                }
                int cd;
                cout << "\nEnter your Mobile number: ";
                getline(cin, mbno);
                if (v.check_mobile(mbno)) {
                  cout << "Valid Mobile Number." << endl;
                  cout << "Enter 4 digit code sent to your mobile number : " ;
                  cin >> cd; 
                  cout << "---------Verification Successful!---------" << endl;
                } else {
                    while(1) {
                        cout << "---------Invalid Mobile Number---------" << endl;
                        cout << "---------Try Again!---------" << endl;
                        cout << "Enter your Mobile number: ";
                        getline(cin, mbno);
                        if (v.check_mobile(mbno)) {
                          cout << "Valid Mobile Number." << endl;
                          cout << "Enter 4 digit code sent to your mobile number : " ;
                          cin >> cd; 
                          cout << "---------Verification Successful!---------" << endl;
                          break;
                        }
                    }
                }
                cout << "\nChoose your account type : " << endl;
                cout << "Press C for Current Account & S for Savings Account : ";
                cin >> acc_type;
                cout << "\nEnter initial balance: Rs. ";
                cin >> balance;
                accountNumber = 10000 + (rand() % 90000);
                if (acc_type == 'C' || acc_type == 'c') {
                  accounts.push_back(new CurrentAccount(accountNumber, accountHolderName, pan, adhr, mbno, balance));
                  mp[accountNumber] = index++;
                }
                else if (acc_type == 'S' || acc_type == 's') {
                  accounts.push_back(new SavingsAccount(accountNumber, accountHolderName, pan, adhr, mbno, balance));
                  mp[accountNumber] = index++;
                }
                cout << "\n\n------------Your account has been created------------" << endl;
                cout << "Assigned account number is " << accountNumber << endl << endl;
                break;
            }
            case 2: {
                int accountNumber; 
                string accountHolderName;
                double amnt;
                cout << "\nEnter account holder name: ";
                cin.ignore();
                getline(cin, accountHolderName);
                cout << "Enter account number: ";
                cin >> accountNumber;
                if (mp.find(accountNumber) != mp.end()) {
                  cout << "Enter amount you wish to transfer: Rs. ";
                  cin >> amnt;
                  cout << "Choose account " << endl;
                  cout << "1. Current\n2. Savings" << endl;
                  cin >> acc_type;
                  if (amnt > 50000) { 
                    cout << "---------Sorry! Amount greater than 50000 can not be deposited---------" << endl<<endl;
                  } else {
                    accounts[mp[accountNumber]]->deposit(amnt);
                    cout << "------------Amount Transferred Successfully to " << accountHolderName << "------------" << endl<<endl;
                  }
                } else {
                    cout << "---------Invalid account number---------" << endl<<endl;
                }
                break;
            }
            case 3: {
                int accountNumber;
                double amount;
                cout << "\nEnter account number: ";
                cin >> accountNumber;
                cout << "Choose account " << endl;
                cout << "1. Current\n2. Savings" << endl;
                cin >> acc_type;
                if (mp.find(accountNumber) != mp.end()) {
                    cout << "Enter deposit amount: Rs. ";
                    cin >> amount;
                    if (amount > 50000) { 
                      cout << "---------Sorry! Amount greater than 50000 can not be deposited---------" << endl<<endl;
                    } else {
                      accounts[mp[accountNumber]]->deposit(amount);
                      cout << "------------Amount Successfully Deposit!------------" << endl<<endl;
                    }
                } else {
                    cout << "---------Invalid account number---------" << endl<<endl;
                }
                break;
            }
            case 4: {
                int accountNumber;
                double amount;
                cout << "\nEnter account number: ";
                cin >> accountNumber;
                if (mp.find(accountNumber) != mp.end()) {
                    cout << "Enter withdrawal amount: Rs. ";
                    cin >> amount;
                    if(amount > 1000) { 
                      accounts[mp[accountNumber]]->withdraw(amount);
                      cout << "------------Amount Withdraw Successfully!------------" << endl<<endl;
                    } else {
                      cout << "---------Sorry! Amount less than balance can not be withdrawan---------" << endl<<endl;
                    }
                } else {
                    cout << "---------Invalid account number---------" << endl<<endl;
                }
                break;
            }
            case 5:
                cout << "\n---------ALL ACCOUNTS---------" << endl << endl;
                for (int i = 0; i < accounts.size(); ++i) {
                    accounts[i]->displayAccount();
                }
                break;
            case 6:
                // Clean up dynamically allocated objects
                for (auto account : accounts) {
                    delete account;
                }
                cout << "\n\n------------Thank You for using Banking Machine!------------" << endl;
                return 0;
            default:
                cout << "\n\n---------Invalid choice. Please try again---------" << endl;
        }
    }

    return 0;
}