#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int id_;
    std::string phone_;
public:
    Person(std::string n, int id, std::string phone)
        : name_(std::move(n)), id_(id), phone_(std::move(phone)) {}
    virtual ~Person() = default;
    const std::string& name() const { return name_; }
};

class Student : virtual public Person {
protected:
    std::string programme_;
    double cgpa_;
public:
    Student(std::string n, int id, std::string phone,
            std::string programme, double cgpa)
        : Person(std::move(n), id, std::move(phone)),
          programme_(std::move(programme)), cgpa_(cgpa) {}
};

class Staff : virtual public Person {
protected:
    std::string department_;
    double salary_;
public:
    Staff(std::string n, int id, std::string phone,
          std::string department, double salary)
        : Person(std::move(n), id, std::move(phone)),
          department_(std::move(department)), salary_(salary) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string n, int id, std::string phone,
                      std::string programme, double cgpa,
                      std::string department, double salary)
        : Person(n, id, phone),
          Student(n, id, phone, programme, cgpa),
          Staff(n, id, phone, department, salary) {}
    void print() const {
        std::cout << name_ << " | " << programme_ << " | "
                  << department_ << " | " << salary_ << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship_;
public:
    ResearchScholar(std::string n, int id, std::string phone,
                    std::string programme, double cgpa, double fellowship)
        : Person(n, id, phone),
          Student(n, id, phone, programme, cgpa),
          fellowship_(fellowship) {}
    double fellowship() const { return fellowship_; }
};

struct TracePerson { TracePerson() { std::cout << "Person "; } };
struct TraceStudent : virtual TracePerson {
    TraceStudent() { std::cout << "Student "; }
};
struct TraceStaff : virtual TracePerson {
    TraceStaff() { std::cout << "Staff "; }
};
struct TraceTA : TraceStudent, TraceStaff {
    TraceTA() { std::cout << "TA "; }
};

int main() {
    TeachingAssistant ta("Kavya", 12, "9000000000", "CSE", 9.1, "IT", 25000);
    ta.print();
    ResearchScholar rs("Arun", 13, "9111111111", "AI", 9.4, 12000);
    std::cout << rs.name() << " fellowship " << rs.fellowship() << '\n';
    TraceTA trace;
    std::cout << '\n';
}
