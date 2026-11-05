# Q7 Design Challenge: Transaction History

## A. Diagnose
The original shift-on-full design moves every retained element one position for each new transaction after capacity is reached. With capacity k, each full-buffer insertion performs k-1 moves: O(k).

## B. Measurable objective
For a fixed capacity of 100,000 and 1,000,000 insertions, preserve the newest 100,000 values in chronological order while making each insertion O(1).

## C. Revised design
Use a circular buffer with `next` pointing to the next write slot and `count` tracking valid entries. Write at `next`, advance modulo capacity, and cap count at capacity. The oldest entry is at `next` once full.

Pseudocode:
1. data[next] = value
2. next = (next + 1) % capacity
3. count = min(count + 1, capacity)

## D. Prediction
The circular version performs one indexed write and one index update per insertion. The shift version performs up to capacity-1 element moves after filling. Predict a lower insertion time for the circular version at large capacity.

## E. Validation
Run `benchmark.cpp` using the same compiler, build flags, capacity and operation count. Record the measured `shift_ms` and `circular_ms` printed by your own machine. Verify both retain the same newest value. Also add a correctness test that checks the full chronological sequence.

## F. Evaluation
Both versions use O(k) storage. Shifting is simpler and may be adequate for tiny capacities. Circular storage adds index logic but provides O(1) insertion independent of capacity. Do not claim a measured speedup until the benchmark has actually been run and its output recorded.
