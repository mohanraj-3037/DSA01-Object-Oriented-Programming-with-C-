# Task 11: Final Design Recommendation

## Recommendation

Use an object-oriented design with a `SmartCard` class for protected balance management and a separate fare-calculation component driven by a fare table. Keep the business rules deterministic and explicit.

## Proposed responsibilities

1. **Fare table:** maps each strongly typed zone to its base fare in integer paise. Adding a zone means adding a fare-table entry rather than expanding a long chain of fare literals.
2. **Fare calculator:** applies the time-based peak rule and any eligible concession/discount in a documented order.
3. **SmartCard:** owns a private balance and exposes controlled operations such as `payFare()` and `getBalance()`.
4. **Pass:** represents a valid monthly pass and the two zones it covers. A matching journey is covered without deducting a per-journey fare.
5. **Input/output layer:** validates user input and formats paise as rupees for display.

## Why this design

- Encapsulation protects the card balance from arbitrary external changes.
- `enum class` prevents unrelated integer values from being used as zone names.
- Integer paise avoids floating-point rounding errors in money.
- A fare table is easier to extend when Airport or future zones are introduced.
- Separating fare calculation from payment makes each rule easier to test.
- Unit tests can cover time boundaries, discounts, pass eligibility, and the minimum-balance invariant independently.

## Invariants

- A card balance must never become negative.
- A charged journey is accepted only if at least ₹50 remains after payment.
- A pass covers only its selected zones and has no per-journey fare deduction.
- A weekend discount and peak surcharge must not be combined; the weekend rule takes precedence.
- Invalid zone/time inputs must be rejected rather than silently charged.

## Conclusion

A table-driven fare calculator combined with encapsulated `SmartCard` and `Pass` classes is more maintainable and testable than placing all rules in one large `switch` statement. Keep the fare rules deterministic; external AI recommendations must never be allowed to directly change balances or bypass validation.
