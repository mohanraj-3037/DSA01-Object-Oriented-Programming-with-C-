# A5 – Prediction, Verification and Checklist

## Pre-run prediction

Write the following before running the supplied `Guard` program:

```text
~f ~main caught 42
```

## Required explanation

- [ ] `Guard("main")` is constructed before calling `f()`.
- [ ] `Guard("f")` is constructed inside `f()`.
- [ ] `throw 42` starts exception propagation.
- [ ] The inner `Guard` is destroyed first.
- [ ] The outer `Guard` is destroyed while leaving the `try` block.
- [ ] `catch (int x)` handles the integer exception.
- [ ] `"not printed"` is skipped because normal execution does not resume after the throw.

## Verification record to complete locally

| Item | Record |
|---|---|
| Compiler and version | ______________________________ |
| Compile command | ______________________________ |
| Run command | ______________________________ |
| Predicted output (written before run) | `~f ~main caught 42` |
| Actual output | ______________________________ |
| Differences and explanation | ______________________________ |

## Design checklist

- [ ] Low-level detection layer is identified.
- [ ] Intermediate catch/log/rethrow layer is identified.
- [ ] Application-boundary reporting layer is identified.
- [ ] `throw;` is distinguished from `throw e;`.
- [ ] Stack unwinding is defined.
- [ ] Reverse destruction order is explained.
- [ ] `unique_ptr`, `vector` and file streams are given as RAII examples.
- [ ] The exact supplied-program output is predicted.
- [ ] The missing `"not printed"` output is explained.
- [ ] Manual cleanup alternative is shown.
- [ ] Time cost is compared fairly.
- [ ] Code-size and leak-path risks are discussed.

## Evidence expected by the assignment

The A5 evidence consists of the catch-and-rethrow design, the RAII/stack-unwinding explanation and the correct output prediction with reasoning. The Mermaid recovery flow is stored as `A5_Recovery_and_Unwinding.mmd` in this task folder.
