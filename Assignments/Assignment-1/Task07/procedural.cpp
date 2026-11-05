#include <iostream>
using namespace std;

// Procedural version: balance is passed to a function and updated.
bool deductFare(long long &balancePaise, long long farePaise) {
    const long long minimumBalancePaise = 5000;
    if (farePaise < 0 || balancePaise - farePaise < minimumBalancePaise) {
        return false;
    }
    balancePaise -= farePaise;
    return true;
}

int main() {
    long long balancePaise = 10000;
    const long long farePaise = 3000;

    cout << "Procedural approach\n";
    if (deductFare(balancePaise, farePaise)) {
        cout << "Fare accepted. Balance: " << balancePaise << " paise\n";
    } else {
        cout << "Fare denied. Balance: " << balancePaise << " paise\n";
    }
    return 0;
}
