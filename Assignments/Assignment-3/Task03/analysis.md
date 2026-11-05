# Q3: Dynamic constructors and destructors

- The constructor allocates a row-pointer array and then one character array per row. Each seat starts as `O` (open).
- The destructor releases each row with `delete[]`, then releases the row-pointer array with `delete[]`.
- Local objects are destroyed in reverse construction order at scope exit. Block-local objects are destroyed at block exit. Heap objects remain alive until `delete`.
- Forgetting `delete` leaks the object and its allocations. Using `delete` instead of `delete[]` for an array is undefined behaviour.
- A destructor has no parameters and no return type, so it cannot be overloaded.
- Access is O(1). A row-pointer design performs rows + 1 allocations. A single contiguous block needs one allocation and has simpler locality; a vector-of-vectors typically performs one outer and one allocation per row.
- Memory for a 2D map is approximately rows*seats bytes plus rows*sizeof(char*) for row pointers, allocator overhead excluded.
- RAII binds resource release to object lifetime, including early returns and exceptions.
