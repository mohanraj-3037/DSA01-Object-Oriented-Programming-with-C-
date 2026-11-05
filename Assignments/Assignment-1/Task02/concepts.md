# Task 02 – Tokens, Keywords, Identifiers and Constants

## Five kinds of C++ tokens

| Token kind | Example from `constants.cpp` | Meaning |
|---|---|---|
| Keyword | `enum`, `class`, `constexpr`, `switch`, `return` | Reserved words with predefined meaning in C++. |
| Identifier | `Zone`, `INNER_FARE_PAISE`, `baseFare` | Names given to types, constants and functions. |
| Constant/literal | `1000`, `20`, `"Inner"`, `0` | Fixed values written directly in the source. |
| Operator | `=`, `+`, `<<`, `==`, `::` | Performs an operation or accesses a scoped name. |
| Punctuator | `{`, `}`, `(`, `)`, `;`, `,` | Separates or groups parts of the program. |

## `#define`, `const` and `constexpr`

- `#define` is a preprocessor substitution. It does not provide normal C++ type checking or namespace scope, so accidental text substitution and naming collisions are possible.
- `const` declares an object that cannot be modified through that name. Its value does not necessarily have to be known at compile time.
- `constexpr` declares a value or function that can be evaluated at compile time when its inputs permit it. It is typed, scoped and suitable for fixed fare values.

`constexpr` is preferred for the fixed fare values, surcharge percentage and minimum balance because these are compile-time configuration values and should be type checked.

## `enum` versus `enum class`

An unscoped `enum` exposes enumerator names into the surrounding scope and can convert to an integer. `enum class` keeps names scoped (`Zone::Inner`) and does not implicitly convert to an integer. This reduces naming conflicts and accidental comparisons between unrelated values.

## Identifier conventions

Identifiers must not be C++ keywords, must not begin with a digit, and are case-sensitive. This implementation uses `PascalCase` for the type `Zone`, `camelCase` for functions such as `baseFare`, and `UPPER_SNAKE_CASE` for constants such as `INNER_FARE_PAISE`.

## Alternative: macros and integer constants

Replacing the typed constants and `enum class` with macros would remove type checking and scope for the macro names and zone values. A macro itself occupies no runtime storage; a `constexpr` value also commonly requires no storage when used as a compile-time constant, although an object can require storage if its address is taken. Neither approach meaningfully changes the O(1) fare lookup time. The typed `constexpr` and `enum class` design is safer and easier to maintain.
