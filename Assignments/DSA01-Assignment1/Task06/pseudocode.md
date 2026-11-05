# Task 06 – Design the Control Structures

## Standard algorithmic pseudocode

**Algorithm: COMPUTE-AND-PROCESS-FARES**

**Input:** Initial card balance in paise; a sequence of journeys, each containing a zone and a peak-hour flag.

**Output:** Fare or denial for each journey, and the remaining balance.

1. BEGIN
2. SET `balance` to 10000 paise.
3. FOR EACH journey in the journey sequence DO
   1. SET `baseFare` to 0.
   2. CASE OF journey zone:
      - Inner: SET `baseFare` to 1000.
      - Middle: SET `baseFare` to 2000.
      - Outer: SET `baseFare` to 3000.
      - OTHERWISE: mark journey invalid and CONTINUE to the next journey.
   3. SET `fare` to `baseFare`.
   4. IF journey is during peak hours THEN
      - SET `fare` to `fare + (fare * 20 / 100)` using integer paise.
   5. IF `balance - fare` is at least 5000 paise THEN
      - SET `balance` to `balance - fare`.
      - DISPLAY fare and remaining balance.
      ELSE
      - DISPLAY low-balance denial and unchanged balance.
4. END FOR
5. END

## Control-structure decisions

- Use `switch` for the finite `Zone` alternatives because each named zone maps to one base fare.
- Use `if-else` for peak surcharge and balance validation because each is a true/false decision.
- Use the conditional operator only for short value selection, not for multi-step fare logic.
- A range-based `for` loop is suitable when processing a known collection of journeys. A `while` loop is better when the number of journeys is not known in advance and input continues until a sentinel/EOF.
- Use `continue` to skip an invalid journey and `break` to leave a loop or switch when appropriate. Each `switch` case uses `break` to prevent fall-through.
- If no `switch` case matches, `default` handles the invalid zone. The program must not silently charge an arbitrary fare.

## Peak-hour boundary rule

Peak windows are `[08:00, 10:00)` and `[17:00, 20:00)`. Therefore 08:00 and 17:00 are peak, while exactly 10:00 and 20:00 are off-peak. The source code includes compile-time `static_assert` checks for these four boundaries.

## Expected execution output

```text
Fare Rs 10.00  balance Rs 90
Fare Rs 36.00  balance Rs 54
Denied (low balance)  balance Rs 54
```

## Alternative concept and complexity

The base fare can also be stored in a `constexpr` array and indexed by a validated zone value. Both a switch and array lookup are O(1). The array stores three `int` values (typically 12 bytes); exact size is `sizeof(BASE_PAISE)`. A switch avoids indexing and makes invalid-enum handling explicit. Adding a fourth zone requires adding a new enum value and corresponding switch case, or extending the array and ensuring the enum-to-index mapping remains correct.
