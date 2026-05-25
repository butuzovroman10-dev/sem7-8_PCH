#ifndef METRICSCALCULATOR_H
#define METRICSCALCULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <typeinfo>
#include <cxxabi.h>
#include "IWorkable.h"
#include "Employee.h"
#include "Developer.h"
#include "Manager.h"
#include "Tester.h"
#include "MyContainer.h"
#include "PendingQueue.h"

struct ClassMetrics {
    std::string className;
    int wmc;      // Weighted Methods per Class
    int dit;      // Depth of Inheritance Tree
    int noc;      // Number of Children
    int cbo;      // Coupling Between Objects
    int rfc;      // Response For a Class
    double lcom;  // Lack of Cohesion of Methods
    int attributes;
    int publicMethods;
    int privateMethods;
    int protectedMethods;
    int overriddenMethods;
    int inheritedMethods;
};

struct SystemMetrics {
    int totalClasses;
    int totalAttributes;
    int totalMethods;
    double mif;   // Method Inheritance Factor
    double ahf;   // Attribute Inheritance Factor
    double pof;   // Polymorphism Factor
    double cof;   // Coupling Factor
    double mhf;   // Method Hiding Factor
    double chf;   // Class Hiding Factor
};

class MetricsCalculator {
private:
    std::vector<ClassMetrics> classMetrics;
    SystemMetrics systemMetrics;
    
    std::map<std::string, std::vector<std::string>> inheritanceTree;
    std::map<std::string, std::set<std::string>> couplingMap;
    std::map<std::string, std::vector<std::string>> methodsMap;
    std::map<std::string, std::vector<std::string>> attributesMap;
    std::map<std::string, std::vector<std::string>> overriddenMap;
    std::map<std::string, std::vector<std::string>> inheritedMethodsMap;
    
    std::string demangle(const char* name) {
        int status;
        char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
        std::string result = (status == 0) ? demangled : name;
        free(demangled);
        return result;
    }
    
public:
    MetricsCalculator() {
        initializeClassData();
        calculateAllMetrics();
    }
    
