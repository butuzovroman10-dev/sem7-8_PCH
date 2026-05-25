cmake_minimum_required(VERSION 3.10)
project(it_company_metrics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(it_company_metrics
    main.cpp
    IWorkable.h
    Employee.h
    Developer.h
    Manager.h
    Tester.h
    MyContainer.h
    PendingQueue.h
    MetricsCalculator.h
)

target_include_directories(it_company_metrics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})