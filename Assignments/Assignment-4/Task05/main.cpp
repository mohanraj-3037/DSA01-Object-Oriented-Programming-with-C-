#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Cart {
    std::string items_[10];
    double prices_[10]{};
    int count_ = 0;
    double discount_ = 0.0;
public:
    Cart& add(const std::string& item, double price) {
        if (count_ < 10 && price >= 0.0) {
            items_[count_] = item;
            prices_[count_] = price;
            ++count_;
        }
        return *this;
    }
    Cart& setDiscount(double discount) {
        this->discount_ = (discount < 0.0) ? 0.0 :
                          (discount > 100.0 ? 100.0 : discount);
        return *this;
    }
    double total() const {
        double sum = 0.0;
        for (int i = 0; i < count_; ++i) sum += prices_[i];
        return sum * (100.0 - discount_) / 100.0;
    }
};

int main() {
    Cart direct;
    direct.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* pointer = &direct;
    pointer->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2)
              << pointer->total() << '\n';

    Cart& reference = direct;
    reference.setDiscount(0);
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Milk", 50);
    std::cout << "Dynamic cart: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    Cart second;
    second.add("Books", 400);
    Cart* carts[] = {&direct, &second};
    Cart* highest = carts[0];
    for (Cart* cart : carts)
        if (cart->total() > highest->total()) highest = cart;
    std::cout << "Highest total: " << highest->total() << '\n';
}
