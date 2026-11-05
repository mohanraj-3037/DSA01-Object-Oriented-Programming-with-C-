# A1 – Alternative Concept and Complexity Analysis

## Alternative: one `Bill` structure with a type field and a `switch`

Instead of an abstract base class and derived objects, the system could use one record with a category tag and fields for every charge type.

### Conceptual structure

```text
RECORD Bill
    type
    patient
    consultationCharge
    testCharges
    days
    roomRatePerDay
    procedureCharges
    medicineCharges
    packagePrice
    baseEmergencyCharge
    timeBasedCharges
END RECORD
```

Only the fields associated with the selected `type` are meaningful for one record. The other fields remain unused.

### SIMATS-style pseudocode for tagged total

```text
ALGORITHM CalculateTaggedBillTotal(B)
    DECLARE Amount AS REAL

    SWITCH B.type
        CASE "OUT_PATIENT":
            SET Amount <- B.consultationCharge + B.testCharges

        CASE "IN_PATIENT":
            SET Amount <- (B.days * B.roomRatePerDay)
                          + B.procedureCharges
                          + B.medicineCharges

        CASE "DAY_CARE":
            SET Amount <- B.packagePrice

        CASE "EMERGENCY":
            SET Amount <- B.baseEmergencyCharge
                          + B.timeBasedCharges

        OTHERWISE:
            REPORT "Unknown bill type"
            RETURN 0
    END SWITCH

    RETURN Amount
END ALGORITHM
```

### Daily total using the tagged representation

```text
ALGORITHM CalculateTaggedDailyTotal(Bills, N)
    DECLARE Sum AS REAL
    DECLARE I AS INTEGER

    SET Sum <- 0

    FOR I <- 0 TO N - 1
        SET Sum <- Sum + CalculateTaggedBillTotal(Bills[I])
    END FOR

    DISPLAY Sum
END ALGORITHM
```

## Time complexity

Let `n` be the number of bills and assume each category calculation performs a fixed number of arithmetic operations.

| Operation | Virtual hierarchy | Tagged record + switch |
|---|---:|---:|
| Calculate one bill | O(1) | O(1) |
| Calculate all `n` bills | O(n) | O(n) |
| Additional loop state | O(1) | O(1) |

Both designs visit every bill once. The assignment specifically expects O(n) for both approaches. A virtual call has dispatch overhead; a switch has branch-selection overhead. The actual difference depends on compiler optimisation, object distribution and hardware and should not be guessed without measurement.

## Space complexity and per-object storage

### Virtual hierarchy
- Each object stores the common base data and the fields required by its derived class.
- A typical implementation stores a hidden virtual-table pointer (`vptr`) in a polymorphic object.
- The C++ standard does not mandate the exact object layout or vptr size.
- An array of pointers stores one pointer per bill, separate from the bill objects.

### Tagged structure
- Every record contains the tag and storage for all declared fields.
- If all possible fields are ordinary members, each record reserves space for fields that are irrelevant to its selected category.
- A union-like representation can reduce unused storage but requires careful lifetime and tag management.

Both collections require O(n) total storage for `n` bills. The constant amount per record differs and should be measured with `sizeof` on the actual compiler if a byte count is required.

## Extension and maintenance comparison

| Evaluation point | Virtual hierarchy | Tagged record + switch |
|---|---|---|
| Add a new bill type | Add a new derived class implementing the interface | Add new tag, fields and switch case |
| Existing daily-total loop | Unchanged | Unchanged if it calls the central tagged-total function |
| Other switch statements | Not needed for total calculation | Must be found and updated if they interpret bill type |
| Risk | New derived class may omit or misimplement an override; compiler catches missing pure virtual implementation by keeping it abstract | A missing switch case may be overlooked unless guarded by validation/warnings |
| Data layout | Stores only fields selected for that concrete type, plus implementation overhead | Simple all-fields record can reserve unused field space |

## Evaluation

The tagged representation may be simpler when the set of bill types is small and fixed. The abstract hierarchy better expresses category-specific behaviour and supports extension without modifying the working aggregation algorithm. For the case study, where different bill types have genuinely different total calculations, the polymorphic hierarchy is a clear object-oriented model.
