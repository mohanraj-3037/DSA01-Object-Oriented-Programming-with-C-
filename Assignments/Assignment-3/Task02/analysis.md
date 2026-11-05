# Q2: Copy constructors, shallow and deep copies

- A compiler-generated copy constructor copies each member. For a raw owning pointer, that copies only the address (shallow copy).
- Both objects then appear to own one allocation. Mutating through either alias affects the same data; both destructors may delete it, causing double-free/undefined behaviour.
- The deep-copy constructor allocates a new array and copies each element. Assignment first builds a replacement array, then releases old storage, and guards self-assignment.
- Rule of Three: if a class needs a destructor, copy constructor, or copy-assignment operator, it usually needs all three.
- Copy constructor situations: initialization from another object (`T b=a`), pass-by-value parameter, and return-by-value when copy elision does not apply.
- Passing by const reference avoids an object copy; passing by value invokes a copy (subject to elision/moves where applicable).
- Deep copy costs O(n) time and O(n) extra space. Shallow pointer copy is O(1) but unsafe for exclusive ownership.
- `std::vector<std::string>` follows Rule of Zero and already performs independent deep-copy semantics.
