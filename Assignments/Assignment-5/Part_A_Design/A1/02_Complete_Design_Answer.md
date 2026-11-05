# A1 – Complete Design Answer

## 1. Design objective

The billing system must calculate different bill categories through one consistent operation. The caller should be able to process an out-patient bill, in-patient bill, day-care bill or emergency bill without writing a separate daily-total loop for every category.

The design therefore separates:
- **common identity and behaviour**, which belong in the abstract `Bill` base class;
- **category-specific data and calculation**, which belong in the concrete derived classes;
- **aggregation**, which depends only on the base-class interface.

This is an application of abstraction and runtime polymorphism. The abstract class expresses what every bill can do, while each derived class decides how its total is calculated.

## 2. A1.1 – Common interface and shared data (2 marks)

### 2.1 Common data

A bill needs enough shared information to identify the bill and the patient to whom it belongs. A reasonable common model is:

| Common member | Suggested type | Purpose | Why it is common |
|---|---|---|---|
| `billId` | `std::string` | Unique bill reference | Every category is still a hospital bill |
| `patient` | `std::string` | Patient name or patient reference | Every bill belongs to a patient |

These are design choices for the class model. The case study says bills are raised for patients, but it does not mandate the exact identifier representation.

Category-specific values should not be placed in the base class. For example, `daysAdmitted` is meaningful for an in-patient bill but not necessarily for an out-patient bill. Storing all category-specific fields in `Bill` would make the base class contain unused or irrelevant state.

### 2.2 Common operations

| Operation | Suggested signature | Classification | Responsibility |
|---|---|---|---|
| Calculate amount | `virtual double total() const = 0` | Pure virtual | Forces every concrete bill type to provide its own calculation |
| Identify category | `virtual std::string type() const = 0` | Pure virtual | Allows reports to identify the concrete bill kind |
| Display bill | `virtual void print() const` or `void print() const` | Common implementation is sufficient | Displays patient/bill information and calls `type()` and `total()` |
| Destroy through base pointer | `virtual ~Bill()` | Virtual destructor | Ensures derived destruction when a `Bill*` is deleted |

**Why is `total()` pure virtual?** The calculation differs by bill category. A generic `Bill` object has no single correct formula. Making `total()` pure virtual prevents direct construction of a `Bill` and requires each concrete class to implement the calculation.

**Why is `type()` useful?** It gives reports and logs a stable category label without requiring the caller to inspect the concrete class with a cast.

**Why can `print()` have a common implementation?** It can print the shared patient information and call the virtual `type()` and `total()` operations. Those inner virtual calls still use the actual object's derived implementations.

**Why must the destructor be virtual?** The system is explicitly designed to hold derived objects through `Bill*`. A virtual destructor makes deletion through that base pointer safe.

### 2.3 Interface contract

The contract for `total()` should be:
1. Return the monetary total for the complete bill.
2. Do not silently omit a charge that belongs to that bill category.
3. Reject invalid input at construction or validation boundaries rather than returning a misleading amount.
4. Return a finite, non-negative amount for a valid bill.
5. Use a consistent currency unit and rounding policy throughout the system. The assignment does not specify a currency or rounding mode, so the implementation must state its chosen convention.

## 3. A1.2 – Abstract class hierarchy (3 marks)

### 3.1 Abstract base class: `Bill`

`Bill` stores the information shared by every bill and declares the common operations. It is abstract because `total()` and `type()` are pure virtual.

### 3.2 Concrete derived classes and calculation responsibility

| Derived class | Information required by the case study | Calculation responsibility |
|---|---|---|
| `OutPatientBill` | Consultation charge and test charges | Consultation + total test charges |
| `InPatientBill` | Number of days, room rate per day, procedure charges and medicine charges | Days × room rate + procedures + medicines |
| `DayCareBill` | Package price | Package price |
| `EmergencyBill` | Base emergency charge and time-based charges | Base charge + time-based charges |

The formulas above directly express the billing basis stated in the case study. The internal representation of “test charges” or “time-based charges” can be a total field or a collection of line items. The brief does not dictate which.

### 3.3 Why each class overrides `total()` and `type()`

- `OutPatientBill::total()` applies the out-patient formula.
- `InPatientBill::total()` applies the in-patient formula.
- `DayCareBill::total()` returns the package amount.
- `EmergencyBill::total()` adds the base amount and time-based charges.
- Each `type()` returns a stable category label such as `"OutPatient"`, `"InPatient"`, `"DayCare"` or `"Emergency"`.

The derived class overrides are marked `override` in C++ design notation. This allows the compiler to detect a signature mismatch.

### 3.4 Why the base pointer array is the right abstraction

A collection of `Bill*` can refer to objects of different concrete classes. The loop sees only the common `Bill` interface. When it calls `total()`, virtual dispatch selects the implementation belonging to the pointed-to object's dynamic type.

This avoids code like:

```text
IF bill is outpatient THEN calculate outpatient
ELSE IF bill is inpatient THEN calculate inpatient
ELSE IF bill is daycare THEN calculate daycare
ELSE IF bill is emergency THEN calculate emergency
```

The category decision is moved into the object's own overridden operation.

## 4. A1.3 – Daily total using base-class pointers (2 marks)

### SIMATS-style algorithmic pseudocode

```text
ALGORITHM CalculateDailyBillTotal(BillList, N)
    DECLARE DailyTotal AS REAL
    DECLARE I AS INTEGER

    SET DailyTotal <- 0

    FOR I <- 0 TO N - 1
        IF BillList[I] IS NOT NULL THEN
            SET DailyTotal <- DailyTotal + BillList[I].total()
        END IF
    END FOR

    DISPLAY "Number of bills: ", N
    DISPLAY "Daily bill total: ", DailyTotal
END ALGORITHM
```

### Explanation of the algorithm

1. `DailyTotal` is initialized to zero so that no previous value affects the calculation.
2. The loop visits each pointer exactly once.
3. A null-pointer check prevents a call through an absent pointer.
4. `BillList[I].total()` is a virtual operation. The actual bill type determines the calculation.
5. The returned amount is added to the running total.
6. After all bills have been processed, the aggregate is displayed.

### Preconditions and postconditions

**Preconditions**
- `N` is the number of valid array positions.
- Every non-null pointer refers to a live object derived from `Bill`.
- Every bill has already passed input validation.
- All totals use the same currency and rounding convention.

**Postconditions**
- `DailyTotal` is the sum of `total()` for every non-null bill pointer in the array.
- No category-specific branch is required in the aggregation algorithm.

### Correctness argument

For an array of `N` bill pointers, after processing index `I`, the loop invariant is:

> `DailyTotal` equals the sum of the totals of all non-null bill objects at indices from `0` through `I`.

Initially, before the loop, the sum over the empty processed range is zero, matching the initialization. At each iteration, the algorithm adds the current bill's total if the pointer is non-null, preserving the invariant. When the loop terminates, all indices have been processed, so `DailyTotal` equals the required daily total.

## 5. Design evaluation

The hierarchy has one stable abstraction and four specialised implementations. This is preferable when bill categories have distinct calculation rules and new categories may be introduced. The daily-total algorithm remains unchanged when a new derived class implements the `Bill` interface.

A limitation is that a new derived class must be compiled and deployed with the application. This design is not itself a plug-in or configuration-driven billing engine. The brief's later production scenario asks students to evaluate that distinction in Part B.
