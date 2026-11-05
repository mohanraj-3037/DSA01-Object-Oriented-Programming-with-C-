#include <array>
#include <iostream>
#include <string>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };

struct FareEntry {
    Zone zone;
    const char* name;
    long long farePaise;
};

constexpr array<FareEntry, 4> FARE_TABLE{{
    {Zone::Inner, "Inner", 1000},
    {Zone::Middle, "Middle", 2000},
    {Zone::Outer, "Outer", 3000},
    {Zone::Airport, "Airport", 6000}
}};

long long baseFare(Zone zone) {
    for (const auto& entry : FARE_TABLE) {
        if (entry.zone == zone) return entry.farePaise;
    }
    return -1;
}

const char* zoneName(Zone zone) {
    for (const auto& entry : FARE_TABLE) {
        if (entry.zone == zone) return entry.name;
    }
    return "Unknown";
}

bool validHour(int hour) {
    return hour >= 0 && hour <= 23;
}

bool isPeak(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

// Weekend discount takes precedence. It never combines with peak surcharge.
// All amounts are integer paise; the percentage calculations round to nearest paise.
long long calculateFare(Zone zone, int hour, bool weekend) {
    if (!validHour(hour)) return -1;
    long long fare = baseFare(zone);
    if (fare < 0) return -1;

    if (weekend) {
        fare = (fare * 90 + 50) / 100; // 10% discount, nearest paise
    } else if (isPeak(hour)) {
        fare = (fare * 120 + 50) / 100; // 20% peak surcharge
    }
    return fare;
}

class Pass {
private:
    Zone firstZone;
    Zone secondZone;
    bool active;

public:
    Pass(Zone first, Zone second, bool isActive = true)
        : firstZone(first), secondZone(second), active(isActive) {}

    bool covers(Zone zone) const {
        return active && (zone == firstZone || zone == secondZone);
    }
};

class SmartCard {
private:
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    explicit SmartCard(long long initialBalancePaise)
        : balancePaise(initialBalancePaise >= 0 ? initialBalancePaise : 0) {}

    long long getBalance() const {
        return balancePaise;
    }

    bool payFare(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < MIN_BALANCE_PAISE) {
            return false;
        }
        balancePaise -= farePaise;
        return true;
    }
};

struct JourneyResult {
    bool accepted;
    bool passUsed;
    long long farePaise;
    string message;
};

JourneyResult processJourney(SmartCard& card, const Pass& pass,
                             Zone zone, int hour, bool weekend) {
    if (!validHour(hour) || baseFare(zone) < 0) {
        return {false, false, -1, "Rejected (invalid journey details)"};
    }

    if (pass.covers(zone)) {
        return {true, true, 0, "Accepted (monthly pass used)"};
    }

    const long long fare = calculateFare(zone, hour, weekend);
    if (!card.payFare(fare)) {
        return {false, false, fare, "Denied (low balance)"};
    }
    return {true, false, fare, "Accepted (fare deducted)"};
}

void printRupees(long long paise) {
    cout << "Rs " << paise / 100 << '.';
    if (paise % 100 < 10) cout << '0';
    cout << paise % 100;
}

int main() {
    cout << "Airport fare examples\n";
    cout << "Weekday off-peak: "; printRupees(calculateFare(Zone::Airport, 12, false)); cout << '\n';
    cout << "Weekday peak: "; printRupees(calculateFare(Zone::Airport, 8, false)); cout << '\n';
    cout << "Weekend off-peak: "; printRupees(calculateFare(Zone::Airport, 12, true)); cout << '\n';
    cout << "Weekend peak hour (discount takes precedence): ";
    printRupees(calculateFare(Zone::Airport, 8, true)); cout << "\n\n";

    SmartCard card(20000); // Rs 200.00
    Pass monthlyPass(Zone::Inner, Zone::Middle);

    const auto covered = processJourney(card, monthlyPass, Zone::Inner, 8, false);
    cout << "Inner journey: " << covered.message << ", balance ";
    printRupees(card.getBalance()); cout << '\n';

    const auto charged = processJourney(card, monthlyPass, Zone::Airport, 8, false);
    cout << "Airport journey: " << charged.message << ", fare ";
    printRupees(charged.farePaise); cout << ", balance ";
    printRupees(card.getBalance()); cout << '\n';

    return 0;
}
