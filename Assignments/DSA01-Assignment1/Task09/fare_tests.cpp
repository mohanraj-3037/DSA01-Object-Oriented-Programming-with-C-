#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Zone { Inner, Middle, Outer };

long long baseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner: return 1000;
        case Zone::Middle: return 2000;
        case Zone::Outer: return 3000;
    }
    return -1;
}

// Peak periods are [08:00, 10:00) and [17:00, 20:00).
bool isPeak(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

// Fare is rounded to the nearest paise using integer arithmetic.
// With these base fares, 20% is an exact whole-paise amount.
long long calculateFare(Zone zone, int hour) {
    long long fare = baseFare(zone);
    if (fare < 0 || hour < 0 || hour > 23) return -1;
    if (isPeak(hour)) fare = (fare * 120 + 50) / 100;
    return fare;
}

bool canTravel(long long balance, long long fare) {
    constexpr long long MIN_BALANCE = 5000;
    return balance >= 0 && fare >= 0 && balance - fare >= MIN_BALANCE;
}

struct Test {
    string name;
    bool passed;
};

int main() {
    vector<Test> tests;
    auto check = [&](const string& name, bool condition) {
        tests.push_back({name, condition});
    };

    check("Inner off-peak fare is 1000 paise", calculateFare(Zone::Inner, 12) == 1000);
    check("Middle off-peak fare is 2000 paise", calculateFare(Zone::Middle, 12) == 2000);
    check("Outer off-peak fare is 3000 paise", calculateFare(Zone::Outer, 12) == 3000);

    check("08:00 is peak", isPeak(8));
    check("10:00 is off-peak", !isPeak(10));
    check("17:00 is peak", isPeak(17));
    check("20:00 is off-peak", !isPeak(20));

    check("Inner peak fare is 1200 paise", calculateFare(Zone::Inner, 8) == 1200);
    check("Middle peak fare is 2400 paise", calculateFare(Zone::Middle, 17) == 2400);
    check("Outer peak fare is 3600 paise", calculateFare(Zone::Outer, 19) == 3600);

    check("Exactly Rs 50 remaining is allowed", canTravel(8000, 3000));
    check("Less than Rs 50 remaining is denied", !canTravel(7999, 3000));
    check("Negative balance is invalid", !canTravel(-1, 1000));
    check("Negative fare is invalid", !canTravel(10000, -1));
    check("Invalid hour is rejected", calculateFare(Zone::Outer, 24) == -1);

    // Five consecutive journeys, each deducted only if the invariant holds.
    long long balance = 20000;
    const vector<pair<Zone, int>> journeys = {
        {Zone::Inner, 7}, {Zone::Middle, 8}, {Zone::Outer, 12},
        {Zone::Inner, 17}, {Zone::Middle, 20}
    };
    int accepted = 0;
    for (const auto& journey : journeys) {
        long long fare = calculateFare(journey.first, journey.second);
        if (canTravel(balance, fare)) {
            balance -= fare;
            ++accepted;
        }
    }
    check("Five-journey scenario accepts all five", accepted == 5);
    check("Five-journey final balance is 10400 paise", balance == 10400);

    int passed = 0;
    for (const auto& test : tests) {
        cout << (test.passed ? "[PASS] " : "[FAIL] ") << test.name << '\n';
        if (test.passed) ++passed;
    }
    cout << "\nResult: " << passed << "/" << tests.size() << " tests passed.\n";
    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
