#include <iostream>
#include <stdexcept>
#include <string>

class Auditorium {
    std::string name;
    int rows, seats;
    char** map;

public:
    Auditorium(const std::string& n, int r, int s)
        : name(n), rows(r > 0 ? r : 0), seats(s > 0 ? s : 0), map(nullptr) {
        if (rows == 0 || seats == 0) {
            rows = seats = 0;
            std::cout << "Created " << name << " with empty map\n";
            return;
        }
        map = new char*[rows]{};
        try {
            for (int i = 0; i < rows; ++i) {
                map[i] = new char[seats];
                for (int j = 0; j < seats; ++j) map[i][j] = 'O';
            }
        } catch (...) {
            for (int i = 0; i < rows; ++i) delete[] map[i];
            delete[] map;
            map = nullptr;
            throw;
        }
        std::cout << "Created " << name << " (" << rows << "x" << seats << ")\n";
    }

    bool book(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats || map[r][s] == 'X') return false;
        map[r][s] = 'X';
        return true;
    }
    bool cancel(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats || map[r][s] == 'O') return false;
        map[r][s] = 'O';
        return true;
    }
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < seats; ++j) std::cout << map[i][j] << ' ';
            std::cout << '\n';
        }
    }
    ~Auditorium() {
        for (int i = 0; i < rows; ++i) delete[] map[i];
        delete[] map;
        std::cout << "Closed " << name << '\n';
    }
};

int main() {
    Auditorium stackEvent("Stack event", 2, 3);
    stackEvent.book(0, 1);
    stackEvent.print();

    Auditorium* heapEvent = new Auditorium("Heap event", 1, 2);
    heapEvent->book(0, 0);
    delete heapEvent;

    {
        Auditorium blockEvent("Block event", 1, 2);
        blockEvent.book(0, 1);
    }
    Auditorium emptyEvent("Empty event", 0, 5);
}
