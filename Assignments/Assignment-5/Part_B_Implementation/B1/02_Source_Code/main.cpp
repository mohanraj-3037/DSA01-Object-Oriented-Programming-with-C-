#include "billing.hpp"
#include <iomanip>
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("B1","Ravi",500,1200));
    bills.push_back(std::make_unique<InPatientBill>("B2","Meena",3,2500,40000,5000));
    bills.push_back(std::make_unique<DayCareBill>("B3","Kiran",18000));
    bills.push_back(std::make_unique<EmergencyBill>("B4","Asha",1000,30,100));
    SelfPay self; Insurance insurance(50000,20);
    GovernmentScheme scheme({{"OP",2000},{"IP",45000},{"DAYCARE",16000},{"EMERGENCY",3000}});
    std::vector<const Payer*> payers{&self,&insurance,&scheme};
    double daily=0;
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& b : bills) {
        b->print(); daily += b->total();
        for (const Payer* p : payers)
            std::cout << "  covered: " << p->amountCovered(*b) << '\n';
    }
    std::cout << "Daily total: " << daily << '\n';
}
