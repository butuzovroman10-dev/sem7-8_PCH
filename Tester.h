#ifndef TESTER_H
#define TESTER_H

#include "Employee.h"
#include <algorithm>

class Tester : public Employee {
private:
    int bugsFoundPerDay;
    std::string testingTool;

public:
    Tester(const std::string& n, int i, double salary, int bugs, const std::string& tool)
        : Employee(n, i, salary), bugsFoundPerDay(bugs), testingTool(tool) {}

    void work() const override {
        std::cout << "Tester " << name << " finds " << bugsFoundPerDay
                  << " bugs using " << testingTool << std::endl;
    }

    double getEfficiency() const override {
        return std::min(1.0, bugsFoundPerDay / 20.0);
    }

    void displayInfo() const override {
        std::cout << "Tester: " << name << " (ID: " << id
                  << ", Salary: $" << baseSalary
                  << ", Bugs/day: " << bugsFoundPerDay
                  << ", Tool: " << testingTool << ")";
    }
    
    int getBugsFoundPerDay() const { return bugsFoundPerDay; }
};

#endif