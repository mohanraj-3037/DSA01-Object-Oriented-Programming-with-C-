# DSA01 Assignment 4 – CO4: Designing Reusable Class Hierarchies

C++17 implementation and analysis for all six tasks in the supplied assignment brief.

## Requirements
- g++ with C++17 support
- Compile each task using:
  `g++ -std=c++17 -Wall -Wextra -pedantic source.cpp -o program`
- For Task 4 sanitizer evidence, use:
  `g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer Task04/main.cpp -o task04_asan`

## Folders
- `Task01` payroll hierarchy, diagnosis, UML and alternative design
- `Task02` people hierarchy, virtual diamond and access table
- `Task03` derived/member construction, destruction and completed TODO
- `Task04` polymorphic accounts, slicing, virtual destructor and smart pointers
- `Task05` object pointers, references, `this`, chaining and cart search
- `Task06` extensible vehicle rental fleet with an abstract base class

## Build and run
Open a terminal in the relevant task folder. Compile the `.cpp` file using the command above, then run the resulting executable (`./program` on Linux/macOS or `program.exe` on Windows).

## Submission checklist
1. Add your name, register number, submission date and GitHub repository URL.
2. Run every program on your own system and save genuine terminal screenshots in the relevant task folder.
3. Record the exact compiler version (`g++ --version`).
4. Commit each task progressively, not as one final upload.
5. Complete the prediction-before-execution fields in each task's `ANALYSIS.md` before running the prediction programs.
6. Review every implementation and be ready to explain it in the viva.

## Notes
The source files are designed to compile with `-std=c++17 -Wall -Wextra -pedantic`. The intentionally defective Task 4 example is isolated in `Task04/defective_demo.cpp`; it is a forensic demonstration and should not be treated as the repaired implementation. AddressSanitizer output depends on compiler/runtime and operating system, so capture the actual output from your own machine rather than using a fabricated report.
