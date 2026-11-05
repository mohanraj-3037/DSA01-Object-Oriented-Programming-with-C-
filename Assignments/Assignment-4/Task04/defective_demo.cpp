#include <iostream>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; }
    ~Account() { std::cout << "Account destructor\n"; }
};
class SeniorAccount : public Account {
    double* history_ = new double[100];
public:
    double rate() const { return 4.0; } // Hides, does not override a virtual function.
    ~SeniorAccount() {
        std::cout << "SeniorAccount destructor\n";
        delete[] history_;
    }
};
int main() {
    Account* accounts[2] = {new Account, new SeniorAccount};
    for (Account* a : accounts) std::cout << a->rate() << '\n';
    for (Account* a : accounts) delete a; // UB: base destructor is not virtual.
    Account copy = SeniorAccount();       // Slicing.
    std::vector<Account> elsewhere;
    elsewhere.push_back(SeniorAccount()); // Also slices.
}
