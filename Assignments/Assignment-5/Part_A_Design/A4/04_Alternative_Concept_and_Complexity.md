# A4 – Alternative Concept and Complexity Analysis

## Alternative: return codes instead of exceptions

The application can return a status value from each operation. The status may be an enumeration such as:

```text
ENUM Status
    SUCCESS
    NEGATIVE_CHARGE
    CLAIM_ABOVE_COVER
    UNKNOWN_PACKAGE
    PATIENT_NOT_FOUND
    ALLOCATION_FAILURE
END ENUM
```

A function can return the status and write its result through an output parameter, or return a result structure containing both status and value.

### SIMATS-style pseudocode

```text
ALGORITHM ValidateClaim(Amount, Cover, ApprovedAmount)
    IF Amount < 0 THEN
        RETURN NEGATIVE_CHARGE
    END IF

    IF Cover < 0 THEN
        RETURN NEGATIVE_CHARGE
    END IF

    IF Amount > Cover THEN
        RETURN CLAIM_ABOVE_COVER
    END IF

    SET ApprovedAmount <- Amount
    RETURN SUCCESS
END ALGORITHM
```

### Caller using return codes

```text
ALGORITHM ProcessClaim(Amount, Cover)
    DECLARE PaidAmount AS REAL
    DECLARE Result AS Status

    SET Result <- ValidateClaim(Amount, Cover, PaidAmount)

    IF Result = SUCCESS THEN
        DISPLAY "Approved: ", PaidAmount
    ELSE
        DISPLAY "Claim rejected: ", Result
    END IF
END ALGORITHM
```

## Time complexity

For a fixed number of validation checks, both approaches perform O(1) work for one claim on the normal path. The assignment asks for a comparison of normal-path and error-path behaviour:

| Path | Exceptions | Return codes |
|---|---|---|
| Normal path | No exception is thrown; runtime cost is implementation-dependent and commonly avoids explicit status propagation at every caller | Each caller checks or propagates a status; fixed checks are O(1) |
| Error path | Throwing and handling requires exception propagation and stack unwinding; can be substantially more expensive | Returns a status and follows explicit branches; fixed checks are O(1) |
| Across `n` claims | O(n) if each claim has bounded validation work | O(n) if each claim has bounded validation work |

Big-O does not capture the constant overhead of exception propagation. The exceptional path can be much more expensive than an ordinary return, especially when many stack frames must be unwound.

## Extra space and code

### Exceptions
- An exception object and runtime bookkeeping are needed while an exception is active.
- Stack unwinding destroys automatic objects between the throw point and handler.
- Callers do not need to pass a status value through every intermediate function.
- A suitable outer handler can centralise reporting.

### Return codes
- Each result needs a status value.
- If the function also returns a calculated amount, it needs an output parameter or a result structure containing both status and value.
- Each caller must check the status or explicitly propagate it.
- Intermediate layers need code to forward failure information.
- A richer error message may require a string or error object, increasing result storage.

## Evaluation

Return codes are suitable when rejection is an expected, frequent result and the caller is expected to make a normal control-flow decision. Exceptions are useful for failures that should interrupt the normal operation and propagate to a layer able to handle them. The choice should be based on failure frequency, API clarity, recovery requirements and measured behaviour, not on the assumption that one technique is always faster.
