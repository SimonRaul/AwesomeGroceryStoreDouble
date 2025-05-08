cmake_minimum_required(VERSION 3.31)
project(AwesomeGroceryStoreDouble)

set(CMAKE_CXX_STANDARD 20)

add_executable(AwesomeGroceryStoreDouble main.cpp
        User/Domain/User.h
        User/Domain/User.cpp
        User/Controller/UserController.h
        User/Controller/UserController.cpp
        Program/UI/BasicUI.h
        Program/UI/BasicUI.cpp)
