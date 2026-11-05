# Task 3 – Constructors in Derived Classes and Member Classes

## 3.1 Initialising bases
A derived constructor uses an initializer list, for example:
`Student(...) : Person(name, id, phone), programme_(programme) {}`
For a virtual base, only the most-derived class's initializer controls construction. Therefore `TeachingAssistant` must initialise `Person` directly. When Student or Staff is constructed alone, its Person initializer is used.

## 3.2 Member classes
`Address` is a member object of Person and `Course` could be a member object of Student. Pass their constructor arguments in the containing class initializer list, e.g. `home_(city, pin)` and `course_(code, title)`.

## 3.3 Supplied Car trace prediction
`Vehicle Engine Car | ~Car ~Engine ~Vehicle`
Construction order is base class, then members in declaration order, then derived constructor body. Destruction reverses that order: derived destructor body, members in reverse declaration order, then base destructor.

## 3.4 Virtual base experiment
Removing virtual from both Student and Staff creates two Person subobjects in TeachingAssistant. Its size commonly increases, but exact `sizeof` is implementation-dependent and must be recorded on the student's compiler. Construction prints Person twice before Student and Staff.

## Completed TODO
The `Student` constructor in `main.cpp` initialises the Person base, `regNo_`, and the Address member in its initializer list. Expected line:
`192311001 Kavya (19) Salem-636001`

Reordering initializer-list entries does not change actual initialisation order. C++ initialises bases first, then members in their declaration order. GCC's `-Wall -Wextra` may emit `-Wreorder` when the written list order conflicts with declaration order.

## Pointer alternative
A dynamically allocated `Address*` adds an allocation and indirection. The constructor must allocate it, the destructor must `delete` it, and the copy constructor/assignment must deep-copy it or use a smart pointer with appropriate ownership semantics. An embedded Address object is simpler and avoids manual lifetime management.
