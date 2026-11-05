#include <climits>
#include <cstddef>
#include <iostream>
#include <limits>

int main() {
    // Currency is represented in integer paise, not floating-point rupees.
    const long long innerFarePaise = 1000;
    const long long middleFarePaise = 2000;
    const long long outerFarePaise = 3000;
    const long long peakOuterFarePaise = outerFarePaise * 120 / 100;

    // The network may process 3,000,000 journeys per day.
    constexpr long long journeysPerDay = 3'000'000;
    const long long worstCaseDailyRevenuePaise = journeysPerDay * peakOuterFarePaise;

    std::cout << "Type sizes on this compiler (bytes)\n";
    std::cout << "bool: " << sizeof(bool) << '\n';
    std::cout << "char: " << sizeof(char) << '\n';
    std::cout << "int: " << sizeof(int) << '\n';
    std::cout << "unsigned int: " << sizeof(unsigned int) << '\n';
    std::cout << "long long: " << sizeof(long long) << '\n';
    std::cout << "float: " << sizeof(float) << '\n';
    std::cout << "double: " << sizeof(double) << '\n';

    std::cout << "\nInteger limits\n";
    std::cout << "INT_MIN: " << INT_MIN << '\n';
    std::cout << "INT_MAX: " << INT_MAX << '\n';
    std::cout << "LLONG_MAX: " << LLONG_MAX << '\n';

    std::cout << "\nFare values (paise)\n";
    std::cout << "Inner: " << innerFarePaise << '\n';
    std::cout << "Middle: " << middleFarePaise << '\n';
    std::cout << "Outer: " << outerFarePaise << '\n';
    std::cout << "Peak outer: " << peakOuterFarePaise << '\n';

    std::cout << "\nWorst-case daily collection for 3,000,000 journeys\n";
    std::cout << "Total: " << worstCaseDailyRevenuePaise << " paise\n";
    std::cout << "INT_MAX: " << INT_MAX << " paise\n";
    std::cout << "Fits in int: "
              << (worstCaseDailyRevenuePaise <= INT_MAX ? "yes" : "no") << '\n';

    // Demonstrate that int and double in one expression cause conversion.
    const int count = 7;
    const double divisor = 2.0;
    const double result = count / divisor;
    std::cout << "\nMixed int/double expression (7 / 2.0): " << result << '\n';

    return 0;
}
