#include <cstring>
#include <iostream>
#include <utility>

class Text {
    char* data;
public:
    Text(const char* s = "") {
        std::size_t n = std::strlen(s);
        data = new char[n + 1];
        std::memcpy(data, s, n + 1);
    }
    Text(const Text& other) {
        std::size_t n = std::strlen(other.data);
        data = new char[n + 1];
        std::memcpy(data, other.data, n + 1);
        std::cout << "[copy] ";
    }
    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        std::size_t n = std::strlen(other.data);
        char* fresh = new char[n + 1];
        std::memcpy(fresh, other.data, n + 1);
        delete[] data;
        data = fresh;
        return *this;
    }
    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        std::size_t a = std::strlen(data), b = std::strlen(other.data);
        char* joined = new char[a + b + 1];
        std::memcpy(joined, data, a);
        std::memcpy(joined + a, other.data, b + 1);
        Text result(joined);
        delete[] joined;
        return result;
    }
    bool operator==(const Text& other) const { return std::strcmp(data, other.data) == 0; }
    bool operator!=(const Text& other) const { return !(*this == other); }
    friend std::ostream& operator<<(std::ostream& os, const Text& t) { return os << t.data; }
};

int main() {
    Text a("Hello "), b("world"), c("");
    Text combined = a + b + c;
    std::cout << combined << '\n';
    std::cout << std::boolalpha << (combined != Text("Hello")) << '\n';
    a = a; // self-assignment
}
