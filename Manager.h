#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include <algorithm>

class Manager : public Employee {
private:
    int teamSize;
    int meetingsPerDay;

public:
    Manager(const std::string& n, int i, double salary, int team, int meetings)
        : Employee(n, i, salary), teamSize(team), meetingsPerDay(meetings) {}

    void work() const override {
        std::cout << "Manager " << name << " conducts " << meetingsPerDay
                  << " meetings and manages a team of " << teamSize << " people" << std::endl;
    }

    double getEfficiency() const override {
        return std::min(1.0, teamSize / 10.0);
    }

    void displayInfo() const override {
        std::cout << "Manager: " << name << " (ID: " << id
                  << ", Salary: $" << baseSalary
                  << ", Team size: " << teamSize
                  << ", Meetings/day: " << meetingsPerDay << ")";
    }
    
    int getTeamSize() const { return teamSize; }
};

#endif