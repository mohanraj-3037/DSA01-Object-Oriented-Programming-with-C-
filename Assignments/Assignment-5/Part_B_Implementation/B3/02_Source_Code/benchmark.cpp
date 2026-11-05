#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct BillBase { virtual ~BillBase()=default; virtual double total() const=0; };
struct OP : BillBase { double a,b; OP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct IP : BillBase { double room,procedure; int days; IP(double r,double p,int d):room(r),procedure(p),days(d){} double total()const override{return room*days+procedure;} };
struct Tagged { int type; double a,b; int days; };
double switchTotal(const Tagged& x) {
    switch(x.type) { case 0:return x.a+x.b; case 1:return x.a*x.days+x.b; default:return 0; }
}
using VariantBill=std::variant<OP,IP>;
double variantTotal(const VariantBill& v) {
    return std::visit([](const auto& x)->double {
        if constexpr (std::is_same_v<std::decay_t<decltype(x)>,OP>) return x.a+x.b;
        else return x.room*x.days+x.procedure;
    },v);
}
template<class F> double measure(const char* label, std::size_t n, F f) {
    volatile double sink=0;
    auto start=std::chrono::steady_clock::now();
    sink=f();
    auto end=std::chrono::steady_clock::now();
    double ms=std::chrono::duration<double,std::milli>(end-start).count();
    std::cout<<label<<" n="<<n<<" total="<<sink<<" time_ms="<<ms<<'\n';
    return ms;
}
int main() {
    for (std::size_t n : {1000u,1000000u,10000000u}) {
        std::vector<std::unique_ptr<BillBase>> poly; poly.reserve(n);
        std::vector<Tagged> tagged; tagged.reserve(n);
        std::vector<VariantBill> vars; vars.reserve(n);
        for(std::size_t i=0;i<n;++i) {
            if(i%2) { poly.push_back(std::make_unique<OP>(500,1200)); tagged.push_back({0,500,1200,0}); vars.emplace_back(OP(500,1200)); }
            else { poly.push_back(std::make_unique<IP>(2500,40000,3)); tagged.push_back({1,2500,40000,3}); vars.emplace_back(IP(2500,40000,3)); }
        }
        auto p=measure("virtual",n,[&]{double s=0;for(auto& x:poly)s+=x->total();return s;});
        auto sw=measure("switch",n,[&]{double s=0;for(auto& x:tagged)s+=switchTotal(x);return s;});
        auto v=measure("variant",n,[&]{double s=0;for(auto& x:vars)s+=variantTotal(x);return s;});
        std::cout<<"virtual/switch totals agree: "<<(p==sw)<<" | virtual/variant agree: "<<(p==v)<<'\n';
    }
}
