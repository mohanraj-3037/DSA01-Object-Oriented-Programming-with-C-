# Task 04 – Control Implicit Conversions

## Predicted output (before execution)

```text
3 3.5
C 68
1 true
s >= u
```

## Conversion analysis

1. `a / b` performs **integer division** because both operands are `int`. The result is `3`; it is then converted to `double` when stored in `c`. In the second expression, `static_cast<double>(a)` makes the division floating-point, producing `3.5`.
2. `'A' + 2` promotes the `char` to `int`, adds 2, then converts the result back to `char` for `ch`. In `ch + 1`, `ch` is promoted to `int`, so the numeric result is `68`.
3. Assigning integer `5` to `bool` converts every nonzero value to `true`. The default stream output is `1`; `std::boolalpha` prints `true`.
4. Comparing `int s = -1` with `unsigned int u = 1` converts `s` to unsigned. The converted value is a very large unsigned value, so `s < u` is false and the conditional expression prints `s >= u`. A compiler may warn about the signed/unsigned comparison.

## Safer alternatives

- Use `static_cast<double>(a) / b` when floating-point division is intended.
- Use explicit, range-checked conversions when narrowing a value.
- Use brace initialization, such as `int count{3};`. `int count{3.7};` is rejected because it narrows a `double` to `int`.
- Avoid comparing signed and unsigned values unless the conversion is deliberate and safe.

## Alternative concept and complexity

Writing conversions explicitly improves readability and makes intent visible. `static_cast` itself normally has no runtime cost for these arithmetic conversions. Brace initialization catches narrowing conversions at compile time. Time and storage remain O(1) for each scalar operation; the main benefit is correctness and diagnostics, not speed.

## Evidence

The program is compiled with warnings enabled. The signed/unsigned comparison may produce a warning, while the program's output remains as predicted.
