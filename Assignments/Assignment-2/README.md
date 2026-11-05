# OOP with C++ | Assignment 2 – CO2

**Repository name:** `DSA01-<RegisterNumber>-Assignment2`  
**Student:** [Enter your name]  
**Register number:** [Enter your register number]  
**Compiler:** g++ [record your installed version with `g++ --version`]  
**Standard:** C++17

## Build and run
From the task folder in PowerShell:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic source.cpp -o program.exe
.\program.exe
```

For Task07:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -pedantic Task07/benchmark.cpp -o Task07/benchmark.exe
.\Task07\benchmark.exe
```

For Task06 benchmark, compile separately with `-O0` and `-O2`.

## Task index
| Folder | Topic | Main files |
|---|---|---|
| Task01 | Value, reference, pointer | `call_types.cpp`, `complete_code.cpp` |
| Task02 | Return by reference | `return_reference.cpp` |
| Task03 | Default arguments and overloads | `courier.cpp` |
| Task04 | Class with transaction array | `savings_account.cpp` |
| Task05 | Static members and object arrays | `bus_ticket.cpp` |
| Task06 | Friend and inline functions | `time_friend.cpp`, `time_member.cpp`, `benchmark.cpp` |
| Task07 | Diagnose, redesign, validate | `benchmark.cpp`, `comparison.md` |

## Important submission actions
1. Fill in your name, register number and actual compiler version.
2. Read each `prediction.txt` and preserve your prediction before running the corresponding program. Where you change a prediction, document why and when.
3. Compile and execute every source file yourself. Save fresh terminal screenshots in each `output/` folder.
4. Record real Task06 and Task07 timing results from your own machine. Do not copy example or fabricated timings.
5. Capture the compiler warning for the deliberately unsafe local-reference function in Task02. Do not call that function.
6. Create at least one genuine Git commit per task, progressively.
7. Add the final GitHub URL to the report and repository submission form.

## Suggested commits
`Complete Task 01`, `Complete Task 02`, …, `Complete Task 07`.

## Notes
- The assignment brief does not specify concession-combination policy or a required courier tariff. The sample Q1 code demonstrates arithmetic; the Q3 tariff is an illustrative design for testing overload selection. State any assumptions clearly.
- Task03: `charge(2)` selects the `int` grams overload by exact match. It therefore represents 2 grams, not 2 kilograms.
- Task07 is a proposed redesign experiment. Use your measured results and correctness tests in the final evaluation.