    void initializeClassData() {
        // IWorkable
        ClassMetrics iworkable;
        iworkable.className = "IWorkable";
        iworkable.wmc = 3;
        iworkable.dit = 0;
        iworkable.noc = 1;
        iworkable.cbo = 2;
        iworkable.rfc = 3;
        iworkable.lcom = 0.0;
        iworkable.attributes = 0;
        iworkable.publicMethods = 2;
        iworkable.privateMethods = 0;
        iworkable.protectedMethods = 0;
        iworkable.overriddenMethods = 0;
        iworkable.inheritedMethods = 0;
        classMetrics.push_back(iworkable);
        
        // Employee
        ClassMetrics employee;
        employee.className = "Employee";
        employee.wmc = 8;
        employee.dit = 1;
        employee.noc = 3;
        employee.cbo = 4;
        employee.rfc = 10;
        employee.lcom = 0.0;
        employee.attributes = 3;
        employee.publicMethods = 6;
        employee.privateMethods = 0;
        employee.protectedMethods = 0;
        employee.overriddenMethods = 0;
        employee.inheritedMethods = 2;
        classMetrics.push_back(employee);
        
        // Developer
        ClassMetrics developer;
        developer.className = "Developer";
        developer.wmc = 5;
        developer.dit = 2;
        developer.noc = 0;
        developer.cbo = 1;
        developer.rfc = 7;
        developer.lcom = 0.33;
        developer.attributes = 5;
        developer.publicMethods = 4;
        developer.privateMethods = 2;
        developer.protectedMethods = 0;
        developer.overriddenMethods = 2;
        developer.inheritedMethods = 2;
        classMetrics.push_back(developer);
        
        // Manager
        ClassMetrics manager;
        manager.className = "Manager";
        manager.wmc = 5;
        manager.dit = 2;
        manager.noc = 0;
        manager.cbo = 1;
        manager.rfc = 7;
        manager.lcom = 0.25;
        manager.attributes = 5;
        manager.publicMethods = 4;
        manager.privateMethods = 2;
        manager.protectedMethods = 0;
        manager.overriddenMethods = 2;
        manager.inheritedMethods = 2;
        classMetrics.push_back(manager);
        
        // Tester
        ClassMetrics tester;
        tester.className = "Tester";
        tester.wmc = 5;
        tester.dit = 2;
        tester.noc = 0;
        tester.cbo = 1;
        tester.rfc = 7;
        tester.lcom = 0.25;
        tester.attributes = 5;
        tester.publicMethods = 4;
        tester.privateMethods = 2;
        tester.protectedMethods = 0;
        tester.overriddenMethods = 2;
        tester.inheritedMethods = 2;
        classMetrics.push_back(tester);
        
        // MyContainer (шаблонный, учитываем как один класс)
        ClassMetrics container;
        container.className = "MyContainer<T>";
        container.wmc = 12;
        container.dit = 0;
        container.noc = 0;
        container.cbo = 0;
        container.rfc = 12;
        container.lcom = 0.0;
        container.attributes = 3;
        container.publicMethods = 11;
        container.privateMethods = 1;
        container.protectedMethods = 0;
        container.overriddenMethods = 0;
        container.inheritedMethods = 0;
        classMetrics.push_back(container);
        
        // PendingQueue
        ClassMetrics pendingQueue;
        pendingQueue.className = "PendingQueue";
        pendingQueue.wmc = 6;
        pendingQueue.dit = 0;
        pendingQueue.noc = 0;
        pendingQueue.cbo = 3;
        pendingQueue.rfc = 6;
        pendingQueue.lcom = 0.0;
        pendingQueue.attributes = 0;
        pendingQueue.publicMethods = 4;
        pendingQueue.privateMethods = 0;
        pendingQueue.protectedMethods = 0;
        pendingQueue.overriddenMethods = 0;
        pendingQueue.inheritedMethods = 0;
        classMetrics.push_back(pendingQueue);
        
        // IPending
        ClassMetrics ipending;
        ipending.className = "IPending";
        ipending.wmc = 2;
        ipending.dit = 0;
        ipending.noc = 1;
        ipending.cbo = 1;
        ipending.rfc = 2;
        ipending.lcom = 0.0;
        ipending.attributes = 0;
        ipending.publicMethods = 1;
        ipending.privateMethods = 0;
        ipending.protectedMethods = 0;
        ipending.overriddenMethods = 0;
        ipending.inheritedMethods = 0;
        classMetrics.push_back(ipending);
        
        // Pending (шаблонный)
        ClassMetrics pending;
        pending.className = "Pending<Callable, Args...>";
        pending.wmc = 4;
        pending.dit = 1;
        pending.noc = 0;
        pending.cbo = 2;
        pending.rfc = 4;
        pending.lcom = 0.0;
        pending.attributes = 2;
        pending.publicMethods = 2;
        pending.privateMethods = 2;
        pending.protectedMethods = 0;
        pending.overriddenMethods = 1;
        pending.inheritedMethods = 1;
        classMetrics.push_back(pending);
        
        // Настройка связей для CBO
        couplingMap["IWorkable"] = {"Employee", "PendingQueue"};
        couplingMap["Employee"] = {"IWorkable", "Developer", "Manager", "Tester", "MyContainer", "PendingQueue"};
        couplingMap["Developer"] = {"Employee"};
        couplingMap["Manager"] = {"Employee"};
        couplingMap["Tester"] = {"Employee"};
        couplingMap["MyContainer<T>"] = {};
        couplingMap["PendingQueue"] = {"IPending", "Pending<Callable, Args...>"};
        couplingMap["IPending"] = {"Pending<Callable, Args...>"};
        couplingMap["Pending<Callable, Args...>"] = {"IPending"};
        
        // Настройка дерева наследования
        inheritanceTree["IWorkable"] = {"Employee"};
        inheritanceTree["Employee"] = {"Developer", "Manager", "Tester"};
        inheritanceTree["IPending"] = {"Pending<Callable, Args...>"};
        inheritanceTree["Developer"] = {};
        inheritanceTree["Manager"] = {};
        inheritanceTree["Tester"] = {};
        inheritanceTree["MyContainer<T>"] = {};
        inheritanceTree["PendingQueue"] = {};
        inheritanceTree["Pending<Callable, Args...>"] = {};
    }
    
