// Intentionally unsafe demonstration. Do not use this version in production.
// Two objects own the same pointer after the compiler-generated shallow copy.
#include <iostream>
class BadPrescription {
    int* data;
public:
    BadPrescription() : data(new int[2]{1, 2}) {}
    ~BadPrescription() { delete[] data; }
    void change() { data[0] = 99; }
    int first() const { return data[0]; }
};
int main() {
    BadPrescription p;
    BadPrescription q = p; // shallow copy: both objects own same allocation
    q.change();
    std::cout << p.first() << '\n'; // also changed
    // At scope exit both destructors delete the same pointer: undefined behaviour.
}
