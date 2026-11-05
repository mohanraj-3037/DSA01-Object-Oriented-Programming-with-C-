# Task 08: Safe Input and Output

- `cin` reads values from standard input.
- `cin.fail()` / the failed stream state detects invalid input such as letters entered for an integer.
- `cin.clear()` resets the error state so another read can be attempted.
- `cin.ignore(numeric_limits<streamsize>::max(), '\\n')` discards the rest of the invalid input line.
- `iomanip`, `fixed`, and `setprecision(2)` display rupee amounts with exactly two decimal places.
- The program stores money as integer paise. Floating point is used only to format the display, not to calculate or store the balance.

## Try these inputs
1. Balance `10000`, fare `3000`: payment accepted, balance ₹70.00.
2. Balance `8000`, fare `3000`: denied because the remaining balance would be below ₹50.00.
3. Enter `abc` for the balance: the program reports invalid input and asks again.
4. Enter a negative amount: the program rejects it and asks again.