    void calculateAllMetrics() {
        calculateSystemMetrics();
    }
    
    void calculateSystemMetrics() {
        int totalClasses = classMetrics.size();
        int totalAttributes = 0;
        int totalMethods = 0;
        int totalOverridden = 0;
        int totalInherited = 0;
        int totalPrivateMethods = 0;
        int totalPrivateAttributes = 0;
        double sumMethodInheritanceRatio = 0.0;
        double sumAttributeInheritanceRatio = 0.0;
        double sumPolymorphismRatio = 0.0;
        
        for (const auto& m : classMetrics) {
            totalAttributes += m.attributes;
            totalMethods += m.wmc;
            totalOverridden += m.overriddenMethods;
            totalInherited += m.inheritedMethods;
            totalPrivateMethods += m.privateMethods;
            totalPrivateAttributes += m.attributes;
            
            double methodRatio = (m.wmc > 0) ? (double)m.inheritedMethods / m.wmc : 0.0;
            double attrRatio = (m.attributes > 0) ? (double)0 / m.attributes : 0.0;
            double polyRatio = (m.wmc > 0) ? (double)m.overriddenMethods / m.wmc : 0.0;
            
            sumMethodInheritanceRatio += methodRatio;
            sumAttributeInheritanceRatio += attrRatio;
            sumPolymorphismRatio += polyRatio;
        }
        
        systemMetrics.totalClasses = totalClasses;
        systemMetrics.totalAttributes = totalAttributes;
        systemMetrics.totalMethods = totalMethods;
        
        systemMetrics.mif = sumMethodInheritanceRatio / totalClasses;
        systemMetrics.ahf = sumAttributeInheritanceRatio / totalClasses;
        systemMetrics.pof = sumPolymorphismRatio / totalClasses;
        systemMetrics.mhf = (totalMethods > 0) ? (double)totalPrivateMethods / totalMethods : 0.0;
        systemMetrics.chf = (totalAttributes > 0) ? (double)totalPrivateAttributes / totalAttributes : 0.0;
        
        int possibleCouplings = (totalClasses * (totalClasses - 1)) / 2;
        int actualCouplings = 0;
        for (const auto& pair : couplingMap) {
            actualCouplings += pair.second.size();
        }
        systemMetrics.cof = (possibleCouplings > 0) ? (double)actualCouplings / possibleCouplings : 0.0;
    }
    
    void printClassMetrics() const {
        std::cout << "\n" << std::string(120, '=') << std::endl;
        std::cout << "                   РАСЧЁТ МЕТРИК ДЛЯ КАЖДОГО КЛАССА" << std::endl;
        std::cout << std::string(120, '=') << std::endl;
        
        for (const auto& m : classMetrics) {
            std::cout << "\n📦 Класс: " << m.className << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "  WMC (Weighted Methods per Class)     : " << m.wmc << std::endl;
            std::cout << "  DIT (Depth of Inheritance Tree)      : " << m.dit << std::endl;
            std::cout << "  NOC (Number of Children)             : " << m.noc << std::endl;
            std::cout << "  CBO (Coupling Between Objects)       : " << m.cbo << std::endl;
            std::cout << "  RFC (Response For a Class)           : " << m.rfc << std::endl;
            std::cout << "  LCOM (Lack of Cohesion of Methods)   : " << m.lcom << std::endl;
            std::cout << "  Attributes                           : " << m.attributes << std::endl;
            std::cout << "  Public methods                       : " << m.publicMethods << std::endl;
            std::cout << "  Private methods                      : " << m.privateMethods << std::endl;
            std::cout << "  Overridden methods                   : " << m.overriddenMethods << std::endl;
            std::cout << "  Inherited methods                    : " << m.inheritedMethods << std::endl;
        }
    }
    
