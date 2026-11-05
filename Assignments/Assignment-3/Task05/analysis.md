# Q5: Increment, comparison and subscript operators

- Prefix `++x` calls `operator++()`; postfix `x++` calls `operator++(int)`. The dummy int distinguishes the overload.
- Prefix mutates and returns a reference to the updated object. Postfix saves and returns the old value, requiring a copy.
- A non-const `operator[]` returns `T&` so callers can modify an element. The const overload returns `const T&` and prevents mutation through a const playlist.
- This implementation throws `std::out_of_range` on invalid access. The task's prompt also allows a printed error policy; throwing is a safer library-style alternative.
- Access is O(1); the range check adds one comparison. Prefix is O(1) with no copy; postfix is O(1) with one object copy.
- The Time example uses seconds since midnight and wraps after 24 hours. It naturally handles 59:59 -> 1:00:00.
