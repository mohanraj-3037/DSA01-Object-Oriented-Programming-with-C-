# A3 – Complete Design Answer

## 1. Purpose of the payer abstraction

The hospital may receive payment from different sources:
- the patient directly;
- an insurance company within the policy cover;
- a government health scheme using fixed package rates.

These payment sources share one responsibility: determine how much of a particular bill they cover. The calculation differs by payer type, so it belongs in a polymorphic interface.

The bill and payer abstractions have separate responsibilities:
- `Bill` calculates the amount charged by the hospital.
- `Payer` calculates the amount covered by a payment policy.

This separation avoids mixing hospital charge calculation with insurance or scheme rules.

## 2. A3.1 – Abstract `Payer` interface (3 marks)

### 2.1 Interface

A suitable abstract interface is:

- `amountCovered(const Bill&)`: receives a bill by const reference and returns the amount covered by that payer.
- virtual destructor: supports safe destruction through a `Payer*`.

The function is pure virtual because the base class does not know whether the payer is the patient, an insurer or a government scheme.

### 2.2 `SelfPay`

**Meaning:** the patient is responsible for the full bill.

**Policy rule:** for a valid bill total `T`, the covered/payment responsibility returned by the payer model is `T`.

**Input:** a `Bill` object.

**Output:** the full bill total.

No policy limit is required for the basic self-pay model. The assignment does not require a discount or payment-plan calculation.

### 2.3 `Insurance`

The brief explicitly requires two policy values:
- cover limit;
- co-payment percentage.

For a clear design, define:
- `T` = bill total;
- `p` = patient's co-payment percentage, represented as a fraction from 0 to 1;
- `L` = remaining insurer cover limit.

Under this stated convention, the insurer's share before the cover cap is:

`T × (1 − p)`

The amount covered by the insurer is:

`min(T × (1 − p), L)`

This formula is a modelling assumption to make the co-payment meaning unambiguous. If the lecturer intends the percentage to mean the insurer's share rather than the patient's share, the formula must be adjusted accordingly. The brief itself does not define which party the percentage belongs to.

**Validation responsibilities**
- cover limit must not be negative;
- co-payment percentage must be within the permitted range;
- bill total must be valid and non-negative;
- remaining cover must be updated consistently when claims are settled.

A real system should distinguish total policy limit from remaining available cover. The assignment only names a cover limit; using `remainingCover` is a practical refinement for repeated claims.

### 2.4 `GovernmentScheme`

The case study says the government health scheme uses fixed package rates.

A suitable design stores a package-code-to-rate mapping:

| Data | Purpose |
|---|---|
| `packageRates` | Associates a package code with its fixed approved amount |

The payer looks up the relevant package rate and returns the amount covered according to that rate. An unknown package code should be rejected with a clear error, which connects to the exception design in A4.

The brief does not provide actual government package names or prices. Do not invent a real-world rate table. A sample table in an implementation must be labelled synthetic or illustrative.

## 3. A3.2 – Add a corporate payer without modifying existing classes (2 marks)

A corporate tie-up can be introduced as a new class derived from `Payer`.

Possible policy data:
- negotiated coverage percentage;
- contract coverage limit;
- optional corporate account or contract identifier.

The class implements `amountCovered(const Bill&)` using the corporate agreement. Existing classes remain unchanged:
- `Payer`;
- `SelfPay`;
- `Insurance`;
- `GovernmentScheme`.

The rest of the billing system continues to store or accept `Payer&` / `Payer*`. It can therefore use the new `CorporatePayer` through the existing interface.

### Extension sequence

1. Create `CorporatePayer` as a public subclass of `Payer`.
2. Add the corporate agreement data to that class.
3. Implement `amountCovered(const Bill&)`.
4. Validate the corporate limit and percentage.
5. Add a test that passes a `CorporatePayer` through a `Payer&`.
6. Do not edit the existing payer classes or the code that depends only on `Payer`.

### Why this is an extension rather than a modification

The original abstraction already defines the operation needed by all payer types. A new payer is another implementation of the same contract. The extension demonstrates the open/closed principle: the design is open to new behaviour through extension while existing tested classes remain closed to modification.

## 4. Interaction between `Payer` and `Bill`

The signature `amountCovered(const Bill&)` intentionally accepts the base abstraction rather than one concrete bill type. A payer should be able to process any supported bill through the bill's public interface.

Conceptually:

```text
Payer reference
      |
      | amountCovered(Bill reference)
      v
Bill interface
      |
      | total() virtual call
      v
Concrete bill total
```

The payer can obtain the bill amount through `Bill::total()`. If a particular payer requires a package code, the design must make that package information available through an appropriate bill interface or through a clearly defined package-specific model. The brief does not prescribe the exact accessor, so this detail should be designed consistently rather than using unsafe casts without justification.

## 5. Design evaluation

The payer hierarchy keeps each payment rule with the class that owns the policy data. It avoids a single large conditional statement that must be edited whenever a payer type is added. The design also keeps bill calculations separate from coverage calculations, which makes each responsibility easier to test and reason about.
