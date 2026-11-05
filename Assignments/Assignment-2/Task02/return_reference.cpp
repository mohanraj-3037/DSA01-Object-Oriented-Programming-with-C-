#include <iostream>
using namespace std;

int& highest(int marks[], int n) {
    int index = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[index]) index = i;
    return marks[index];
}

int* highestPointer(int marks[], int n) {
    int index = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[index]) index = i;
    return &marks[index];
}

int highestIndex(const int marks[], int n) {
    int index = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[index]) index = i;
    return index;
}

// Deliberately unsafe demonstration: compiler should warn.
// Do not call this function or dereference its result.
int& danglingReference() {
    int local = 42;
    return local;
}

int main() {
    int marks[] = {75, 90, 85, 95, 80};
    highest(marks, 5) += 2;

    cout << "Marks after moderation: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    int idx = highestIndex(marks, 5);
    cout << "Highest via index: " << marks[idx] << " at " << idx << '\n';

    int* ptr = highestPointer(marks, 5);
    cout << "Highest via pointer: " << *ptr << '\n';
}
