#include <iostream>
struct Bill {
    ~Bill() { std::cout << "~Bill "; }
    virtual double total() const = 0;
};
struct OPBill : Bill {
    ~OPBill() { std::cout << "~OPBill "; }
    double total() const override { return 500; }
};
int main() { Bill* b = new OPBill; std::cout << b->total() << '\n'; delete b; }
