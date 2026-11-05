# Q7: Complex-number class for AC impedance

## Requirements
Represent real and imaginary parts as doubles; support construction from zero, real-only and real/imaginary values; implement +, -, *, /, ==, stream output and magnitude; detect division by zero.

## Formulae
- Addition: (a+jb)+(c+jd) = (a+c)+j(b+d)
- Subtraction: (a+jb)-(c+jd) = (a-c)+j(b-d)
- Multiplication: (ac-bd)+j(ad+bc)
- Division: ((ac+bd)+j(bc-ad))/(c²+d²)
- Magnitude: sqrt(a²+b²)

The arithmetic operators are members because the left operand is Complex. `<<` is a friend non-member because the left operand is an ostream. Equality uses a small tolerance because floating-point arithmetic is approximate.

## Verification
Series example: 10+j20 + (-j5) = 10+j15; magnitude = sqrt(325) ≈ 18.028 ohms.
Parallel example: (10+j5)||(20-j5) = (Z1*Z2)/(Z1+Z2); program prints the computed rectangular value and magnitude.
Division by zero throws `std::domain_error`.

## Evaluation
`std::complex<double>` already implements the arithmetic and is preferable in production. Both representations use two doubles and O(1) time per operation. The custom class demonstrates the design and allows domain-specific formatting and explicit zero-division policy. Limitation: double precision and exact-zero check may need a domain-specific tolerance.
