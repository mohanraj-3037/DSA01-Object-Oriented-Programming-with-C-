#include <iostream>
#include <string>
#include <utility>

class Prescription {
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count < 0 ? 0 : count), medicines(new std::string[n]) {}

    Prescription(const Prescription& other)
        : n(other.n), medicines(new std::string[other.n]) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
        std::cout << "[copy constructor] ";
    }

    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this;
        std::string* fresh = new std::string[other.n];
        for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
        delete[] medicines;
        medicines = fresh;
        n = other.n;
        return *this;
    }

    ~Prescription() { delete[] medicines; }

    void set(int i, const std::string& m) {
        if (i >= 0 && i < n) medicines[i] = m;
    }
    std::string get(int i) const {
        return (i >= 0 && i < n) ? medicines[i] : "";
    }
    int size() const { return n; }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';
    r = r; // self-assignment test
}
