#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() = default;
};
class SeniorAccount : public Account {
    double* history_;
public:
    SeniorAccount() : history_(new double[100]{}) {}
    ~SeniorAccount() override { delete[] history_; }
    double rate() const override { return 4.0; }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts)
        std::cout << account->rate() << '\n';

    SeniorAccount senior;
    Account sliced = senior; // Demonstrates slicing: only the Account part is copied.
    std::cout << "Sliced copy rate: " << sliced.rate() << '\n';
}
