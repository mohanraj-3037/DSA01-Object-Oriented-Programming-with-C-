#include <iostream>
#include <string_view>

// Strongly typed zone names prevent accidental use of unrelated integers.
enum class Zone {
    Inner,
    Middle,
    Outer
};

// constexpr values are compile-time constants with type and scope.
constexpr long long INNER_FARE_PAISE = 1000;   // Rs 10.00
constexpr long long MIDDLE_FARE_PAISE = 2000;  // Rs 20.00
constexpr long long OUTER_FARE_PAISE = 3000;   // Rs 30.00
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000; // Rs 50.00

constexpr long long baseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return INNER_FARE_PAISE;
        case Zone::Middle: return MIDDLE_FARE_PAISE;
        case Zone::Outer:  return OUTER_FARE_PAISE;
    }
    return 0; // Defensive fallback for an invalid enum value.
}

constexpr std::string_view zoneName(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return "Inner";
        case Zone::Middle: return "Middle";
        case Zone::Outer:  return "Outer";
    }
    return "Unknown";
}

int main() {
    std::cout << "Metro fare constants\n";
    std::cout << zoneName(Zone::Inner) << ": " << baseFare(Zone::Inner) << " paise\n";
    std::cout << zoneName(Zone::Middle) << ": " << baseFare(Zone::Middle) << " paise\n";
    std::cout << zoneName(Zone::Outer) << ": " << baseFare(Zone::Outer) << " paise\n";
    std::cout << "Peak surcharge: " << PEAK_SURCHARGE_PERCENT << "%\n";
    std::cout << "Minimum remaining balance: " << MIN_BALANCE_PAISE << " paise\n";
}
