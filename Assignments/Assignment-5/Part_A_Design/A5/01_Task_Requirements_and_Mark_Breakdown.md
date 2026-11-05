# A5 – Design Recovery and Rethrowing
**Marks: 4 | Bloom level: K5 – Evaluate**

## Exact assessed requirements

### A5.1 Where to catch – 2 marks
Decide:
- where each exception is caught;
- where it is logged;
- where it is rethrown using `throw;`;
- where the program finally reports it to the user.

### A5.2 No leaks on errors – 2 marks
Explain:
- stack unwinding;
- how objects with destructors release memory and files when an exception passes through a function;
- how RAII provides cleanup.

### Required output prediction
Predict the exact output of the supplied `Guard` program before running it. Explain destructor order and why `"not printed"` never appears.

### Required alternative analysis
Compare RAII (`std::unique_ptr`, `std::vector`) with manual `delete` in every catch block. Analyse time, code size and the number of possible leak locations when new error paths are added.
