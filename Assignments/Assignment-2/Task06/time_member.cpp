#include <iostream>
#include <cstdlib>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    int totalMinutes() const { return h * 60 + m; }
    int minutesTo(const Time& other) const {
        return abs(totalMinutes() - other.totalMinutes());
    }
    bool isEarlier(const Time& other) const {
        return totalMinutes() < other.totalMinutes();
    }
};

int main() {
    Time a(9, 45), b(13, 10);
    cout << a.minutesTo(b) << ' ' << boolalpha << b.isEarlier(a) << '\n';
}
