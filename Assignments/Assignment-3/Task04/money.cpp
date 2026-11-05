#include <iomanip>
#include <iostream>
#include <stdexcept>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        return Money(0, static_cast<int>(paise + other.paise));
    }
    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }
    bool operator==(const Money& other) const { return paise == other.paise; }
    bool operator<(const Money& other) const { return paise < other.paise; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long whole = m.paise / 100;
        long long fraction = m.paise % 100;
        if (fraction < 0) fraction = -fraction;
        return os << "Rs " << (m.paise < 0 && whole == 0 ? "-" : "")
                  << (whole < 0 ? -whole : whole) << '.'
                  << std::setw(2) << std::setfill('0') << fraction
                  << std::setfill(' ');
    }
    friend std::istream& operator>>(std::istream& is, Money& m) {
        long long r; int p;
        if (is >> r >> p) m.paise = r * 100 + (r < 0 ? -p : p);
        return is;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';
    Money carry(0, 75);
    carry += Money(0, 50);
    std::cout << carry << '\n';
    Money negative(1, 0);
    negative += Money(-2, 0);
    std::cout << negative << '\n';
}
