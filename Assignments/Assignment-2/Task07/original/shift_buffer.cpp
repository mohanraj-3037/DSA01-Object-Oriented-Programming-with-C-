#include <iostream>
#include <vector>
using namespace std;

class ShiftHistory {
    vector<long long> data;
    size_t capacity;
public:
    explicit ShiftHistory(size_t cap) : capacity(cap) {}
    void add(long long value) {
        if (data.size() == capacity) {
            for (size_t i = 1; i < data.size(); ++i) data[i - 1] = data[i];
            data.back() = value;
        } else data.push_back(value);
    }
    const vector<long long>& values() const { return data; }
};
