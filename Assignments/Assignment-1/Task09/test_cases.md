# Task 09: Fare Logic Test Plan

## Assumptions
- Inner/Middle/Outer base fares are ₹10/₹20/₹30.
- Peak surcharge is 20%.
- Peak windows are start-inclusive and end-exclusive: 08:00–09:59 and 17:00–19:59.
- A journey is accepted only when the balance after deduction is at least ₹50.
- Money is stored as integer paise.

## Boundary and validation tests

| Test | Input / condition | Expected |
|---|---|---|
| Morning start | 08:00 | Peak |
| Morning end | 10:00 | Off-peak |
| Evening start | 17:00 | Peak |
| Evening end | 20:00 | Off-peak |
| Exact minimum | ₹80 balance, ₹30 fare | Accept, ₹50 remains |
| Below minimum | ₹79.99 balance, ₹30 fare | Deny |
| Negative balance | -1 paise | Invalid |
| Negative fare | -1 paise | Invalid |
| Invalid hour | 24 | Reject |
| Five journeys | See executable scenario | Five accepted; ₹132 remains |

## Executable test
Compile and run `fare_tests.cpp`. Each case prints `[PASS]` or `[FAIL]`; the process returns exit code 0 only when all tests pass.
