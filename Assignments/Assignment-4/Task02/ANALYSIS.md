# Task 2 – From Requirement to Hierarchy

## 2.1 Relationships
- `Student is-a Person`: public single inheritance.
- `Staff is-a Person`: public single inheritance.
- `TeachingAssistant is-a Student` and `is-a Staff`: public multiple inheritance. Since Student and Staff both virtually inherit Person, the combined structure is hybrid inheritance and resolves the diamond.
- `ResearchScholar is-a Student`: public multilevel inheritance.
- Address/contact details or a Course would be `has-a` member objects, not inheritance, because they are contained entities.

## 2.2 Diamond problem
Without virtual inheritance, a TeachingAssistant contains two Person subobjects, one through Student and one through Staff. Accessing `name` through the TeachingAssistant object is ambiguous and duplicates identity state. Declaring both intermediate bases as `virtual public Person` gives the most-derived TeachingAssistant one shared Person subobject. The most-derived class is responsible for initialising that virtual base.

## 2.3 Design decisions
The source implements `Person`, `Student`, `Staff`, `TeachingAssistant` and `ResearchScholar`. Inheritance is public because each derived object must be usable through its public base interface. Data is protected in the example for derived-class access; production code would usually keep fields private and expose validated accessors.

## 2.4 Access table
| Person member | Public inheritance | Protected inheritance | Private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | not directly accessible | not directly accessible | not directly accessible |

Private base members still exist in the base subobject, but derived classes cannot access them directly.

## Prediction exercise
For the supplied virtual-diamond trace program, predicted output:
`Person Student Staff TA `
Person is constructed once because it is a virtual base. Virtual bases are constructed by the most-derived object before its non-virtual bases. Without `virtual`, two Person subobjects are constructed, so the output begins `Person Person Student Staff TA `; a simple `name` access through TeachingAssistant becomes ambiguous.

## Alternative: composition
A TeachingAssistant containing Student and Staff members has-a rather than is-a relationships. Each member would itself contain a Person, normally producing two Person subobjects. `sizeof` should be measured on the target compiler because padding and virtual-base implementation details are ABI-dependent. Composition makes access explicit (`ta.student.name()`), avoids ambiguous inherited members, but does not make a TeachingAssistant substitutable for Student or Staff.
