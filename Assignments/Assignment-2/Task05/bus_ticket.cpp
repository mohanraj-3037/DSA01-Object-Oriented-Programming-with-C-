#include <iostream>
#include <string>
using namespace std;

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    string name;

public:
    explicit BusTicket(const string& n) : seat(0), name(n) {
        if (issued < CAPACITY) {
            ++issued;
            seat = issued;
        }
    }

    static int count() { return issued; }

    void print() const {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat) : string("Waiting")) << '\n';
    }
};

int BusTicket::issued = 0;

void createBatch(const string& prefix) {
    BusTicket batch[2] = {BusTicket(prefix + "-1"), BusTicket(prefix + "-2")};
    for (const BusTicket& ticket : batch) ticket.print();
    cout << "Cumulative issued: " << BusTicket::count() << '\n';
}

int main() {
    BusTicket trip[4] = {
        BusTicket("Asha"), BusTicket("Bala"),
        BusTicket("Chitra"), BusTicket("Dev")
    };
    for (const BusTicket& ticket : trip) ticket.print();
    cout << "Issued: " << BusTicket::count() << '\n';

    cout << "Two further batches:\n";
    createBatch("BatchA");
    createBatch("BatchB");
}
