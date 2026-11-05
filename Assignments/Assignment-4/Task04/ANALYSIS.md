# Task 4 – Pointers to Derived Classes: Forensics

## 4.1 Defects
1. `rate()` in Account is non-virtual, so `Account*` calls the base implementation (static binding).
2. Account's destructor is non-virtual, so deleting a SeniorAccount through Account* is undefined behaviour. The SeniorAccount destructor may not run, leaking `history`.
3. `Account copy = SeniorAccount();` slices the derived object. Only its Account base subobject is copied; SeniorAccount-specific state and behaviour are lost.
4. The derived `rate()` hides the base method rather than overriding it.

## 4.2 Evidence
`defective_demo.cpp` isolates the intentionally defective example. Run with AddressSanitizer:
`g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer defective_demo.cpp -o defective`
The exact diagnostics depend on the compiler and runtime. Do not invent or paste expected sanitizer output as if it were measured. Undefined behaviour may not produce a consistent report.

## 4.3 Repair
`main.cpp` uses a virtual `rate()`, `override`, a virtual destructor, and `std::unique_ptr<Account>` in a vector. The output is:
`3.5`
`4`
`Sliced copy rate: 3.5`
The final line intentionally shows that copying into a base object still slices even after virtual functions are added. Prefer pointers/references for polymorphic use.

## 4.4 Prevention
- If a base class is used polymorphically, give it a virtual destructor.
- Mark intended overrides with `override` so signature mistakes are diagnosed.

## Prediction exercise
For the supplied code, output is `3.5 4.0 3.5` if the separator character literals are corrected to valid single-space characters. `p->rate()` is statically bound to Account::rate because it is non-virtual. `p->vrate()` dispatches at run time to SeniorAccount::vrate. `copy.vrate()` calls Account::vrate because `copy` is a sliced Account object.

## unique_ptr alternative and complexity
A vector of unique_ptr still processes n accounts in O(n), with O(n) container storage. Each element owns one heap object and the pointer has a small fixed overhead. Automatic destruction prevents forgotten deletes and the virtual destructor invokes derived cleanup. Smart pointers do not prevent slicing if code explicitly copies `*ptr` into a base object, and they do not make non-virtual functions polymorphic.
