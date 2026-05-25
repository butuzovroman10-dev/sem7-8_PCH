#ifndef IWORKABLE_H
#define IWORKABLE_H

#include <iostream>

class IWorkable {
public:
    virtual void work() const = 0;
    virtual double getEfficiency() const = 0;
    virtual ~IWorkable() = default;
};

#endif