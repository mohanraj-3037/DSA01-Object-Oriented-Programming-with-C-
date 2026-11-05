# Q2 Analysis

Returning `int&` aliases the selected array element, so `highest(marks, 5) += 2` modifies the array. A `const int&` permits reading but not assignment through that reference. Returning `int` produces an independent copy.

Returning a reference to a local variable is invalid because the local object's lifetime ends when the function returns. The reference dangles; using it is undefined behaviour. The unsafe function is present only to produce compiler diagnostic evidence and is never called.

Finding the maximum is O(n) time and O(1) auxiliary space for reference, pointer and index approaches. An index is generally the clearest handle for a vector that may reallocate: after growth, re-index the vector. A pointer/reference into a vector can be invalidated by reallocation. An index remains meaningful only if the logical element ordering/removal policy preserves its meaning.
