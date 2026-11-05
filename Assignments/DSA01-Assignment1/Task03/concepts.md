# Task 03 – Data Types and Type Compatibility

## Recommended data types

| Value | Recommended type | Reason |
|---|---|---|
| Card balance and fare | `long long` | Stores integer paise exactly and provides a large positive range. |
| Journey count | `long long` | Safely supports growth in processed journey counts. |
| Hour (0–23) | `int` | Small signed whole-number range is sufficient. |
| Zone | `enum class Zone` | Restricts values to named zone enumerators. |
| Peak/concession eligibility | `bool` | Represents true or false. |
| Single character input | `char` | Represents one character. |
| Display-only rupee ratio | `double` | Useful for non-authoritative display or analysis, not balance storage. |
| Fixed fare constants | `constexpr long long` | Typed compile-time constants in paise. |

The exact `sizeof` values are implementation-dependent. On the compiler used for the captured run, `bool` and `char` are 1 byte, `int` and `float` are 4 bytes, and `long long` and `double` are 8 bytes. Record the values from your own compiler in the submitted report.

## Why integer paise?

Binary floating-point cannot represent every decimal fraction exactly. Repeated additions and percentage calculations using `double` can therefore produce small representation errors. Integer paise represents every whole-paise amount exactly. For the current 20% surcharge, calculate with integer arithmetic: `baseFarePaise * 120 / 100`. The chosen fare values are divisible appropriately, so the result is an exact number of paise.

## Type compatibility

In an expression containing an `int` and a `double`, the `int` is converted to `double` before arithmetic. For example, `7 / 2.0` evaluates to `3.5`. In contrast, `7 / 2` performs integer division first and evaluates to `3`; assigning that result to a `double` does not restore the lost fraction. A `bool` converted to an integer becomes `0` or `1`; a nonzero integer converted to `bool` becomes `true`.

Use explicit casts when a conversion is intentional, and avoid mixing signed and unsigned values without checking their ranges.

## Range and network-scale collection

The program prints `INT_MAX` and `LLONG_MAX` from `<climits>`. With the assignment's largest original fare after the peak surcharge, the fare is ₹36 = 3,600 paise. If 3,000,000 journeys all paid this fare, the total would be 10,800,000,000 paise. This is greater than the common 32-bit `int` maximum of 2,147,483,647, so a 32-bit `int` is not sufficient for the total. `long long` is the appropriate accumulator.

## Alternative: `double` rupees

A `double` rupee balance uses 8 bytes on the tested compiler, the same storage size as `long long`, and addition is O(1) for either type. However, binary floating-point represents many decimal fractions approximately. Integer paise is exact for whole-paise amounts. The implementation therefore uses `long long` for authoritative money values and formats paise as rupees only when displaying results.
