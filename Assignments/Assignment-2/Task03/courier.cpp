#include <iostream>
#include <iomanip>
using namespace std;

struct Parcel {
    double weightKg;
    bool express = false;
    bool insured = false;
};

double charge(double weightKg, bool express = false, bool insured = false) {
    double total = weightKg * 50.0;
    if (express) total += 30.0;
    if (insured) total += 20.0;
    return total;
}

double charge(int weightGrams) {
    return charge(weightGrams / 1000.0, false, false);
}

double charge(const Parcel& parcel) {
    return charge(parcel.weightKg, parcel.express, parcel.insured);
}

int main() {
    cout << fixed << setprecision(2);
    cout << "charge(2)       -> double/kg overload: " << charge(2) << '\n';
    cout << "charge(2.0)     -> double/kg overload: " << charge(2.0) << '\n';
    cout << "charge(2.0f)    -> double/kg overload: " << charge(2.0f) << '\n';
    cout << "charge(2000)    -> int/grams overload: " << charge(2000) << '\n';
    Parcel p{2.5, true, true};
    cout << "charge(Parcel)  -> Parcel overload: " << charge(p) << '\n';
    cout << "charge(2,true)  -> double/kg overload: " << charge(2.0, true) << '\n';
}
