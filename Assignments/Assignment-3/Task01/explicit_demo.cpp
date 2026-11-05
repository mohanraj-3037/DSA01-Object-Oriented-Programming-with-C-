#include <string>
class Book {
public:
    explicit Book(const std::string&) {}
};
void registerBook(Book) {}
int main() {
    // registerBook("Dune"); // Does not compile: explicit blocks implicit conversion.
    registerBook(Book("Dune")); // OK: direct construction.
}
