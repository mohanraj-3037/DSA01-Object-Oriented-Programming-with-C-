# DSA01 Assignment 3 – CO3: Constructors and Operators

This project contains C++17 implementations and analysis for all seven questions in the uploaded Assignment 3 brief.

## Requirements
- GCC / MinGW-w64 (MSYS2 UCRT64 recommended)
- C++17
- VS Code optional

## Compile and run
From the project root, for example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic Task01/book.cpp -o task01
./task01
```

On Windows PowerShell, run `.\task01.exe` after compilation. Repeat with the source file for each task.

For AddressSanitizer (supported GCC toolchains):

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address -g Task02/prescription.cpp -o prescription
./prescription
```

For optimized timing experiments use `-O0` and `-O2` and record your own results on your machine.

## Task index
| Task | Source | Focus |
|---|---|---|
| 01 | `Task01/book.cpp` | Constructors, delegation, validation, explicit |
| 02 | `Task02/prescription.cpp` | Deep copy, assignment, destructor |
| 03 | `Task03/auditorium.cpp` | Dynamic 2D allocation, destructor, RAII |
| 04 | `Task04/money.cpp` | Arithmetic and stream operators |
| 05 | `Task05/time_playlist.cpp` | Prefix/postfix, comparisons, checked subscript |
| 06 | `Task06/text.cpp` | Rule of Three and operator-overloading rules |
| 07 | `Task07/complex_impedance.cpp` | Complex class and AC impedance |

Each task folder includes source code, a prediction/notes file and analysis.

## Important submission checklist
1. Fill in your name, register number, compiler/version and GitHub repository URL in the report.
2. Make your own prediction before running each Predict the Output task. Prediction files are study aids, not proof of a pre-run prediction.
3. Compile and execute every program locally.
4. Run sanitizer builds for Q2 and Q3 and save genuine terminal output/screenshots.
5. Perform the timing experiments requested in Q2, Q4, Q5 and Q6. Record your own measurements, machine/compiler details and flags.
6. Add memory diagrams for Q1, Q2 and Q3 to the report.
7. Create the required GitHub repository `DSA01-<RegisterNumber>-Assignment3`; commit progressively, at least one commit per task.
8. Share the repository with faculty and add the working URL to the report.

## Notes and assumptions
- Q4's constructor stores the total in paise. The sample includes negative values for demonstration; decide and document your production policy.
- Q5 uses exceptions for invalid playlist indexing, a safe library-style policy.
- Q7 uses example impedances because the assignment does not prescribe particular circuit values.
- Compiler output, sanitizer diagnostics and benchmark timings vary by platform. Do not submit fabricated measurements or screenshots.
