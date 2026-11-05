# Q6: Rules of operator overloading

- Operators that cannot be overloaded: `::`, `.`, `.*`, `?:`, and `sizeof`.
- Overloading cannot change precedence, associativity, or arity. At least one operand must be a user-defined type.
- `operator=` must be a member function.
- A friend is useful when a non-member needs private access or when the left operand is an external type, as with `std::ostream << Text`.
- The class owns a dynamic character array, so it implements destructor, copy constructor and copy assignment (Rule of Three).
- `+` concatenates into a new result. For lengths n1 and n2, it copies O(n1+n2) characters and allocates O(n1+n2) temporary/result storage.
- For `a+b+c`, the intermediate result is materialized conceptually; modern compilers may elide copies. A `std::string` implementation is safer and generally preferable.
- Self-assignment is explicitly guarded. Long and empty messages are supported by null-terminated allocation.
