#pragma once
#include <vector>
#include <cstddef>

class CircularHistory {
    std::vector<long long> data;
    std::size_t next = 0;
    std::size_t count = 0;
public:
    explicit CircularHistory(std::size_t capacity) : data(capacity) {}
    void add(long long value) {
        if (data.empty()) return;
        data[next] = value;
        next = (next + 1) % data.size();
        if (count < data.size()) ++count;
    }
    std::size_t size() const { return count; }
    long long chronological(std::size_t i) const {
        const std::size_t start = (count == data.size()) ? next : 0;
        return data[(start + i) % data.size()];
    }
};
