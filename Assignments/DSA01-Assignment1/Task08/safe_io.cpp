#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

int main() {
    long long balancePaise = 0;
    long long farePaise = 0;

    cout << "Enter card balance in paise: ";
    while (!(cin >> balancePaise) || balancePaise < 0) {
        cout << "Invalid balance. Enter a non-negative whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter fare in paise: ";
    while (!(cin >> farePaise) || farePaise < 0) {
        cout << "Invalid fare. Enter a non-negative whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    constexpr long long MIN_BALANCE_PAISE = 5000;
    if (balancePaise - farePaise < MIN_BALANCE_PAISE) {
        cout << "Denied (low balance). Balance remains Rs "
             << fixed << setprecision(2) << balancePaise / 100.0 << '\n';
    } else {
        balancePaise -= farePaise;
        cout << "Payment accepted. New balance Rs "
             << fixed << setprecision(2) << balancePaise / 100.0 << '\n';
    }
    return 0;
}
