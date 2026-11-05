# A5 – Alternative Concept and Complexity Analysis

## Alternative: manual `delete` in every catch block

Without RAII, a function may allocate resources manually and then release them in every possible exit path.

### Conceptual pseudocode

```text
ALGORITHM ProcessWithManualResource()
    DECLARE ResourcePointer

    SET ResourcePointer <- ALLOCATE RESOURCE

    TRY
        CALL FirstOperation()
        CALL SecondOperation()
        RELEASE ResourcePointer
        RETURN SUCCESS

    CATCH ErrorA
        RELEASE ResourcePointer
        RETHROW

    CATCH ErrorB
        RELEASE ResourcePointer
        RETHROW

    CATCH ALL
        RELEASE ResourcePointer
        RETHROW
    END TRY
END ALGORITHM
```

This pseudocode demonstrates the repetition. Every new catch branch and every early-return path must be reviewed to ensure that the resource is released exactly once.

## RAII alternative

```text
ALGORITHM ProcessWithRAII()
    DECLARE ResourceOwner AS UNIQUE_OWNER
    INITIALIZE ResourceOwner WITH RESOURCE

    CALL FirstOperation()
    CALL SecondOperation()

    RETURN SUCCESS
    // When scope exits normally or by exception,
    // ResourceOwner destructor releases the resource.
END ALGORITHM
```

## Time complexity

For one resource, both manual release and RAII destruction perform the underlying resource-release operation. The asymptotic release time is the same for the same resource:

| Measure | Manual cleanup | RAII |
|---|---|---|
| Release one resource | O(1) for a constant-time release | O(1) for the same release |
| Release `r` independent resources | O(r) | O(r) |
| Additional cleanup work | Repeated cleanup branches | Destructors run automatically |
| Error-path traversal | Handler must perform cleanup | Stack unwinding invokes destructors |

For containers, destruction may be proportional to the number of elements if each element has non-trivial destruction. The key comparison is not that RAII makes destruction magically faster; it makes cleanup systematic and exception-safe.

## Code size and leak opportunities

Manual cleanup requires a cleanup statement for each resource on every exit path. If there are `r` resources and `p` independent exit paths, the cleanup obligations can grow with the combinations of resources and paths. This is not a universal exact formula for source lines, but it explains why the maintenance burden can grow rapidly.

RAII generally centralises each resource's release logic in its owner. Adding a new error path does not require adding another `delete` for every existing owner.

The number of leak locations is not a fixed number independent of the program. It depends on the number of acquired resources and the number of paths that can leave before manual cleanup. A new error path creates another place that must be audited. With RAII, that new path still exits the scope and triggers the existing destructors.

## Comparison table

| Evaluation | Manual `delete` / `close` | RAII (`unique_ptr`, `vector`, streams) |
|---|---|---|
| Underlying release time | Same resource-specific cost | Same resource-specific cost |
| Normal path | Explicit cleanup required | Destructor cleanup on scope exit |
| Exception path | Every handler must clean up correctly | Stack unwinding invokes destructors |
| New error branch | Must add/check cleanup | Existing owners clean up automatically |
| Common failure risks | Leak, double delete, dangling pointer | Incorrect ownership design or misuse of non-owning references |
| Code organisation | Cleanup scattered across paths | Cleanup localised in resource-owning type |

## Evaluation

RAII is the preferred C++ design because it makes resource lifetime follow object lifetime. It reduces the number of manually maintained cleanup paths and is naturally compatible with exception propagation. Manual resource management may still be required for low-level APIs, but ownership should be wrapped in an RAII object as soon as practical.
