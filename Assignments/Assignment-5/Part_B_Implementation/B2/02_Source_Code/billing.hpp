#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class BillingError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};
class ClaimError : public BillingError {
public: using BillingError::BillingError;
};
class UnknownPackageError : public BillingError {
public: using BillingError::BillingError;
};
class PatientNotFoundError : public BillingError {
public: using BillingError::BillingError;
};

class Bill {
    std::string id_, patient_;
protected:
    static void nonNegative(double x, const char* field) {
        if (!std::isfinite(x) || x < 0.0) throw std::invalid_argument(std::string("invalid ") + field);
    }
public:
    Bill(std::string id, std::string patient) : id_(std::move(id)), patient_(std::move(patient)) {
        if (patient_.empty()) throw PatientNotFoundError("missing patient record");
        if (id_.empty()) throw std::invalid_argument("empty bill id");
    }
    virtual ~Bill() noexcept = default;
    const std::string& id() const noexcept { return id_; }
    const std::string& patient() const noexcept { return patient_; }
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    void print() const { std::cout << type() << ' ' << patient() << ": " << total() << '\n'; }
};

class OutPatientBill : public Bill {
    double consultation_, tests_;
public:
    OutPatientBill(std::string id, std::string p, double c, double t)
        : Bill(std::move(id), std::move(p)), consultation_(c), tests_(t) {
        nonNegative(c, "consultation"); nonNegative(t, "tests");
    }
    double total() const override { return consultation_ + tests_; }
    std::string type() const override { return "OP"; }
};
class InPatientBill : public Bill {
    int days_; double room_, procedures_, medicines_;
public:
    InPatientBill(std::string id, std::string p, int d, double r, double pr, double m)
        : Bill(std::move(id), std::move(p)), days_(d), room_(r), procedures_(pr), medicines_(m) {
        if (d <= 0) throw std::invalid_argument("days must be positive");
        nonNegative(r,"room rate"); nonNegative(pr,"procedures"); nonNegative(m,"medicines");
    }
    double total() const override { return days_ * room_ + procedures_ + medicines_; }
    std::string type() const override { return "IP"; }
};
class DayCareBill : public Bill {
    double package_;
public:
    DayCareBill(std::string id, std::string p, double packagePrice)
        : Bill(std::move(id), std::move(p)), package_(packagePrice) { nonNegative(packagePrice,"package"); }
    double total() const override { return package_; }
    std::string type() const override { return "DAYCARE"; }
};
class EmergencyBill : public Bill {
    double base_, perMinute_; int minutes_;
public:
    EmergencyBill(std::string id, std::string p, double b, int minutes, double rate)
        : Bill(std::move(id), std::move(p)), base_(b), perMinute_(rate), minutes_(minutes) {
        nonNegative(b,"emergency base"); nonNegative(rate,"per-minute rate");
        if (minutes < 0) throw std::invalid_argument("negative emergency minutes");
    }
    double total() const override { return base_ + minutes_ * perMinute_; }
    std::string type() const override { return "EMERGENCY"; }
};

class Payer {
public:
    virtual ~Payer() noexcept = default;
    virtual double amountCovered(const Bill&) const = 0;
};
class SelfPay : public Payer {
public: double amountCovered(const Bill& b) const override { return b.total(); }
};
class Insurance : public Payer {
    double limit_, copayPercent_;
public:
    Insurance(double limit, double copay) : limit_(limit), copayPercent_(copay) {
        if (limit < 0 || copay < 0 || copay > 100) throw std::invalid_argument("invalid insurance policy");
    }
    double amountCovered(const Bill& b) const override {
        const double eligible = std::min(b.total(), limit_);
        return eligible * (100.0 - copayPercent_) / 100.0;
    }
};
class GovernmentScheme : public Payer {
    std::map<std::string,double> rates_;
public:
    explicit GovernmentScheme(std::map<std::string,double> rates) : rates_(std::move(rates)) {}
    double amountCovered(const Bill& b) const override {
        auto it = rates_.find(b.type());
        if (it == rates_.end()) throw UnknownPackageError("unknown package: " + b.type());
        return std::min(b.total(), it->second);
    }
};
class CorporatePayer : public Payer {
    double discount_;
public:
    explicit CorporatePayer(double discount) : discount_(discount) {
        if (discount < 0 || discount > 100) throw std::invalid_argument("invalid corporate discount");
    }
    double amountCovered(const Bill& b) const override { return b.total() * (100.0-discount_)/100.0; }
};
