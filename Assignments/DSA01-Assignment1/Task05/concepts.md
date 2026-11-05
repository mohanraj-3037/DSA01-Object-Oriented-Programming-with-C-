# Task 05 – Write Correct Expressions with the Right Precedence

## Predicted output (before execution)

```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```

## Line-by-line explanation

1. `*` has higher precedence than `+`: `5 + (3 * 2) = 11`. Parentheses force `(5 + 3) * 2 = 16`.
2. `x++` yields the old value 5 and then increments `x` to 6. `++y` increments `y` from 3 to 4 and yields 4. Therefore `z = 5 + 4 = 9`; the printed values are `9 6 4`.
3. The conditional operator selects `x` because `6 > 4`, so it prints 6. `%` and `*` have equal precedence and associate left-to-right: `(6 % 4) * 2 = 4`.
4. Integer division truncates toward zero: `10 / 3 = 3` and `-10 / 3 = -3`. The remainder has the sign of the dividend: `10 % 3 = 1`, `-10 % 3 = -1`.
5. The loop uses `i = 0, 3, 6, 9`; `k = 0 + 3 + 6 + 9 = 18`.

## Metro fare expressions

```cpp
bool peak = (hour >= 8 && hour < 10) ||
            (hour >= 17 && hour < 20);
long long fare = baseFare;
if (peak) fare += fare * 20 / 100;
```

The intervals are half-open: 08:00 and 17:00 are peak; 10:00 and 20:00 are not. Parentheses make the two peak windows easy to read. The expression without parentheses is logically equivalent because `&&` binds more tightly than `||`, but is less clear.

A concession expression can be written as `fare -= fare * concessionPercent / 100;` after the policy percentage is confirmed. The assignment brief does not specify the concession percentage, so do not invent one in the implementation.

## Operators and safety

- `++i` increments before yielding the value; `i++` yields the old value and then increments.
- Do not write `i = i++`. It is confusing and can invoke undefined behavior in relevant language versions/contexts; use `++i` or `i += 1` as a separate statement.
- Compound assignment such as `fare += surcharge` updates the left operand. Use parentheses for clarity when expressions become complex.

## Alternative concept and complexity

A `bool peak[24]` lookup table can check a valid hour in O(1), just like the logical expression. It uses 24 boolean entries (commonly 24 bytes, though `sizeof(bool)` is implementation-defined). The logical expression uses constant space and is usually clearer for two simple ranges; the table can be convenient for irregular schedules.
