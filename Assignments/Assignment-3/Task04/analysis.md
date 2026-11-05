# Q4: Arithmetic and stream operators

- Store money as integer paise to avoid binary floating-point rounding in routine currency arithmetic.
- `+` returns a new value and leaves operands unchanged. `+=` mutates the left operand and returns `Money&` to support chaining without copying.
- `<<` is a non-member because its left operand is `std::ostream`; it is a friend to access the private paise value. `>>` follows the same stream convention.
- `a + b` is translated to `a.operator+(b)` for a member overload.
- The sample normalizes values through total paise. Negative values are allowed in this implementation; a production billing system may reject negative balances at input/business-rule boundaries.
- Multiplying Money by Money is not generally meaningful because the unit becomes currency-squared. Multiplication by a scalar can be meaningful.
- All arithmetic/comparison operations shown are O(1) time and O(1) extra space.
- A non-member overload can support symmetric conversions such as `100 + m` when a suitable converting constructor is available; a member overload naturally supports `m + 100`.
