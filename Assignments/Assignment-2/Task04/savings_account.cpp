#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SavingsAccount {
private:
    long long accountNumber;
    long long balancePaise;
    long long transactions[10];
    int count;
    int next; // next insertion position; also oldest when full

    void record(long long signedAmount) {
        transactions[next] = signedAmount;
        next = (next + 1) % 10;
        if (count < 10) ++count;
    }

public:
    SavingsAccount(long long account, long long openingPaise)
        : accountNumber(account), balancePaise(openingPaise), count(0), next(0) {}

    void deposit(long long amountPaise);
    bool withdraw(long long amountPaise);
    void miniStatement() const;
    long long balance() const { return balancePaise; }
};

void SavingsAccount::deposit(long long amountPaise) {
    if (amountPaise <= 0) {
        cout << "Deposit must be positive\n";
        return;
    }
    balancePaise += amountPaise;
    record(amountPaise);
}

bool SavingsAccount::withdraw(long long amountPaise) {
    if (amountPaise <= 0 || amountPaise > balancePaise) {
        cout << "Withdrawal rejected\n";
        return false;
    }
    balancePaise -= amountPaise;
    record(-amountPaise);
    return true;
}

void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nLast " << count << " transactions:\n";
    int start = (count == 10) ? next : 0;
    for (int i = 0; i < count; ++i) {
        long long value = transactions[(start + i) % 10];
        cout << (value >= 0 ? "Deposit  " : "Withdraw ")
             << (value >= 0 ? value : -value) << " paise\n";
    }
    cout << "Balance: " << balancePaise << " paise\n";
}

int main() {
    SavingsAccount account(10001, 100000);
    for (int i = 1; i <= 7; ++i) account.deposit(i * 1000);
    for (int i = 1; i <= 5; ++i) account.withdraw(i * 500);
    account.miniStatement();
}
