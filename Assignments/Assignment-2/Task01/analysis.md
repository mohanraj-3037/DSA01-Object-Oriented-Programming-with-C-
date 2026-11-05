# Q1 Analysis

- **Value:** the parameter is a separate local copy. The caller's fee is unchanged.
- **Reference:** the parameter is an alias for the caller's object. Changes affect it.
- **Pointer:** the pointer value is copied, but it points to the caller's object; dereferencing changes that object. A null check is appropriate when null is possible.
- **const reference:** use for large read-only objects to avoid copying while preventing modification.
- **Design decision:** for one fee update, returning a new fee is easy to test and compose; in-place reference mutation is reasonable when the API explicitly represents an update. Apply multiple concessions sequentially and document whether percentages apply to the original fee or the progressively reduced fee.
- All three scalar approaches take O(1) time. A `long long` value copy is O(1) space. Passing a large `Student` object by value copies its fields (and any owned data); reference/const-reference parameters avoid that object copy and use O(1) parameter space.
