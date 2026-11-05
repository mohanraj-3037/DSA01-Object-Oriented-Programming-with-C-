#include <iostream>
using namespace std;

void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}

int& bigger(int& p, int& q) {
    return p > q ? p : q;
}

void show(int x, int y = 5, int z = 10) {
    cout << x + y + z << ' ';
}

int main() {
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    cout << a << ' ' << b << ' ' << c << '\n';

    bigger(a, c) = 100;
    cout << a << ' ' << c << '\n';

    show(1);
    show(1, 2);
    show(1, 2, 3);
    cout << '\n';
}
