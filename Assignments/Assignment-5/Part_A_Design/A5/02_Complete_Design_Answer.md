# A5 – Complete Design Answer

## 1. Purpose of recovery and rethrowing

Detecting an error is only the first part of reliable software. The program must decide which layer has enough information to respond. A low-level function may know that a claim exceeds cover, but it may not know how to communicate the failure to the end user. A higher layer may know the patient workflow and be able to report the failure clearly.

The design should therefore separate:
- detecting the failure;
- adding technical or business context;
- logging the event;
- deciding whether to recover or propagate;
- reporting a safe message at the application boundary.

## 2. A5.1 – Where to catch, log and rethrow (2 marks)

### 2.1 Three-layer handling strategy

| Layer | Responsibility | Catch/rethrow decision |
|---|---|---|
| Validation / repository / low-level service | Detect invalid amount, missing patient, unknown package, allocation failure | Throw a specific exception; do not print user-facing output |
| Billing / claim service | Add context such as operation name or safe claim reference | Catch only if useful context can be added; log once; use `throw;` to preserve the original exception |
| Application boundary / `main` | Decide final response and prevent an unhandled exception from terminating normal application flow | Catch known exceptions, report a safe message; optionally catch all remaining exceptions |

### 2.2 Example propagation sequence

Suppose a claim exceeds the policy's remaining cover:

1. `approveClaim()` compares the requested amount with available cover.
2. It detects the violation and throws `CoverageExceededError`.
3. `processClaim()` catches the error only if it can add useful context.
4. The service logs the claim-processing context.
5. The service uses `throw;` to rethrow the currently handled exception.
6. Stack unwinding destroys local automatic objects.
7. The application boundary catches the exception and displays a user-readable message.
8. The application records the failure outcome and does not mark the claim as paid.

### 2.3 Why `throw;` matters

Inside a catch handler:
- `throw;` rethrows the currently handled exception.
- It preserves the original exception object and its dynamic type.
- `throw e;` throws a new exception object based on the static type of `e`. If `e` is a reference to a base class and the original object is derived, the new object can be sliced.

For a logging-and-rethrow operation, use `throw;` when the intention is to propagate the same exception.

### 2.4 Avoid duplicate logging

A common design mistake is logging the same exception at every layer. If three functions catch and log the same error before rethrowing, one failure can create three nearly identical log entries.

A better policy is:
- lower layer: throw with a meaningful cause;
- intermediate layer: add context only when it adds value, and avoid duplicate log records;
- outer boundary: record the final failure once and report it.

If the assignment's supplied program explicitly prints a log at an intermediate layer, preserve that output for the required exercise. The production design should still define a consistent one-event logging policy.

### 2.5 Catch order

Catch more specific exception types before general base classes. For example:

```text
TRY
    CALL ProcessBilling()
CATCH CoverageExceededError
    HANDLE COVERAGE REJECTION
CATCH BillingError
    HANDLE OTHER BILLING FAILURE
CATCH std::exception
    HANDLE OTHER STANDARD FAILURE
CATCH ALL
    HANDLE UNKNOWN FAILURE
END TRY
```

A general handler placed before a derived exception handler would intercept the derived type first and make the more specific handler unreachable.

## 3. A5.2 – Stack unwinding and RAII (2 marks)

### 3.1 Stack unwinding

When a function throws an exception and no handler exists inside that function, the exception propagates to its caller. As scopes are exited, C++ destroys fully constructed automatic objects in reverse order of construction.

For example:

```text
main scope:
    construct Guard("main")
    call f()

f scope:
    construct Guard("f")
    throw exception
```

When the exception leaves `f`, the `Guard("f")` object is destroyed first. Then the exception leaves the `try` block in `main`, so `Guard("main")` is destroyed before the matching handler runs.

This reverse-order destruction is stack unwinding.

### 3.2 RAII principle

RAII means Resource Acquisition Is Initialization. An object acquires or takes ownership of a resource during construction and releases it in its destructor.

Examples:
- `std::unique_ptr<T>` owns a dynamically allocated object and deletes it when the owner is destroyed.
- `std::vector<T>` owns its dynamic storage and releases it when the vector is destroyed.
- `std::ifstream` and `std::ofstream` manage file handles and close them when the stream object is destroyed.
- `std::lock_guard` manages a mutex lock and unlocks it when the guard leaves scope.

The resource lifetime is tied to the owner's lifetime. Since destructors run during stack unwinding, resources are released even when a function exits because of an exception.

### 3.3 Why RAII is safer than manual cleanup

With manual allocation, every path after acquisition must release the resource:
- normal return;
- validation failure;
- exception from a later operation;
- early return;
- nested call failure.

If one path misses `delete` or `close`, a resource leak can occur. If cleanup is duplicated incorrectly, double deletion or use-after-free can occur.

RAII places cleanup in one owner object. The caller does not need to repeat cleanup in every catch block.

## 4. Required output prediction: supplied `Guard` program

### Predicted output before execution

```text
~f ~main caught 42
```

### Exact reasoning

1. `main()` enters the `try` block.
2. `Guard m("main")` is constructed. It is the first automatic object in this scope.
3. `f()` is called.
4. Inside `f()`, `Guard g("f")` is constructed.
5. `f()` executes `throw 42`.
6. There is no matching handler inside `f()`, so the exception begins propagating to `main()`.
7. The `f()` scope is exited. `g` is destroyed and prints `~f `.
8. The exception leaves the `try` block in `main()`. The local object `m` is destroyed and prints `~main `.
9. The matching `catch (int x)` handler executes and prints `caught 42`.
10. The statement `std::cout << "not printed ";` is after the call to `f()` in the `try` block. Since `f()` throws, normal execution never reaches that statement.
11. The newline is printed after the catch block.

### Why the destructor order is `~f` then `~main`

Objects are destroyed in reverse order of completed construction as their scopes are exited. `g` is constructed after `m`, and `g` belongs to the inner function scope, so it is destroyed first.

### Why `"not printed"` never appears

The throw interrupts normal sequential execution. The next control flow is exception propagation, not the next statement after `f()`. The matching handler is entered only after the relevant stack scopes have been unwound.

## 5. Design conclusion

A reliable C++ design uses typed exceptions to report exceptional failures, catches them at layers that can add value, rethrows the same exception when propagation is required, and relies on RAII owners to release resources automatically. This combination prevents error handling from becoming a second source of leaks.
