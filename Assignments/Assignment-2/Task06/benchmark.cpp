#include <iostream>
#include <chrono>
#include <cstdint>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int inlineMinutesBetween(const Time&, const Time&);
    friend int ordinaryMinutesBetween(const Time&, const Time&);
};

inline int inlineMinutesBetween(const Time& a, const Time& b) {
    int x = a.h * 60 + a.m, y = b.h * 60 + b.m;
    return x > y ? x - y : y - x;
}

int ordinaryMinutesBetween(const Time& a, const Time& b) {
    int x = a.h * 60 + a.m, y = b.h * 60 + b.m;
    return x > y ? x - y : y - x;
}

int main() {
    const Time a(9, 45), b(13, 10);
    constexpr int N = 10000000;
    volatile std::uint64_t checksum = 0;

    auto start1 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) checksum += inlineMinutesBetween(a, b);
    auto end1 = chrono::steady_clock::now();

    auto start2 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) checksum += ordinaryMinutesBetween(a, b);
    auto end2 = chrono::steady_clock::now();

    cout << "inline_ms="
         << chrono::duration<double, milli>(end1 - start1).count() << '\n';
    cout << "ordinary_ms="
         << chrono::duration<double, milli>(end2 - start2).count() << '\n';
    cout << "checksum=" << checksum << '\n';
}
