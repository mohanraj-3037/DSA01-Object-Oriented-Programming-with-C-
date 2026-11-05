# Task 10: Expected vs Actual Results, Scale and Performance

## Expected vs actual

The fare program stores money as integer paise and calculates a fare using a fixed number of arithmetic and comparison operations. The compiled implementation should therefore produce the same fare for the same zone and time, regardless of the number of journeys processed.

The Phase 3 executable test suite reported **17/17 tests passed**. This is the recorded actual result for the included boundary and validation tests.

## Maximum-fare scale calculation

For a conservative upper-bound estimate, assume every journey is charged the maximum original fare of ₹30 plus the 20% peak surcharge:

- Maximum fare = ₹30 × 1.20 = ₹36 = 3,600 paise.
- 20,000 journeys: 20,000 × ₹36 = ₹7,20,000 (₹7.2 lakh).
- 500,000 journeys: 500,000 × ₹36 = ₹1,80,00,000 (₹1.8 crore).
- 3,000,000 journeys: 3,000,000 × ₹36 = ₹10,80,00,000 (₹10.8 crore).

The 3-million-journey total in paise is 10,800,000,000. A signed 32-bit `int` typically has a maximum of 2,147,483,647, so it cannot store this aggregate paise value. A signed 64-bit `long long` is appropriate.

## Data type recommendation

- Store an individual fare and card balance as `long long` integer paise.
- Store aggregate daily totals as `long long` integer paise.
- Do not use `float` or `double` for monetary calculations because many decimal fractions cannot be represented exactly in binary floating point.
- Use floating point only if a separate non-monetary calculation genuinely requires it, not as the stored money representation.

## Complexity

For one journey, fare lookup, peak-window check, arithmetic and balance validation each take constant time: **O(1)** time and **O(1)** extra space.

For `n` journeys processed one by one, total processing time is **O(n)**. If each journey is processed without retaining a history, extra working space remains **O(1)**. Storing all journey records would require **O(n)** space.

## Compiler warnings and validation

Compile with:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic fare.cpp -o fare
```
Warnings help reveal suspicious conversions, signed/unsigned comparisons, and other potential defects. A clean build does not replace boundary tests; both are required.
