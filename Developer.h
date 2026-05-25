#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "Employee.h"
#include <algorithm>

class Developer : public Employee {
private:
    std::string programmingLanguage;
    int linesOfCodePerDay;

public:
    Developer(const std::string& n, int i, double salary,
              const std::string& lang, int loc)
        : Employee(n, i, salary), programmingLanguage(lang), linesOfCodePerDay(loc) {}

    void work() const override {
        std::cout << "Developer " << name << " writes " << linesOfCodePerDay
                  << " lines of " << programmingLanguage << " code" << std::endl;
    }

    double getEfficiency() const override {
        return std::min(1.0, linesOfCodePerDay / 500.0);
    }

    void displayInfo() const override {
        std::cout << "Developer: " << name << " (ID: " << id
                  << ", Salary: $" << baseSalary
                  << ", Language: " << programmingLanguage
                  << ", LOC/day: " << linesOfCodePerDay << ")";
    }
    
    std::string getProgrammingLanguage() const { return programmingLanguage; }
};

#endif