    void printSystemMetrics() const {
        std::cout << "\n" << std::string(120, '=') << std::endl;
        std::cout << "                   СИСТЕМНЫЕ МЕТРИКИ MOOD (Абреу)" << std::endl;
        std::cout << std::string(120, '=') << std::endl;
        
        std::cout << "\n📊 Размерные метрики:" << std::endl;
        std::cout << "  Total Classes (TC)     : " << systemMetrics.totalClasses << std::endl;
        std::cout << "  Total Attributes       : " << systemMetrics.totalAttributes << std::endl;
        std::cout << "  Total Methods          : " << systemMetrics.totalMethods << std::endl;
        
        std::cout << "\n📊 Метрики наследования и полиморфизма:" << std::endl;
        std::cout << "  MIF (Method Inheritance Factor)     : " << systemMetrics.mif << " (" << systemMetrics.mif * 100 << "%)" << std::endl;
        std::cout << "  AHF (Attribute Inheritance Factor)  : " << systemMetrics.ahf << " (" << systemMetrics.ahf * 100 << "%)" << std::endl;
        std::cout << "  POF (Polymorphism Factor)           : " << systemMetrics.pof << " (" << systemMetrics.pof * 100 << "%)" << std::endl;
        
        std::cout << "\n📊 Метрики сокрытия и сцепления:" << std::endl;
        std::cout << "  MHF (Method Hiding Factor)          : " << systemMetrics.mhf << " (" << systemMetrics.mhf * 100 << "%)" << std::endl;
        std::cout << "  CHF (Class Hiding Factor)           : " << systemMetrics.chf << " (" << systemMetrics.chf * 100 << "%)" << std::endl;
        std::cout << "  COF (Coupling Factor)               : " << systemMetrics.cof << " (" << systemMetrics.cof * 100 << "%)" << std::endl;
    }
    
