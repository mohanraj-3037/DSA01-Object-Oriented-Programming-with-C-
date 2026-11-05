#include <iostream>
using namespace std;

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyConcessionPointer(long long* fee, int percent) {
    if (fee != nullptr)
        *fee -= *fee * percent / 100;
}

long long concessionReturningValue(long long fee, int percent) {
    return fee - fee * percent / 100;
}

int main() {
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    cout << "after call by value   : " << hostelFee << '\n';
    applyConcession(hostelFee, 10);
    cout << "after call by reference: " << hostelFee << '\n';

    long long sportsFee = 45000;
    applyConcessionPointer(&sportsFee, 15);
    cout << "after call by pointer  : " << sportsFee << '\n';

    long long returnedFee = concessionReturningValue(45000, 25);
    cout << "returned fee           : " << returnedFee << '\n';
}
