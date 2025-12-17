#include <bits/stdc++.h>
using namespace std;

class Account {
private:
    int accNo;
    string name;
    double balance;

public:
    Account(int a = 0, string n = "", double b = 0) {
        accNo = a;
        name = n;
        balance = b;
    }

    int getAccNo() const { return accNo; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amt) {
        if (amt <= 0) {
            cout << "Invalid amount\n";
            return;
        }
        balance += amt;
        cout << "Amount deposited successfully\n";
    }

    void withdraw(double amt) {
        if (amt <= 0 || amt > balance) {
            cout << "Invalid or insufficient balance\n";
            return;
        }
        balance -= amt;
        cout << "Amount withdrawn successfully\n";
    }

    void display() const {
        cout << "Account No: " << accNo
             << " | Name: " << name
             << " | Balance: " << balance << endl;
    }

    // File I/O
    void writeToFile(ofstream &out) const {
        out << accNo << " " << name << " " << balance << "\\n";
    }

    void readFromFile(ifstream &in) {
        in >> accNo >> name >> balance;
    }
};

vector<Account> accounts;

// ---------- FILE HANDLING ----------
void loadData() {
    ifstream in("accounts.txt");
    if (!in) return;

    Account acc;
    while (in.peek() != EOF) {
        acc.readFromFile(in);
        accounts.push_back(acc);
    }
    in.close();
}

void saveData() {
    ofstream out("accounts.txt");
    for (const auto &acc : accounts)
        acc.writeToFile(out);
    out.close();
}

// ---------- UTILITIES ----------
Account* findAccount(int accNo) {
    for (auto &acc : accounts)
        if (acc.getAccNo() == accNo)
            return &acc;
    return nullptr;
}

// ---------- OPERATIONS ----------
void createAccount() {
    int accNo;
    string name;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (findAccount(accNo)) {
        cout << "Account already exists\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Initial Balance: ";
    cin >> balance;

    accounts.push_back(Account(accNo, name, balance));
    cout << "Account created successfully\n";
}

void depositMoney() {
    int accNo;
    double amt;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found\n";
        return;
    }

    cout << "Enter amount to deposit: ";
    cin >> amt;
    acc->deposit(amt);
}

void withdrawMoney() {
    int accNo;
    double amt;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found\n";
        return;
    }

    cout << "Enter amount to withdraw: ";
    cin >> amt;
    acc->withdraw(amt);
}

void showAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found\n";
        return;
    }
    acc->display();
}

void showAllAccounts() {
    for (const auto &acc : accounts)
        acc.display();
}

// ---------- MAIN ----------
int main() {
    loadData();
    int choice;

    do {
        cout << "\\n===== BANK MANAGEMENT SYSTEM =====\\n";
        cout << "1. Create Account\\n";
        cout << "2. Deposit Money\\n";
        cout << "3. Withdraw Money\\n";
        cout << "4. Show Account Details\\n";
        cout << "5. Show All Accounts\\n";
        cout << "0. Exit\\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: showAccount(); break;
            case 5: showAllAccounts(); break;
            case 0: saveData(); cout << "Data saved. Exiting...\\n"; break;
            default: cout << "Invalid choice\\n";
        }
    } while (choice != 0);

    return 0;
}
