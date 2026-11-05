#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
volatile long long sinkValue=0;
template<class F> void run(const std::string& name,int n,F f) {
    auto s=std::chrono::steady_clock::now(); long long ok=0;
    for(int i=0;i<n;++i) if(f(i)) ++ok;
    auto e=std::chrono::steady_clock::now();
    sinkValue=ok;
    std::cout<<name<<" valid="<<ok<<" time_ms="
      <<std::chrono::duration<double,std::milli>(e-s).count()<<'\n';
}
int main() {
    constexpr int N=1000000;
    for(int pct:{0,1,50}) {
        auto invalid=[=](int i){return pct && (i%100)<pct;};
        run("return-code "+std::to_string(pct)+"%",N,[&](int i){return !invalid(i);});
        run("exception "+std::to_string(pct)+"%",N,[&](int i){
            try { if(invalid(i)) throw std::runtime_error("invalid"); return true; }
            catch(const std::exception&) { return false; }
        });
    }
}
