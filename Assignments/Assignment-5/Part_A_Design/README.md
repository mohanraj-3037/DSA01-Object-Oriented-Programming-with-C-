# PART A – DESIGN (25 MARKS)
## Reliable Software with Runtime Polymorphism and Exceptions

This folder is organised exactly by the five assessed design tasks A1–A5 in the assignment brief. Each task has its own answer, pseudocode/design artefacts, Mermaid source diagram, alternative-concept analysis and evidence checklist.

### How to use this section

1. Read the task requirement sheet to see the exact marks and assessed points.
2. Read the design answer. It distinguishes requirements stated in the brief from explicit modelling assumptions.
3. Open the `.mmd` file located inside that same task folder. Paste its contents into [Mermaid Live Editor](https://mermaid.live/) to render and export it.
4. Use the alternative analysis to answer the assignment's required “what if?” design comparison.
5. Complete the checklist and add any lecturer-specific cover-page details.

### Important academic distinction

Part A asks for **design reasoning, UML, conceptual diagrams and SIMATS-style pseudocode**. It does not ask for C++ implementation in place of pseudocode. The executable implementation and measured experimental evidence belong in Part B, which has intentionally not been edited in this update.

### Task and mark map

| Task | Design focus | Marks |
|---|---|---:|
| A1 | Polymorphic bill hierarchy | 7 |
| A2 | Runtime binding, vtables and virtual destructors | 5 |
| A3 | Abstract payer classes and extension | 5 |
| A4 | Exception strategy and exception specifications | 4 |
| A5 | Recovery, rethrowing, stack unwinding and RAII | 4 |
| **Total** | | **25** |

### Source fidelity

The hospital case study specifies four bill categories and three payer categories. Where the brief does not specify exact field names, formulas or policy details, this design labels them as modelling choices instead of presenting them as mandatory facts. For example, an insurance co-payment formula must state which party's percentage it represents.