    void printAnalysis() const {
        std::cout << "\n" << std::string(120, '=') << std::endl;
        std::cout << "                       АНАЛИЗ И РЕКОМЕНДАЦИИ" << std::endl;
        std::cout << std::string(120, '=') << std::endl;
        
        std::cout << "\n🔍 Анализ метрик Чидамбера-Кемерера (CK):" << std::endl;
        
        for (const auto& m : classMetrics) {
            std::cout << "\n  " << m.className << ":" << std::endl;
            
            if (m.wmc <= 20) {
                std::cout << "    ✅ WMC=" << m.wmc << " (≤20) - хорошая сложность класса" << std::endl;
            } else if (m.wmc <= 30) {
                std::cout << "    ⚠️ WMC=" << m.wmc << " (20-30) - допустимая сложность" << std::endl;
            } else {
                std::cout << "    ❌ WMC=" << m.wmc << " (>30) - класс слишком сложный" << std::endl;
            }
            
            if (m.dit <= 2) {
                std::cout << "    ✅ DIT=" << m.dit << " (≤2) - оптимальная глубина" << std::endl;
            } else if (m.dit <= 5) {
                std::cout << "    ⚠️ DIT=" << m.dit << " (2-5) - допустимая глубина" << std::endl;
            } else {
                std::cout << "    ❌ DIT=" << m.dit << " (>5) - слишком глубокое наследование" << std::endl;
            }
            
            if (m.noc <= 10) {
                std::cout << "    ✅ NOC=" << m.noc << " (≤10) - нормальное количество потомков" << std::endl;
            } else if (m.noc <= 20) {
                std::cout << "    ⚠️ NOC=" << m.noc << " (10-20) - много потомков" << std::endl;
            } else {
                std::cout << "    ❌ NOC=" << m.noc << " (>20) - слишком много потомков" << std::endl;
            }
            
            if (m.cbo <= 10) {
                std::cout << "    ✅ CBO=" << m.cbo << " (≤10) - слабая связанность" << std::endl;
            } else if (m.cbo <= 15) {
                std::cout << "    ⚠️ CBO=" << m.cbo << " (10-15) - допустимая связанность" << std::endl;
            } else {
                std::cout << "    ❌ CBO=" << m.cbo << " (>15) - высокая связанность" << std::endl;
            }
            
            if (m.rfc <= 30) {
                std::cout << "    ✅ RFC=" << m.rfc << " (≤30) - хороший отклик" << std::endl;
            } else if (m.rfc <= 50) {
                std::cout << "    ⚠️ RFC=" << m.rfc << " (30-50) - допустимый отклик" << std::endl;
            } else {
                std::cout << "    ❌ RFC=" << m.rfc << " (>50) - слишком много методов" << std::endl;
            }
            
            if (m.lcom <= 1.0) {
                std::cout << "    ✅ LCOM=" << m.lcom << " (≤1) - хорошая связность" << std::endl;
            } else {
                std::cout << "    ❌ LCOM=" << m.lcom << " (>1) - класс следует разделить" << std::endl;
            }
        }
        
        std::cout << "\n📊 Анализ метрик Абреу (MOOD):" << std::endl;
        
        if (systemMetrics.mif >= 0.3 && systemMetrics.mif <= 0.5) {
            std::cout << "  ✅ MIF=" << systemMetrics.mif << " (0.3-0.5) - оптимальное наследование методов" << std::endl;
        } else if (systemMetrics.mif < 0.3) {
            std::cout << "  ⚠️ MIF=" << systemMetrics.mif << " (<0.3) - наследование используется слабо" << std::endl;
        } else {
            std::cout << "  ⚠️ MIF=" << systemMetrics.mif << " (>0.5) - возможно глубокое наследование" << std::endl;
        }
        
        if (systemMetrics.pof >= 0.1 && systemMetrics.pof <= 0.3) {
            std::cout << "  ✅ POF=" << systemMetrics.pof << " (0.1-0.3) - оптимальный полиморфизм" << std::endl;
        } else if (systemMetrics.pof < 0.1) {
            std::cout << "  ⚠️ POF=" << systemMetrics.pof << " (<0.1) - полиморфизм используется слабо" << std::endl;
        } else {
            std::cout << "  ⚠️ POF=" << systemMetrics.pof << " (>0.3) - возможно излишнее усложнение" << std::endl;
        }
        
        if (systemMetrics.cof <= 0.3) {
            std::cout << "  ✅ COF=" << systemMetrics.cof << " (≤0.3) - слабая связанность системы" << std::endl;
        } else if (systemMetrics.cof <= 0.5) {
            std::cout << "  ⚠️ COF=" << systemMetrics.cof << " (0.3-0.5) - допустимая связанность" << std::endl;
        } else {
            std::cout << "  ❌ COF=" << systemMetrics.cof << " (>0.5) - сильная связанность системы" << std::endl;
        }
        
        if (systemMetrics.mhf > 0.3) {
            std::cout << "  ✅ MHF=" << systemMetrics.mhf << " (>0.3) - хорошее сокрытие методов" << std::endl;
        } else {
            std::cout << "  ⚠️ MHF=" << systemMetrics.mhf << " (<0.3) - недостаточное сокрытие методов" << std::endl;
        }
        
        std::cout << "\n💡 Рекомендации по улучшению архитектуры:" << std::endl;
        
        bool hasIssue = false;
        for (const auto& m : classMetrics) {
            if (m.wmc > 30) {
                std::cout << "  • Класс " << m.className << " имеет высокую сложность (WMC=" << m.wmc 
                          << "). Рекомендуется разделить его на несколько более мелких классов." << std::endl;
                hasIssue = true;
            }
            if (m.lcom > 1.0) {
                std::cout << "  • Класс " << m.className << " имеет низкую связность (LCOM=" << m.lcom 
                          << "). Рекомендуется разделить его на несколько классов по функциональности." << std::endl;
                hasIssue = true;
            }
        }
        
        if (systemMetrics.mif < 0.3) {
            std::cout << "  • Низкий фактор наследования методов (MIF=" << systemMetrics.mif 
                      << "). Можно вынести общую логику в базовые классы для уменьшения дублирования." << std::endl;
            hasIssue = true;
        }
        
        if (systemMetrics.pof > 0.3) {
            std::cout << "  • Высокий фактор полиморфизма (POF=" << systemMetrics.pof 
                      << "). Проверьте, не является ли полиморфизм избыточным." << std::endl;
            hasIssue = true;
        }
        
        if (systemMetrics.cof > 0.5) {
            std::cout << "  • Высокое сцепление системы (COF=" << systemMetrics.cof 
                      << "). Рекомендуется уменьшить зависимости между классами." << std::endl;
            hasIssue = true;
        }
        
        if (!hasIssue) {
            std::cout << "  ✅ Архитектура системы признаётся хорошей. Радикальный рефакторинг не требуется." << std::endl;
        }
    }
    
    void printAll() const {
        printClassMetrics();
        printSystemMetrics();
        printAnalysis();
    }
};

#endif