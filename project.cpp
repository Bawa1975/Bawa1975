#include <iostream>
#include <string>

// Abstract Person Class
class Person {
protected:
    std::string name;
    int age;
    std::string address;
    std::string phone;
    std::string email;

public:
    Person(const std::string& name, int age, const std::string& address, const std::string& phone, const std::string& email)
        : name(name), age(age), address(address), phone(phone), email(email) {}

    virtual std::string toString() const = 0;
    virtual bool equals(const Person& other) const = 0;
    virtual std::string getCategory() const = 0;
};

// PayRoll Interface
class PayRoll {
public:
    virtual double computePayRoll() const = 0;
};

// Teacher Class (Derived from Person and PayRoll)
class Teacher : public Person, public PayRoll {
private:
    std::string specialty;
    std::string degree;
    bool fullTime;
    int hoursWorked; 

public:
    Teacher(const std::string& name, int age, const std::string& address, const std::string& phone, const std::string& email,
            const std::string& specialty, const std::string& degree, bool fullTime, int hoursWorked = 0)
        : Person(name, age, address, phone, email), specialty(specialty), degree(degree), 
          fullTime(fullTime), hoursWorked(hoursWorked) {}

    std::string toString() const override {
        return "Teacher: " + name + " (" + std::to_string(age) + "), Specialty: " + specialty + 
               ", Degree: " + degree + ", Full-time: " + (fullTime ? "Yes" : "No");
    }

    bool equals(const Person& other) const override {
        const Teacher* otherTeacher = dynamic_cast<const Teacher*>(&other);
        return otherTeacher && Person::equals(other) && specialty == otherTeacher->specialty && degree == otherTeacher->degree;
    }

    std::string getCategory() const override {
        return "Teacher";
    }

    double computePayRoll() const override {
        double degreeRate = (degree == "PhD") ? 112 : (degree == "Master") ? 82 : 42;
        if (fullTime) {
            return (32 * degreeRate * 2) * 0.85;
        } else {
            return (hoursWorked * degreeRate * 2) * 0.76;
        }
    }
};

// Staff Class (Derived from Person and PayRoll)
class Staff : public Person, public PayRoll {
private:
    std::string duty;
    int workload;

public:
    Staff(const std::string& name, int age, const std::string& address, const std::string& phone, const std::string& email,
          const std::string& duty, int workload)
        : Person(name, age, address, phone, email), duty(duty), workload(workload < 40 ? workload : 40) {}

    std::string toString() const override {
        return "Staff: " + name + " (" + std::to_string(age) + "), Duty: " + duty + ", Workload: " + std::to_string(workload);
    }

    bool equals(const Person& other) const override {
        const Staff* otherStaff = dynamic_cast<const Staff*>(&other);
        return otherStaff && Person::equals(other) && duty == otherStaff->duty;
    }

    std::string getCategory() const override {
        return "Staff";
    }

    double computePayRoll() const override {
        return (workload * 32 * 2) * 0.75;
    }
};


