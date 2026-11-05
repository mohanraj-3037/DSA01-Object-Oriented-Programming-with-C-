#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
    std::string name_;
    int id_;
protected:
    double basic_;
public:
    Staff(std::string name, int id, double basic)
        : name_(std::move(name)), id_(id), basic_(basic) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual void print() const {
        std::cout << name_ << " (ID " << id_ << "): Rs "
                  << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class Professor : public Staff {
    double research_;
public:
    Professor(std::string n, int id, double basic, double research)
        : Staff(std::move(n), id, basic), research_(research) {}
    double pay() const override { return basic_ * 1.42 + research_; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(std::string n, int id, double basic)
        : Staff(std::move(n), id, basic) {}
    double pay() const override { return basic_ * 1.42; }
};

class GuestFaculty : public Staff {
    double hours_, rate_;
public:
    GuestFaculty(std::string n, int id, double hours, double rate)
        : Staff(std::move(n), id, 0.0), hours_(hours), rate_(rate) {}
    double pay() const override { return hours_ * rate_; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Bala", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Charan", 103, 40, 900));
    for (const auto& person : staff) person->print();
}
