# A2 – Complete Design Answer

## 1. Why runtime binding is needed

A `Bill*` pointer is declared using the base-class type, but it can point to an object of any concrete class derived from `Bill`. The compiler knows the pointer's static type, but the object it refers to at run time may be an `OutPatientBill`, `InPatientBill`, `DayCareBill` or `EmergencyBill`.

When the called member is virtual, C++ chooses the final overrider belonging to the object's dynamic type. This is the mechanism that allows one interface to support multiple implementations.

## 2. A2.1 – Early binding and late binding (2 marks)

### Early binding (compile-time binding)

Early binding means the function to call is determined using information available at compile time. For an ordinary non-virtual member function, the compiler selects the member according to the expression's static type.

If `show()` is non-virtual and the expression is `b->show()` where `b` has type `Bill*`, the selected function is `Bill::show()`.

### Late binding (run-time binding)

Late binding applies to virtual functions. The call is resolved using the dynamic type of the object.

If `total()` is virtual and `b` points to an `OPBill`, then:

```text
Bill* b = address of an OPBill object
b->total()
```

invokes `OPBill::total()`, not a generic base implementation.

### Comparison

| Point | Early binding | Late binding |
|---|---|---|
| Decision time | Compile time | Run time |
| Main basis | Static type of expression | Dynamic type of object |
| Typical member | Non-virtual function | Virtual function |
| Flexibility | Call target is fixed by static type | Derived override can be selected |
| Billing example | `b->show()` selects `Bill::show()` if `show()` is non-virtual | `b->total()` selects `OPBill::total()` if the object is an `OPBill` |

### Static type versus dynamic type

- Static type of `b`: `Bill*`.
- Dynamic type of the object pointed to by `b`: `OPBill`.
- `virtual` makes the call use the dynamic type for final overrider selection.

## 3. A2.2 – Conceptual virtual tables and dispatch (2 marks)

### What is a vtable?

A vtable is a common implementation technique used by C++ compilers to support virtual dispatch. Conceptually, it is a table of function entries associated with a polymorphic class. A polymorphic object commonly contains a hidden pointer (`vptr`) that allows the run-time system to find the appropriate table.

Important language-law point: the C++ standard specifies virtual-function behaviour, not a mandatory vtable layout. Slot order, object layout, vptr placement and implementation details are compiler-specific. Therefore, the diagram is a conceptual teaching model.

### Conceptual entries

| Class table | `total()` entry | `type()` entry | Destructor entry |
|---|---|---|---|
| `Bill` | Pure virtual / no concrete base implementation | Pure virtual / no concrete base implementation | `Bill::~Bill()` |
| `OutPatientBill` | `OutPatientBill::total()` | `OutPatientBill::type()` | `OutPatientBill::~OutPatientBill()` |
| `InPatientBill` | `InPatientBill::total()` | `InPatientBill::type()` | `InPatientBill::~InPatientBill()` |

### Dispatch sequence for `b->total()`

1. The program evaluates the pointer `b`.
2. The object referred to by `b` is an `OutPatientBill`.
3. Because `total()` is virtual, dispatch uses the object's dynamic type.
4. The final overrider for `OutPatientBill` is selected.
5. `OutPatientBill::total()` executes and returns the out-patient total.

The flow diagram and class-specific conceptual tables are in `A2_Virtual_Dispatch.mmd` in this folder.

## 4. Why non-virtual `show()` can reach `OPBill::total()`

This is a two-stage call:

1. `b->show()` is a call to a non-virtual member. The static type of `b` is `Bill*`, so `Bill::show()` is selected.
2. Inside `Bill::show()`, the expression `total()` is a separate call. Since `total()` is virtual, that inner call is dispatched using the dynamic type of the object. The object is an `OPBill`, so `OPBill::total()` runs.

Therefore, a non-virtual function can call a virtual function. The caller's own binding mode does not change the binding mode of the separate virtual call made inside its body.

## 5. A2.3 – Why `Bill` needs a virtual destructor (1 mark)

The program allocates an `OPBill` object but stores its address in a `Bill*` and deletes through that pointer.

When a derived object is deleted through a pointer to its base class, the base class must have a virtual destructor for defined behaviour. With a virtual destructor, destruction proceeds from the most-derived object toward its base classes:

```text
OPBill::~OPBill()
Bill::~Bill()
```

This ensures derived-class resources are released before the base subobject is destroyed.

If `Bill::~Bill()` is not virtual, deleting an `OPBill` through `Bill*` has undefined behaviour. The program must not rely on a particular output. A sanitizer may report a problem, but the exact diagnostic depends on compiler, sanitizer runtime and platform. The absence of a diagnostic does not make the program defined.

## 6. Required output prediction

### Predicted output before execution

```text
500 ~OPBill ~Bill
```

### Reason

- `b->show()` calls `Bill::show()`.
- `Bill::show()` calls virtual `total()`.
- The object is an `OPBill`, so the total returned is `500`.
- `show()` prints the number followed by a space.
- `delete b` invokes the virtual destructor chain.
- `OPBill::~OPBill()` prints `~OPBill `.
- `Bill::~Bill()` prints `~Bill `.
- `main` prints a newline.

The destructor order is derived first, base second.

### If `virtual` is removed from `~Bill`

The expression `delete b` attempts to delete a derived object through a base pointer whose destructor is non-virtual. This is undefined behaviour. Do not state that the only possible output is `500 ~Bill`, even if that is what a particular build appears to print. The correct design conclusion is that the deletion is invalid and the virtual destructor must be restored.

### Sanitizer verification procedure

The assignment requests verification with AddressSanitizer. Compile the modified program using the compiler's supported sanitizer flags, for example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer no_virtual_destructor.cpp -o no_virtual_destructor
```

Run the executable and record:
- compiler name and version;
- exact compile command;
- exact run command;
- full sanitizer output or observed output;
- whether the runtime reports a problem.

Do not manufacture a sanitizer report. Different toolchains may diagnose this undefined behaviour differently.

## 7. Design conclusion

Virtual functions allow a base-class interface to invoke the correct derived operation without manual type tests. A virtual destructor completes the safe ownership contract when objects are deleted through base pointers.
