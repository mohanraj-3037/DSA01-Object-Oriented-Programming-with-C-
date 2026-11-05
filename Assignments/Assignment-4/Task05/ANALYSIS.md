# Task 5 – Pointers to Objects and the this Pointer

## 5.1 Four ways to reach an object
- Direct object: `Cart c; c.total();`
- Pointer: `Cart* p = &c; p->total();`
- Reference: `Cart& r = c; r.total();`
- Dynamic object: `Cart* p = new Cart; p->total(); delete p;`

The implementation demonstrates all four. `add()` and `setDiscount()` return `Cart&` via `*this`, enabling chained calls. `this->discount_` explicitly selects the data member when the parameter is also named `discount`.

## 5.2 Highest cart
The source stores pointers in an array and scans them with indexing. The scan takes O(n) time and O(1) extra space.

## 5.3 Comparison
| Form | Lifetime | Main consideration |
|---|---|---|
| Direct object | Scope-based | Safest simple ownership |
| Pointer to existing object | Does not own object | Can be null or dangling |
| Reference | Does not own object | Must refer to a valid object; cannot be reseated |
| `new` pointer | Dynamic until `delete` | Manual ownership risks leaks; prefer smart pointers |

`this` is the implicit pointer to the object on which a non-static member function was called. `*this` is that object as an lvalue.

## Completed TODO output
`324.00`
The cart total before discount is 60 + 120 + 180 = 360; a 10% discount leaves 324.

Returning Cart by value creates a copy/temporary at each chain step instead of returning the same object by reference. It can cause extra copies and makes chaining operate on temporary copies, so subsequent mutations may not affect the original object.

## vector alternative
A `vector<Cart>` stores objects directly and still permits an O(n) highest-total scan. It avoids one pointer indirection and separate allocations, but vector growth may move objects and invalidate pointers/references/iterators to its elements. A vector of pointers stores pointer-sized elements but requires separate object lifetime management or smart pointers.
