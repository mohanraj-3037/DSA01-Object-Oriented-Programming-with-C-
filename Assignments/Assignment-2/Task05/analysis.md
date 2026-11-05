# Q5 Analysis

`issued` and `CAPACITY` belong to the class, so they are static. `issued` is defined once outside the class. `count()` is static because it needs no particular ticket object and therefore has no `this` pointer. A static function cannot directly access a non-static `seat` or `name`.

An array of objects constructs each element. The static count persists across loops and function calls, so subsequent batches see the cumulative count. A global counter is less encapsulated. A separate `TicketOffice` object allows two buses to maintain independent capacities and counters, which is more flexible when multiple buses operate concurrently.
