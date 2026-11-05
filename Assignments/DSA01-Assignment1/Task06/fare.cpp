#include <iomanip>
#include <iostream>

enum class Zone { Inner, Middle, Outer };

constexpr int BASE_PAISE[] = {1000, 2000, 3000}; // Rs 10, Rs 20, Rs 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;   // Rs 50 must remain

constexpr bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long fare(Zone z, bool peak) {
    int base = 0;
    switch (z) {
        case Zone::Inner:  base = BASE_PAISE[0]; break;
        case Zone::Middle: base = BASE_PAISE[1]; break;
        case Zone::Outer:  base = BASE_PAISE[2]; break;
        default: return 0; // Invalid enum value: reject as zero/invalid fare.
    }

    long long result = base;
    if (peak) {
        result += result * PEAK_SURCHARGE_PERCENT / 100;
    }
    return result;
}

bool canTravel(long long balance, long long f) {
    return f > 0 && balance >= f && balance - f >= MIN_BALANCE_PAISE;
}

int main() {
    long long balance = 10000; // Rs 100.00 in paise
    struct Trip { Zone zone; bool peak; };
    Trip trips[] = {
        {Zone::Inner, false},
        {Zone::Outer, true},
        {Zone::Middle, false}
    };

    for (const Trip& t : trips) {
        const long long f = fare(t.zone, t.peak);
        if (canTravel(balance, f)) {
            balance -= f;
            std::cout << "Fare Rs " << f / 100 << '.'
                      << std::setw(2) << std::setfill('0') << f % 100
                      << std::setfill(' ');
        } else {
            std::cout << "Denied (low balance)";
        }
        std::cout << "  balance Rs " << balance / 100 << '\n';
    }
}

// Boundary checks: 10:00 and 20:00 are off-peak; 08:00 and 17:00 are peak.
static_assert(isPeakHour(8));
static_assert(!isPeakHour(10));
static_assert(isPeakHour(17));
static_assert(!isPeakHour(20));
