# Q4 Analysis

The transaction array is private so callers cannot corrupt the account's history or count. The circular-array implementation stores up to 10 entries. Once full, the next insertion overwrites the oldest entry and advances the start position.

- Shifting: O(k) moves for each insertion when full, O(1) fixed storage.
- Circular array: O(1) insertion, O(1) fixed storage, with index bookkeeping.
- `std::deque`: push_back/pop_front are O(1) at the ends, with container overhead and dynamic allocation.

Changing capacity from 10 to 50 changes the fixed array size and loop/modulus bound, but a named capacity constant would make that change safer. A circular array is selected because the required operation is retaining the newest fixed number of transactions.
