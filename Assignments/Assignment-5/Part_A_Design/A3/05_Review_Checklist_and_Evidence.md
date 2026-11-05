# A3 – Review Checklist and Evidence

## Design checklist

- [ ] `Payer` is abstract.
- [ ] `amountCovered(const Bill&)` is pure virtual.
- [ ] A virtual destructor is included.
- [ ] `SelfPay` is described as covering the full bill.
- [ ] `Insurance` stores a cover limit.
- [ ] `Insurance` stores a co-payment percentage.
- [ ] The meaning of the co-payment percentage is explicitly stated.
- [ ] The cover-cap rule is explained.
- [ ] `GovernmentScheme` uses fixed package rates.
- [ ] No unsupported real-world package rate is invented.
- [ ] `CorporatePayer` is added as a new subclass.
- [ ] Existing payer classes remain unchanged in the extension explanation.
- [ ] The UML includes all required payer classes and their inheritance.
- [ ] The dependency on `Bill` is shown.
- [ ] Function pointer / `std::function` alternative is explained.
- [ ] O(1) time per call is stated for both designs.
- [ ] Per-payer storage and cover-limit storage are compared.

## Evidence expected by the assignment

The A3 design evidence consists of the abstract payer interface, derived class design and demonstrated extension path. The class diagram is included as `A3_Payer_Hierarchy.mmd` in this task folder.
