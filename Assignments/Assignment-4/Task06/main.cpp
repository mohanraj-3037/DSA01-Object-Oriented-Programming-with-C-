#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
    std::string registration_;
    double dailyRate_;
    bool rented_ = false;
public:
    Vehicle(std::string registration, double dailyRate)
        : registration_(std::move(registration)), dailyRate_(dailyRate) {}
    virtual ~Vehicle() = default;
    const std::string& registration() const { return registration_; }
    bool rented() const { return rented_; }
    void rent() {
        if (rented_) throw std::logic_error("Vehicle is already rented");
        rented_ = true;
    }
    double returnVehicle(int daysLate = 0) {
        if (!rented_) throw std::logic_error("Vehicle is not currently rented");
        rented_ = false;
        // Demonstration policy: late fee is 10% of daily rate per late day.
        return (daysLate > 0) ? daysLate * dailyRate_ * 0.10 : 0.0;
    }
    virtual double charge(int days) const = 0;
    virtual std::string type() const = 0;
    double dailyRate() const { return dailyRate_; }
};

class Bicycle : public Vehicle {
public:
    using Vehicle::Vehicle;
    double charge(int days) const override { return dailyRate() * days; }
    std::string type() const override { return "Bicycle"; }
};
class MotorVehicle : public Vehicle {
    double fuelOrCharge_;
    std::string serviceDue_;
public:
    MotorVehicle(std::string reg, double rate, double level, std::string due)
        : Vehicle(std::move(reg), rate), fuelOrCharge_(level), serviceDue_(std::move(due)) {}
    double level() const { return fuelOrCharge_; }
    const std::string& serviceDue() const { return serviceDue_; }
};
class TwoWheeler : public MotorVehicle {
public:
    using MotorVehicle::MotorVehicle;
    double charge(int days) const override { return dailyRate() * days; }
    std::string type() const override { return "Two-wheeler"; }
};
class Car : public MotorVehicle {
    int seats_;
public:
    Car(std::string reg, double rate, double level, std::string due, int seats)
        : MotorVehicle(std::move(reg), rate, level, std::move(due)), seats_(seats) {}
    double charge(int days) const override { return dailyRate() * days; }
    std::string type() const override { return "Car"; }
    int seats() const { return seats_; }
};
class ElectricCar : public Car {
    double batteryKwh_;
    double kwhRate_;
public:
    ElectricCar(std::string reg, double rate, double level, std::string due,
                int seats, double batteryKwh, double kwhRate)
        : Car(std::move(reg), rate, level, std::move(due), seats),
          batteryKwh_(batteryKwh), kwhRate_(kwhRate) {}
    double charge(int days) const override {
        return dailyRate() * days + batteryKwh_ * kwhRate_;
    }
    std::string type() const override { return "Electric car"; }
};
class ElectricBus : public MotorVehicle {
    int seats_;
    double batteryKwh_;
    double kwhRate_;
public:
    ElectricBus(std::string reg, double rate, double level, std::string due,
                int seats, double batteryKwh, double kwhRate)
        : MotorVehicle(std::move(reg), rate, level, std::move(due)),
          seats_(seats), batteryKwh_(batteryKwh), kwhRate_(kwhRate) {}
    double charge(int days) const override {
        return dailyRate() * days + batteryKwh_ * kwhRate_;
    }
    std::string type() const override { return "Electric bus"; }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("B-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("T-201", 300, 5, "2026-12-01"));
    fleet.push_back(std::make_unique<Car>("C-301", 1200, 20, "2026-12-10", 5));
    fleet.push_back(std::make_unique<ElectricCar>("E-401", 1500, 80, "2026-12-15", 5, 40, 8));
    fleet.push_back(std::make_unique<ElectricBus>("EB-501", 4000, 70, "2026-12-20", 30, 120, 7));

    for (const auto& vehicle : fleet) {
        vehicle->rent();
        std::cout << vehicle->type() << " " << vehicle->registration()
                  << " charge for 2 days: Rs " << std::fixed
                  << std::setprecision(2) << vehicle->charge(2) << '\n';
        const int lateDays = (vehicle->registration() == "C-301") ? 2 : 0;
        std::cout << "Late fee: Rs " << vehicle->returnVehicle(lateDays) << '\n';
    }
}
