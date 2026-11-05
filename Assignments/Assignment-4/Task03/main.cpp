#include <iostream>
#include <string>

struct Engine {
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};
struct Vehicle {
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle "; }
};
struct Car : Vehicle {
    Engine engine;
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

class Person {
protected:
    std::string name_;
    int age_;
public:
    Person(const std::string& n, int a) : name_(n), age_(a) {}
};
class Address {
    std::string city_;
    int pin_;
public:
    Address(const std::string& city, int pin) : city_(city), pin_(pin) {}
    std::string str() const { return city_ + "-" + std::to_string(pin_); }
};
class Student : public Person {
    long long regNo_;
    Address home_;
public:
    Student(const std::string& name, int age, long long regNo,
            const std::string& city, int pin)
        : Person(name, age), regNo_(regNo), home_(city, pin) {}
    void print() const {
        std::cout << regNo_ << ' ' << name_ << " (" << age_ << ") "
                  << home_.str() << '\n';
    }
};

int main() {
    {
        Car c;
        std::cout << "| ";
    }
    std::cout << '\n';
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();
}
