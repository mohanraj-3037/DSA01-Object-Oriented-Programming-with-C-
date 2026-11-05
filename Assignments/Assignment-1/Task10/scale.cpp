#include <iostream>
using namespace std;

int main() {
    constexpr long long MAX_FARE_PAISE = 3600; // Rs 30 + 20% peak surcharge
    constexpr long long JOURNEYS_20K = 20000;
    constexpr long long JOURNEYS_500K = 500000;
    constexpr long long JOURNEYS_3M = 3000000;

    const long long total20K = JOURNEYS_20K * MAX_FARE_PAISE;
    const long long total500K = JOURNEYS_500K * MAX_FARE_PAISE;
    const long long total3M = JOURNEYS_3M * MAX_FARE_PAISE;

    cout << "Maximum fare: " << MAX_FARE_PAISE << " paise (Rs 36.00)\n";
    cout << "20,000 journeys: " << total20K << " paise\n";
    cout << "500,000 journeys: " << total500K << " paise\n";
    cout << "3,000,000 journeys: " << total3M << " paise\n";
    cout << "Signed 32-bit int maximum: 2147483647\n";
    cout << "3-million total exceeds signed 32-bit int: "
         << (total3M > 2147483647LL ? "yes" : "no") << '\n';
    return 0;
}
