# Q1: Constructors and constructor overloading

- The default constructor is supplied only when no constructor is user-declared. Declaring any constructor suppresses implicit default-constructor generation.
- Member initializer lists directly initialize members; assignment in the body first default-constructs class-type members and then assigns them.
- Members initialize in declaration order, regardless of initializer-list order.
- Delegation funnels all validation through the full constructor, so the non-negative-copy rule is checked in one place.
- `explicit` prevents unintended implicit conversions for one-argument constructors.
- Array creation such as `Book books[3];` requires a usable default constructor for each element.
- Construction of each object takes O(1) time and O(1) per-object storage, excluding dynamic string storage.
- A single constructor with default arguments can cover the same cases, but overloads express distinct creation intent more clearly. Both approaches should centralize validation.
