#define main fare_demo_main
#include "final_fare_system.cpp"
#undef main

int main() {
    int passed = 0;
    int total = 0;
    auto check = [&](const char* name, bool condition) {
        ++total;
        cout << (condition ? "[PASS] " : "[FAIL] ") << name << '\n';
        if (condition) ++passed;
    };

    check("Airport base fare is Rs 60", baseFare(Zone::Airport) == 6000);
    check("Airport weekday off-peak is Rs 60", calculateFare(Zone::Airport, 12, false) == 6000);
    check("Airport weekday peak is Rs 72", calculateFare(Zone::Airport, 8, false) == 7200);
    check("Airport weekend fare is Rs 54", calculateFare(Zone::Airport, 12, true) == 5400);
    check("Weekend peak does not stack surcharge", calculateFare(Zone::Airport, 8, true) == 5400);
    check("10 AM is off-peak", !isPeak(10));
    check("20:00 is off-peak", !isPeak(20));
    check("Invalid hour rejected", calculateFare(Zone::Airport, 24, false) == -1);

    Pass pass(Zone::Inner, Zone::Middle);
    check("Pass covers first selected zone", pass.covers(Zone::Inner));
    check("Pass covers second selected zone", pass.covers(Zone::Middle));
    check("Pass does not cover Airport", !pass.covers(Zone::Airport));

    SmartCard card(12000);
    auto freeRide = processJourney(card, pass, Zone::Inner, 8, false);
    check("Pass journey accepted without deduction", freeRide.accepted && freeRide.passUsed && card.getBalance() == 12000);

    auto paidRide = processJourney(card, pass, Zone::Airport, 12, false);
    check("Uncovered Airport ride deducts Rs 60", paidRide.accepted && !paidRide.passUsed && card.getBalance() == 6000);

    SmartCard lowCard(8000);
    auto deniedRide = processJourney(lowCard, pass, Zone::Airport, 12, false);
    check("Low-balance Airport ride denied", !deniedRide.accepted && lowCard.getBalance() == 8000);

    SmartCard invalidCard(10000);
    auto invalidRide = processJourney(invalidCard, pass, Zone::Airport, 24, false);
    check("Invalid journey does not change balance", !invalidRide.accepted && invalidCard.getBalance() == 10000);

    cout << "\nResult: " << passed << "/" << total << " tests passed.\n";
    return passed == total ? 0 : 1;
}
