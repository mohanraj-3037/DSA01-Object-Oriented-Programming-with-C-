# A1 – Design the Polymorphic Bill Hierarchy
**Marks: 7 | Bloom level: K5 – Evaluate**

## What the assignment explicitly asks

### A1.1 Identify the common interface – 2 marks
Identify:
- operations every bill must provide, with examples `total()`, `type()` and `print()`;
- data that is common to all bills.

### A1.2 Design the hierarchy – 3 marks
- Design an abstract base class named `Bill`.
- Include pure virtual functions.
- Include derived classes for every bill kind in the case study.
- Draw a UML class diagram.
- Mark virtual, pure virtual and overridden operations clearly.

### A1.3 Process all bills together – 2 marks
Write SIMATS Engineering standard algorithmic pseudocode that computes the day's total for an array of base-class pointers containing different bill types.

## Case-study facts to preserve

The brief identifies these bill categories and their billing basis:

| Bill kind | Case-study description |
|---|---|
| Out-patient | Consultation and tests |
| In-patient | Room charges per day, procedures and medicines |
| Day-care surgery | Package price |
| Emergency | Base charge plus time-based charges |

The brief does not prescribe exact C++ member names, database identifiers or rounding policy. Those are design choices and should be stated as such.
