# A2 – Alternative Concept and Complexity Analysis

## Alternative: non-virtual `total()` and `dynamic_cast`

If `total()` were not virtual, the caller could inspect the dynamic type using `dynamic_cast` and then call the matching derived operation. This makes the type decision explicit in the caller.

### Conceptual pseudocode

```text
ALGORITHM CalculateBillUsingCasts(B)
    IF B can be converted to OutPatientBill POINTER THEN
        RETURN OutPatientBill-specific total
    ELSE IF B can be converted to InPatientBill POINTER THEN
        RETURN InPatientBill-specific total
    ELSE IF B can be converted to DayCareBill POINTER THEN
        RETURN DayCareBill-specific total
    ELSE IF B can be converted to EmergencyBill POINTER THEN
        RETURN EmergencyBill-specific total
    ELSE
        REPORT "Unsupported bill type"
    END IF
END ALGORITHM
```

This assumes the hierarchy is polymorphic, because `dynamic_cast` to a derived pointer requires a suitable polymorphic source type for run-time checked downcasting.

## Time comparison

Let `k` be the number of concrete bill types and `n` the number of bills.

| Operation | Virtual dispatch | Sequential `dynamic_cast` checks |
|---|---:|---:|
| One bill | One virtual call, O(1) | Up to `k` checked casts, O(k) |
| `n` bills | O(n) | O(nk) |
| If `k` is fixed | O(n) | O(n) asymptotically, with a larger type-check sequence possible |

The assignment specifically asks for the contrast of one virtual call versus up to `k` casts for `k` bill types. If the number of types is treated as a fixed constant, both complete traversals are linear in `n`, but the cast-based design has work that grows with the number of concrete types.

## Space comparison

- A polymorphic object commonly contains a hidden vptr. The exact size is implementation-dependent.
- The vtable is generally associated with the class implementation, not duplicated in full inside every object.
- `dynamic_cast` does not remove the need for polymorphic type information in this design.
- The cast-based approach may also require additional branch/control-flow code, but this is not a per-bill data field.

Do not claim an exact vptr size without measuring the target compiler and architecture.

## Evaluation

The `dynamic_cast` solution is useful when a caller genuinely needs type-specific behaviour that is not part of the common interface. It is not a good replacement for a virtual `total()` operation because it centralises knowledge of all derived types in the caller. When a new bill category is added, every relevant type-test chain must be reviewed. Virtual dispatch keeps the caller dependent on the abstraction.
