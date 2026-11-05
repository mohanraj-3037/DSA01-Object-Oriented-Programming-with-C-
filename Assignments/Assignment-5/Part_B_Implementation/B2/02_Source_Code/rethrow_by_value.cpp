#include <iostream>
#include <stdexcept>
#include <typeinfo>
class ClaimError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};
double approve(double billed,double cover) {
    if (billed > cover) throw ClaimError("exceeds cover");
    return billed;
}
double settle(double billed,double cover) {
    try { return approve(billed,cover); }
    catch (const ClaimError& e) { std::cout << "audit: " << e.what() << '\n'; throw e; }
}
int main() {
    try { settle(60000,50000); }
    catch (const ClaimError& e) { std::cout << "claim rejected: " << e.what() << '\n'; }
}
