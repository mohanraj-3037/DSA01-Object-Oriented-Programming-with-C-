# A3 – Alternative Concept and Complexity Analysis

## Alternative: function pointer or `std::function` policy

Instead of defining a class for every payer, the application can store a callable policy object. The callable accepts a `Bill` and returns the amount covered.

Conceptual policy definitions:

```text
SelfPayPolicy(Bill)
    RETURN Bill.total()

InsurancePolicy(Bill, CoverLimit, CoPayPercent)
    DECLARE InsurerShare AS REAL
    SET InsurerShare <- Bill.total() * (1 - CoPayPercent)
    RETURN MIN(InsurerShare, CoverLimit)

GovernmentPolicy(Bill, PackageRateTable)
    LOOK UP Bill package code
    IF package is absent THEN
        REPORT unknown package
    END IF
    RETURN fixed package rate
```

A `std::function<double(const Bill&)>` can hold a lambda that captures policy data. A plain function pointer can also be used for stateless functions, but it cannot directly capture per-policy state. State would need to be passed separately or stored in an associated object.

## Time complexity

For one policy call, assuming the policy calculation itself is constant time:

| Design | Time per call |
|---|---:|
| Virtual `Payer::amountCovered()` call | O(1) dispatch |
| Function pointer call | O(1) invocation |
| `std::function` call | O(1) invocation in Big-O terms |

The actual constant overhead may differ. If a government scheme performs a lookup in a map with `m` package entries, that lookup is typically O(log m), and that cost applies regardless of whether the policy is represented by a class or callable.

## Per-payer storage

### Abstract class design
- An `Insurance` object stores its cover limit and co-payment percentage as member data.
- A `GovernmentScheme` object stores its package-rate mapping or a reference to shared rate data.
- A `CorporatePayer` stores its negotiated agreement data.
- A polymorphic object commonly has a hidden vptr; exact object layout is compiler-dependent.

### Callable design
- A stateless function pointer may require only the function pointer itself.
- A `std::function` wrapper stores a callable target. A lambda can capture the cover limit and co-payment percentage.
- The callable's captured state contributes to the wrapper's storage. Whether it uses small-object storage or dynamic allocation is implementation-dependent.
- A large package table should normally be shared or referenced rather than copied into every callable.

## Comparison table

| Evaluation | Abstract `Payer` | Function pointer / `std::function` |
|---|---|---|
| Call time | O(1) dispatch | O(1) invocation |
| Store insurance limit | Member field in `Insurance` | Captured value or external state |
| Store scheme rates | Member/shared data in scheme object | Captured/shared table |
| Add a payer | Add a derived class | Supply another callable policy |
| Type safety and organisation | Explicit named class and interface | Flexible but policy data may be separated from callable |
| Stateful policies | Natural object state | Lambda captures or separate state object |
| Extensibility | Clear class hierarchy | Easy to register/select callables |

## Evaluation

The class design is preferable when payer policies have meaningful identity, multiple state values, validation rules and behaviour that should remain together. `std::function` is attractive when the system needs configurable or dynamically selected policies and the callable abstraction is sufficient. Both can provide O(1) call overhead in Big-O terms; the design decision is primarily about ownership, state organisation, extension and maintainability.
