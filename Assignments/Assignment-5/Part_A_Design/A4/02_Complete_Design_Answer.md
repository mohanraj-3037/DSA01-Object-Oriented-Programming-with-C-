# A4 – Complete Design Answer

## 1. Purpose of the exception strategy

The billing application must reject invalid claims with clear reasons and must not lose bills because an error occurs. An exception strategy gives failures a defined representation and a controlled path from the point of detection to a layer that can report or recover.

The design should distinguish:
- invalid input or business-rule violations;
- missing domain data;
- resource failures;
- normal business outcomes.

A rejected claim is not a successful payment. It should not be represented by a plausible-looking bill total.

## 2. A4.1 – Error catalogue (2 marks)

The assignment explicitly names five error conditions.

| No. | Error condition | Suggested exception | Why this exception is suitable |
|---:|---|---|---|
| 1 | Negative charge | `InvalidChargeError` | The amount violates the billing input rule |
| 2 | Claim above insurance cover | `ClaimError` or `CoverageExceededError` | The claim violates the policy's coverage constraint |
| 3 | Unknown package | `UnknownPackageError` | The requested government package code cannot be found |
| 4 | Missing patient record | `PatientNotFoundError` | The required patient entity does not exist |
| 5 | Memory allocation failure | `std::bad_alloc` | This is the standard exception used by C++ allocation operations |

### 2.1 Proposed custom hierarchy

A practical hierarchy is:

- `std::exception`
  - `std::runtime_error`
    - `BillingError`
      - `InvalidChargeError`
      - `ClaimError`
        - `CoverageExceededError`
      - `UnknownPackageError`
      - `PatientNotFoundError`
  - `std::bad_alloc` (standard library branch, separate from the custom billing branch)

This keeps domain-specific errors under a common `BillingError` category. A caller can catch one `BillingError` when it wants to handle any known billing-domain problem, or catch a more specific derived type when it needs different recovery behaviour.

`std::bad_alloc` should not be forced into the custom hierarchy. It is already part of the standard exception hierarchy and represents a resource-allocation failure rather than a billing-rule failure.

### 2.2 What information should an exception carry?

An exception message should explain the reason, not expose unnecessary private patient information. Useful context may include:
- the field or rule that failed;
- a safe bill or claim reference;
- the invalid value, if it is safe and useful to report;
- the expected constraint.

Examples of clear messages:
- `"negative charge"`
- `"claim exceeds available cover"`
- `"unknown package code"`
- `"patient record not found"`

The assignment's example messages can be retained for the corresponding program outputs. Production messages may add safe identifiers and context.

## 3. A4.2 – Decide which functions may throw and which must not (2 marks)

### 3.1 Functions that may throw

| Function category | Possible failure | Design decision |
|---|---|---|
| Bill constructor / charge validation | Negative or invalid amount | May throw `InvalidChargeError` |
| Insurance claim approval | Claim exceeds cover | May throw `CoverageExceededError` |
| Government package lookup | Package not found | May throw `UnknownPackageError` |
| Patient repository lookup | Patient missing | May throw `PatientNotFoundError` |
| Numeric parsing | Invalid text or out-of-range number | Standard conversion exceptions may propagate |
| Dynamic allocation / container growth | Allocation failure | May throw `std::bad_alloc` |

A function should throw only when it cannot fulfil its documented operation. It should not print an error and continue with an invalid value.

### 3.2 Functions that should not throw

Destructors and cleanup operations should not allow exceptions to escape. A destructor's job is to release resources owned by the object. Throwing from a destructor is especially dangerous during stack unwinding.

Examples of operations that should be non-throwing when correctly designed:
- destructors;
- resource release;
- simple state-reset operations;
- logging fallback/cleanup paths where failure cannot be propagated safely.

Mark a function `noexcept` only when its implementation and all operations it calls can honour that promise. `noexcept` is a contract: if an exception escapes a `noexcept` function, C++ calls `std::terminate`.

### 3.3 Why destructors should not throw

When an exception is thrown, C++ starts stack unwinding and destroys automatic objects as their scopes are exited. If a destructor throws another exception while an earlier exception is already being unwound, the program cannot safely continue normal exception propagation and calls `std::terminate`.

Therefore:
- destructors should perform cleanup;
- destructors should not report recoverable business errors by throwing;
- if cleanup can fail, the design should handle that failure internally or expose an explicit operation that can report failure before destruction.

### 3.4 Exception specification examples

| Function | Suggested exception contract | Reason |
|---|---|---|
| `Bill::total()` | May throw if calculation depends on validated external state; otherwise document non-throwing behaviour | Depends on implementation |
| `validateCharge()` | May throw `InvalidChargeError` | Invalid input is exceptional |
| `findPatient()` | May throw `PatientNotFoundError` | Lookup may fail |
| `findPackage()` | May throw `UnknownPackageError` | Package may not exist |
| `approveClaim()` | May throw `CoverageExceededError` | Policy rule may reject claim |
| `~Bill()` | `noexcept` | Destruction must not propagate exceptions |
| `~Payer()` | `noexcept` | Same resource-safety requirement |
| resource-release helper | `noexcept` where possible | Cleanup must be safe during unwinding |

The exact specification should match the actual implementation. It is incorrect to mark a function `noexcept` merely to make the interface look complete if it calls operations that may throw.

## 4. Exception propagation model

1. Validate user input near the boundary.
2. Throw a specific exception at the point where the invalid condition is detected.
3. Allow the exception to propagate until a layer can add useful context or recover.
4. Catch the specific type before a more general base type.
5. Report a safe and understandable message at the application boundary.
6. Ensure RAII objects release resources during propagation.

This is expanded in A5, which focuses on where to catch, log and rethrow.

## 5. Design conclusion

A typed exception hierarchy makes failure causes explicit and allows callers to handle errors at an appropriate level. The design keeps business errors distinct from standard resource failures and treats destructors as non-throwing cleanup operations.
