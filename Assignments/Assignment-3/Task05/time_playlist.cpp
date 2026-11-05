#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;
public:
    explicit Time(int total = 0) : seconds((total % 86400 + 86400) % 86400) {}
    Time& operator++() { seconds = (seconds + 1) % 86400; return *this; }
    Time operator++(int) { Time old(*this); ++(*this); return old; }
    bool operator==(const Time& o) const { return seconds == o.seconds; }
    bool operator<(const Time& o) const { return seconds < o.seconds; }
    int value() const { return seconds; }
    void print() const {
        int h = seconds / 3600, m = (seconds / 60) % 60, s = seconds % 60;
        std::cout << h << ':' << (m < 10 ? "0" : "") << m << ':'
                  << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> t) : tracks(t) {}
    std::string& operator[](std::size_t i) {
        if (i >= tracks.size()) throw std::out_of_range("playlist index out of range");
        return tracks[i];
    }
    const std::string& operator[](std::size_t i) const {
        if (i >= tracks.size()) throw std::out_of_range("playlist index out of range");
        return tracks[i];
    }
    std::size_t size() const { return tracks.size(); }
};

int main() {
    Time t(3599);
    Time a = t++;
    Time b = ++t;
    std::cout << "a="; a.print();
    std::cout << " b="; b.print();
    std::cout << " t="; t.print(); std::cout << '\n';

    Playlist p{"Track One", "Track Two", "Track Three"};
    std::cout << p[1] << '\n';
    try { std::cout << p[static_cast<std::size_t>(-1)] << '\n'; }
    catch (const std::out_of_range& e) { std::cout << e.what() << '\n'; }
}
