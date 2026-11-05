# Task 1 – Class Design Review

## 1.1 Design deficiencies
1. `name`, `id`, `basic` and `da` are duplicated across unrelated classes.
2. Public data members allow invalid values and uncontrolled modification.
3. `name`/`nm` and `id`/`code` use inconsistent names for equivalent concepts.
4. `da` is stored but never used in either regular staff pay calculation.
5. `0.42` is a magic number with no named policy or explanation.
6. `pay()` is not polymorphic, so a common collection cannot call the correct calculation through a shared base interface.
7. Adding a staff category requires another unrelated class and more caller-side branching.

## 1.2 Repaired design
`Staff` owns common identity and basic-pay data and declares pure virtual `pay()`. `Professor`, `LabAssistant` and `GuestFaculty` implement the pay rule. A virtual destructor makes deletion through `Staff*` safe.

```text
                 <<abstract>>
                    Staff
          name, id, basic (protected/private)
                 + pay() = 0
                 /      |       \
        Professor  LabAssistant  GuestFaculty
        research       (none)      hours, rate
```

## 1.3 Design defence (under 100 words)
A new staff category can derive from `Staff`, initialise the shared identity fields and override `pay()`. Existing code that stores `unique_ptr<Staff>` and calls `pay()` does not need to know the concrete category. This localises each pay rule, removes repeated identity fields and avoids a growing switch statement. The virtual destructor also ensures derived resources are released correctly.

## Alternative: one Staff class with a type and switch
The `pay()` call remains O(1) for a fixed number of types. A single class must reserve fields for every category, leaving irrelevant fields unused in many objects. A new category changes the class fields, constructor/validation logic, `pay()` switch and often callers/tests. In the hierarchy, the new type normally adds one derived class and its tests. Both designs use O(1) object space for a fixed schema; the single class may have greater per-object field storage.
