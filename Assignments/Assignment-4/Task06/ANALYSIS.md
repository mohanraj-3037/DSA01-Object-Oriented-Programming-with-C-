# Task 6 – Design Challenge: Vehicle Rental Fleet

## Stage 1: Entities and testable requirements
- Every vehicle has a registration number, daily rate and rental state.
- Bicycle is a vehicle.
- TwoWheeler and Car are motor vehicles; motor vehicles also hold a fuel/charge level and service due date.
- Car has seating capacity.
- ElectricCar has battery capacity and an energy rate per kWh.
- Each type computes a rental charge through the same interface.
- The system must rent, return and list all vehicles, calculate charges for a requested number of days, reject invalid state transitions, and allow a new type without modifying existing types.

## Stage 2: Hierarchy
```text
                 <<abstract>> Vehicle
           registration, dailyRate, rented
              rent(), returnVehicle()
                charge(days) = 0
                type() = 0
                       |
          +------------+-------------+
          |                          |
       Bicycle                  MotorVehicle
                                  /       \
                           TwoWheeler     Car
                                            |
                                       ElectricCar
```
`ElectricBus` is added as another `MotorVehicle` subtype. Inheritance is public. Vehicle ownership in the fleet is represented by `unique_ptr<Vehicle>`.

## Stage 3: Critical decisions
- `Vehicle` owns common registration, rate and rental state.
- `charge()` and `type()` are pure virtual.
- The destructor is virtual.
- `MotorVehicle` owns fuel/charge level and service due date.
- `Car` owns seat capacity; `ElectricCar` adds battery capacity and kWh rate.
- The fleet is a vector of base-class smart pointers, allowing heterogeneous vehicles and automatic cleanup.

## Stage 4: Class declarations and pseudocode
The full class declarations are in `main.cpp`.

**Rent pseudocode**
1. Receive a vehicle reference.
2. If its rented state is true, report an error.
3. Otherwise set rented state to true.
4. Record the rental start and customer details in a production system.

**Return pseudocode**
1. Receive the vehicle and actual rental days.
2. If it is not rented, report an error.
3. Compute base charge using virtual `charge(days)`.
4. Compute late fee if actual return exceeds due date.
5. Set rented state to false and issue the total.

The sample implementation demonstrates state validation, type-specific two-day charges and returning vehicles with a late fee. Because the assignment does not specify a numeric policy, the demonstration clearly labels its chosen example policy: 10% of the daily rate per late day. Replace this with the faculty-approved rate if one is supplied.

## Stage 5: Demonstration and extension
The program rents and returns a Bicycle, TwoWheeler, Car, ElectricCar and a newly added ElectricBus. ElectricBus is added as a new derived class and inserted into the fleet without changing Vehicle or existing concrete classes.

## Alternative: one Vehicle with type code and switch
For a fixed set of vehicle types, a switch-based `charge()` and a virtual call are both O(1). A single class often contains fields irrelevant to many vehicle types. A virtual hierarchy stores each type's relevant fields in its own class; typical polymorphic objects also have implementation-level virtual dispatch overhead (commonly a vptr). A new type in the switch design changes the central Vehicle class and its switch, while the hierarchy adds a new derived class. Both fleet scans are O(n).
