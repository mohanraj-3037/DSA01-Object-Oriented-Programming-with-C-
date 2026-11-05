#include <iostream>
using namespace std;

class SmartCard {
private:
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    explicit SmartCard(long long initialBalancePaise)
        : balancePaise(initialBalancePaise >= 0 ? initialBalancePaise : 0) {}

    bool payFare(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < MIN_BALANCE_PAISE) {
            return false;
        }
        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const {
        return balancePaise;
    }
};

int main() {
    SmartCard card(10000);
    const long long farePaise = 3000;

    cout << "Object-oriented approach\n";
    if (card.payFare(farePaise)) {
        cout << "Fare accepted. Balance: " << card.getBalance() << " paise\n";
    } else {
        cout << "Fare denied. Balance: " << card.getBalance() << " paise\n";
    }
    return 0;
}
