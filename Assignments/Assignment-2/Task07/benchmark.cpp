#include <iostream>
#include <vector>
#include <chrono>
#include "original/shift_buffer.cpp"
#include "redesigned/circular_buffer.h"
using namespace std;
using Clock = chrono::steady_clock;

int main() {
    const size_t capacity = 100000;
    const size_t operations = 1000000;

    cout << "capacity=" << capacity << ", operations=" << operations << endl;

    ShiftHistory oldVersion(capacity);
    cout << "Running shift benchmark..." << endl;
    auto a = Clock::now();
    for (size_t i = 0; i < operations; ++i) oldVersion.add(static_cast<long long>(i));
    auto b = Clock::now();
    cout << "Shift benchmark complete." << endl;

    CircularHistory newVersion(capacity);
    cout << "Running circular benchmark..." << endl;
    auto c = Clock::now();
    for (size_t i = 0; i < operations; ++i) newVersion.add(static_cast<long long>(i));
    auto d = Clock::now();

    cout << "shift_ms=" << chrono::duration<double, milli>(b-a).count() << '\n';
    cout << "circular_ms=" << chrono::duration<double, milli>(d-c).count() << '\n';
    cout << "last_old=" << oldVersion.values().back()
         << ", last_new=" << newVersion.chronological(newVersion.size()-1) << '\n';
}
