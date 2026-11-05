# A2 – Understand Runtime Binding
**Marks: 5 | Bloom level: K5 – Evaluate**

## Exact assessed requirements

| Subtask | Marks | Required response |
|---|---:|---|
| A2.1 Early and late binding | 2 | Explain compile-time and run-time binding using a call through a `Bill` pointer |
| A2.2 Virtual table | 2 | Draw conceptual vtables for `Bill`, `OutPatientBill` and `InPatientBill`; show how `b->total()` reaches the correct function |
| A2.3 Virtual destructors | 1 | Explain why `Bill` must have a virtual destructor |

The task also requires:
- predict the exact output of the supplied `Bill` / `OPBill` program before execution;
- explain how non-virtual `show()` reaches `OPBill::total()`;
- remove `virtual` from `~Bill`, predict the changed behaviour and verify with `-fsanitize=address`;
- compare virtual dispatch with type testing using `dynamic_cast`;
- compare one virtual call with up to `k` casts for `k` bill types and discuss vptr storage.

## Source program details

The supplied program:
- constructs an `OPBill` dynamically;
- stores its address in a `Bill*`;
- calls `b->show()`;
- deletes the object through `Bill*`;
- prints destructor messages from `OPBill` and `Bill`.

Do not confuse the static type of the pointer (`Bill*`) with the dynamic type of the object (`OPBill`).
