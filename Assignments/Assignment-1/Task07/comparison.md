# Task 07: Procedural vs Object-Oriented Design

## Procedural implementation
`procedural.cpp` stores the balance in a variable and passes it by reference to `deductFare()`. The function checks the minimum-balance rule and updates the variable.

## OOP implementation
`oop.cpp` places the balance and payment operation inside `SmartCard`. The balance is private, so callers cannot directly overwrite it. `payFare()` is the controlled public interface.

## Comparison

| Aspect | Procedural | OOP |
|---|---|---|
| Main organization | Functions and data | Objects combining data and behaviour |
| Balance protection | Depends on disciplined function use | Private member enforces encapsulation |
| Reuse | Reuse functions | Reuse class instances and methods |
| Validation | In each function that modifies balance | Centralized in `SmartCard::payFare()` |
| Suitability as features grow | Can become harder to maintain | Easier to extend with card-specific behaviour |

## Invariant
A successful payment must leave at least 5000 paise (₹50.00). A failed payment must not change the balance. Both programs enforce this rule.

## Complexity
A single fare deduction takes O(1) time and O(1) extra space.
