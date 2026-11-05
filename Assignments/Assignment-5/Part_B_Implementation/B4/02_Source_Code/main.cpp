#include "billing.hpp"
#include <iostream>
#include <memory>
#include <vector>
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("1","Ravi",500,1200));
    bills.push_back(std::make_unique<DayCareBill>("2","Meena",18000));
    bills.push_back(std::make_unique<EmergencyBill>("3","Asha",1000,30,100));
    SelfPay self;
    CorporatePayer corporate(15);
    std::vector<const Payer*> payers{&self,&corporate};
    for (const auto& b : bills) {
        b->print();
        for (const Payer* p : payers)
            std::cout << "covered " << p->amountCovered(*b) << '\n';
    }
}
