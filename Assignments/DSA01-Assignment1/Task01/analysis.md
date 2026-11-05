# Task 01 – Understand the Problem and Identify the Objects

## 1. Problem summary

The Namma Metro smart-card system calculates a fare from the farthest zone travelled. The original network has three zones: Inner (₹10), Middle (₹20) and Outer (₹30). A 20% surcharge applies during 08:00–09:59 and 17:00–19:59. A journey is accepted only when the card has at least ₹50 remaining after the fare is deducted. The assignment also mentions student and senior-citizen concessions, but it does not specify their percentage. Therefore, the concession percentage must be confirmed or stated as an explicit assumption before implementing it.

All monetary calculations should use integer paise. This avoids binary floating-point rounding when calculating fares and balances.

## 2. Objects, data and behaviour

| Object | Data (state) | Behaviour (responsibility) | Why it is needed |
|---|---|---|---|
| SmartCard | card ID, balance in paise | recharge, check eligibility, deduct fare | Owns and protects the stored balance so it cannot become negative or violate the minimum-balance rule. |
| Passenger | passenger ID, passenger category | report concession eligibility | Keeps passenger-related information separate from card and journey data. |
| Journey | origin zone, farthest zone, entry hour, travel date | validate journey details | Represents one trip and provides the inputs needed for fare calculation. |
| Zone | zone identity | identify the fare band | A strongly typed zone value prevents arbitrary text or unrelated integers from being used as a zone. |
| FareTable | base fares, surcharge percentage, minimum balance | return base fare and calculate final fare | Centralises fare rules so a fare revision is made in one place. |

## 3. OOP principles in this system

- **Encapsulation:** `SmartCard` keeps `balancePaise` private. Other parts of the program cannot directly assign a negative balance. They must use validated methods such as `recharge()` and `deduct()`.
- **Abstraction:** A caller can use `FareTable::calculateFare()` without needing to know every arithmetic step used internally.
- **Inheritance:** If passenger categories have different concession policies, `StudentPassenger` and `SeniorPassenger` could derive from a common `Passenger` base class. This should only be introduced if the policies genuinely differ; inheritance is not required merely to use OOP.
- **Polymorphism:** A virtual concession method in `Passenger` could be overridden by student and senior passenger types. The fare service could call the method through a `Passenger` reference without checking the concrete type.

## 4. Rules and assumptions

1. A valid zone must be one of the defined zone values.
2. Peak hours are `hour >= 8 && hour < 10` or `hour >= 17 && hour < 20`. Thus 08:00 and 17:00 are peak; 10:00 and 20:00 are not.
3. The peak surcharge is 20% of the base fare.
4. Money is stored as integer paise.
5. A journey is accepted only if `balancePaise - farePaise >= 5000`.
6. A rejected journey must not change the card balance.
7. The assignment does not state the student/senior concession percentage or how the two categories interact. This must be clarified or explicitly assumed in the final implementation.

## 5. Procedural and object-oriented approaches

A procedural implementation could store balances in an array and use free functions such as `calculateFare(zone, hour)` and `deductFare(balance, fare)`. It can produce the same result and has O(1) time per journey and O(1) balance storage per card. However, every function receiving a balance must remember to enforce the minimum-balance rule. A new fare rule may require edits across several functions.

An object-oriented implementation groups balance and its validation operations inside `SmartCard`, while `FareTable` owns fare rules and `Journey` represents trip data. It has the same asymptotic time and storage costs: O(1) per journey for a fixed number of zones and O(1) balance storage per card. Its main advantage is safer organisation and lower change impact, not faster execution.

## 6. Complexity comparison

| Measure | Procedural | Object-oriented |
|---|---:|---:|
| Fare calculation per journey | O(1) | O(1) |
| Balance check/deduction | O(1) | O(1) |
| Balance storage per card | O(1) | O(1) |
| Change to a fare rule | May affect multiple functions and call sites | Usually localised in `FareTable` |

## 7. Conclusion

The object-oriented design is recommended because it assigns clear responsibilities to `SmartCard`, `Journey`, `Passenger` and `FareTable`, and encapsulation protects the balance invariant. For the current small system, it does not improve Big-O performance over a procedural program, but it makes the rules easier to maintain and validate as the network grows.
