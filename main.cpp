#include "MetricsCalculator.h"
#include <iostream>

int main() {
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                         РАСЧЁТ МЕТРИК ООП ДЛЯ IT-COMPANY                                  ║" << std::endl;
    std::cout << "║                        Семинар 7-8 | Метрики Чидамбера-Кемерера и Абреу                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    MetricsCalculator calculator;
    calculator.printAll();
    
    std::cout << "\n" << std::string(120, '=') << std::endl;
    std::cout << "                              РАСЧЁТ ЗАВЕРШЁН" << std::endl;
    std::cout << std::string(120, '=') << std::endl;
    
    return 0;
}