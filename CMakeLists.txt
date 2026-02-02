cmake_minimum_required(VERSION 3.16)
project(WorkerManageSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WorkerManageSystem
    src/main.cpp
    src/workerManager.cpp
    src/employee.cpp
    src/manager.cpp
    src/boss.cpp
)

target_include_directories(WorkerManageSystem PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
