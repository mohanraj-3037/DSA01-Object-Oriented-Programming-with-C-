# Q6 Analysis

A friend function is not a member, so it is called as `minutesBetween(a,b)`, not `a.minutesBetween(b)`. It can access private members because the class explicitly grants friendship. A member function has an implicit `this` object and can access its own private state.

Friend functions are justified when an operation naturally treats two objects symmetrically. Member functions/getters offer tighter encapsulation and can be preferable if the operation conceptually belongs to one object. Making fields public weakens invariants.

`inline` permits multiple identical definitions under the One Definition Rule and may encourage inlining, but it does not force the compiler to substitute the function body. Compare actual timings at `-O0` and `-O2`; optimisation may inline either function and benchmark results vary by machine/compiler.
