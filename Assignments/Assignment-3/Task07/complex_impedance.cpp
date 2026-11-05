#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double real) : re(real), im(0) {}
    Complex(double real, double imag) : re(real), im(imag) {}

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }

    Complex operator+(const Complex& z) const { return {re + z.re, im + z.im}; }
    Complex operator-(const Complex& z) const { return {re - z.re, im - z.im}; }
    Complex operator*(const Complex& z) const {
        return {re*z.re - im*z.im, re*z.im + im*z.re};
    }
    Complex operator/(const Complex& z) const {
        double d = z.re*z.re + z.im*z.im;
        if (d == 0.0) throw std::domain_error("division by zero impedance");
        return {(re*z.re + im*z.im)/d, (im*z.re - re*z.im)/d};
    }
    bool operator==(const Complex& z) const {
        constexpr double eps = 1e-9;
        return std::abs(re-z.re) < eps && std::abs(im-z.im) < eps;
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << std::fixed << std::setprecision(3) << z.re
           << (z.im < 0 ? " - j" : " + j") << std::abs(z.im);
        return os;
    }
};

int main() {
    // Example RLC series impedance: R=10 ohm, XL=20 ohm, XC=5 ohm.
    Complex resistor(10, 0), inductor(0, 20), capacitor(0, -5);
    Complex series = resistor + inductor + capacitor;
    std::cout << "Series Z = " << series << ", |Z| = " << series.magnitude() << '\n';

    // Parallel combination of two impedances: (10+j5) || (20-j5).
    Complex z1(10, 5), z2(20, -5);
    Complex parallel = (z1 * z2) / (z1 + z2);
    std::cout << "Parallel Z = " << parallel << ", |Z| = " << parallel.magnitude() << '\n';

    try {
        Complex invalid = z1 / Complex();
        std::cout << invalid << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Handled: " << e.what() << '\n';
    }
}
