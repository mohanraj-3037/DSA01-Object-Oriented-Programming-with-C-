# A4 – Design the Exception Strategy
**Marks: 4 | Bloom level: K5 – Evaluate**

## Exact assessed requirements

### A4.1 Identify the errors – 2 marks
List every error specified by the assignment:
1. negative charges;
2. claim above cover;
3. unknown package;
4. missing patient record;
5. memory allocation failure.

Design a hierarchy of exception classes derived from `std::exception`, with examples such as `BillingError` and `ClaimError`.

### A4.2 Specify exceptions – 2 marks
- Decide which functions may throw.
- Decide which functions must never throw.
- Mark non-throwing functions `noexcept`.
- Explain why destructors should not throw.

### Required alternative analysis
Compare exceptions with return codes (`enum Status` or `bool` plus error message). Analyse normal-path time, error-path time, extra storage and the code needed to pass errors to callers.
