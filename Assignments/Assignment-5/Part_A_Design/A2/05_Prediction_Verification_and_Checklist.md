# A2 – Prediction, Verification and Checklist

## Pre-run prediction record

Write this prediction in your report before running the supplied program:

```text
500 ~OPBill ~Bill
```

## Explanation prompts

1. Which function is selected by the expression `b->show()` and why?
2. Which function is selected by the call to `total()` inside `show()` and why?
3. What is the static type of `b`?
4. What is the dynamic type of the object?
5. In which order do the destructors execute?
6. Why is deleting through `Bill*` unsafe if the base destructor is non-virtual?

## Verification record to complete locally

| Item | Record |
|---|---|
| Compiler and version | ______________________________ |
| Compile command | ______________________________ |
| Run command | ______________________________ |
| Actual output | ______________________________ |
| Sanitizer diagnostic | ______________________________ |
| Difference from prediction | ______________________________ |
| Explanation using C++ rules | ______________________________ |

## Submission checklist

- [ ] Explain early and late binding using `Bill*`.
- [ ] Include conceptual tables for `Bill`, `OutPatientBill` and `InPatientBill`.
- [ ] Include the `b->total()` dispatch path.
- [ ] Explain the non-virtual `show()` / virtual `total()` sequence.
- [ ] Explain why a virtual destructor is required.
- [ ] Give the predicted output before running.
- [ ] Explain undefined behaviour after removing the virtual destructor.
- [ ] Run the modified program with AddressSanitizer and record actual evidence.
- [ ] Include the `dynamic_cast` alternative.
- [ ] Compare one virtual call with up to `k` casts.
- [ ] Discuss vptr storage without inventing a fixed byte size.
