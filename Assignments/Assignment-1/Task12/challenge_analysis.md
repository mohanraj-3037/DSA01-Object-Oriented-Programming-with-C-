# Task 12: Day-4 Challenge and Impact Analysis

## New requirements
- Add an Airport zone with a base fare of ₹60.
- Apply a 10% weekend discount.
- The weekend discount must not combine with the 20% peak surcharge.
- Add a monthly pass for unlimited journeys in two selected zones.

## Rule precedence and fare outcomes

The implementation uses this order:
1. Validate zone and hour.
2. If the journey is covered by an active monthly pass, accept it with zero per-journey fare.
3. Otherwise, calculate the fare. On weekends, apply the 10% discount and do not apply peak surcharge. On weekdays, apply the 20% surcharge only during peak windows.
4. Ask `SmartCard` to deduct the fare. Reject if the resulting balance would be below ₹50.

Airport examples:
- Weekday off-peak: ₹60.00.
- Weekday peak: ₹60 × 1.20 = ₹72.00.
- Weekend off-peak: ₹60 × 0.90 = ₹54.00.
- Weekend during a peak clock hour: ₹54.00, because weekend discount takes precedence and the two adjustments do not combine.

## Impact on the original design

### Replacing the switch statement
A `switch` is clear for three fixed zones, but every new zone requires editing the switch. The fare table stores zone, display name, and fare together. Adding Airport requires a new table entry, reducing the risk of updating one switch but forgetting another.

### SmartCard
`SmartCard` keeps its balance private and checks the ₹50 minimum before any deduction. The rest of the program cannot directly modify the balance.

### Pass
`Pass` stores two selected zones and whether the pass is active. It covers unlimited journeys in those zones for the modeled validity period. This small assignment model does not implement calendar dates, renewal, or expiry timestamps; those would be required in a production monthly-pass system.

## Rounding and money
All fares and balances are integer paise. Percentage calculations use integer arithmetic and round to the nearest paise. The Airport calculations produce exact whole-paise values.

## Validation
`final_fare_system.cpp` demonstrates the four Airport fare outcomes, a covered journey, and a charged Airport journey. The accompanying test program checks the new rules and card invariants.
