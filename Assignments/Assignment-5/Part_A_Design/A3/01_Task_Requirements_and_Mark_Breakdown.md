# A3 – Design with Abstract Classes
**Marks: 5 | Bloom level: K5 – Evaluate**

## Exact assessed requirements

### A3.1 Payer interface – 3 marks
Design:
- an abstract class `Payer`;
- a pure virtual function `amountCovered(const Bill&)`;
- derived class `SelfPay`;
- derived class `Insurance` with a cover limit and co-payment percentage;
- derived class `GovernmentScheme` with fixed package rates.

### A3.2 Extension – 2 marks
Show how a new payer, such as a corporate tie-up, can be added without changing any existing class.

### Required alternative analysis
Compare the abstract payer hierarchy with function pointers or `std::function` policy objects:
- describe the alternative solution;
- compare time per call, O(1) for both;
- compare per-payer storage;
- explain how cover-limit data is stored in each design.

## Scope note

The brief does not define the exact co-payment convention, government package table, currency, or behaviour for an uncovered package. This answer states a clear illustrative policy assumption and marks it as an assumption rather than an assignment-mandated formula.
