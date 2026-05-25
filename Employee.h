#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "IWorkable.h"
#include <string>
#include <iostream>

class Employee : public IWorkable {
protected:
    std::string name;
    int id;
    double baseSalary;

public:
    Employee(const std::string& n, int i, double salary)
        : name(n), id(i), baseSalary(salary) {}

    virtual ~Employee() = default;

    void work() const override = 0;
    double getEfficiency() const override = 0;

    std::string getName() const { return name; }
    int getId() const { return id; }
    double getSalary() const { return baseSalary; }
    
    virtual void displayInfo() const = 0;
    
    bool operator==(const Employee& other) const {
        return id == other.id;
    }
    
    bool operator<(const Employee& other) const {
        return id < other.id;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp) {
        emp.displayInfo();
        return os;
    }
};

#endif