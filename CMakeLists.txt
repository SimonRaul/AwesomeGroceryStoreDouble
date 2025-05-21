cmake_minimum_required(VERSION 3.31)
project(AwesomeGroceryStoreDouble)

set(CMAKE_CXX_STANDARD 20)

add_executable(AwesomeGroceryStoreDouble main.cpp
        Data/Domain/User.h
        Data/Domain/User.cpp
        Service/Controller/UserController.h
        Service/Controller/UserController.cpp
        Presentation/UI/BasicUI.h
        Presentation/UI/BasicUI.cpp
        Data/Repo/OrderRepo.h
        Data/Repo/OrderRepo.cpp
        Data/Repo/ProductRepository.h
        Data/Repo/ProductRepository.cpp
        Data/Domain/Product.h
        Data/Domain/Product.cpp
        Data/Domain/OrderDomain.h
        Data/Domain/OrderDomain.cpp
        Service/Controller/OrderController.h
        Service/Controller/OrderController.cpp
        Data/Domain/Employee.h
        Data/Domain/Employee.cpp
        Data/Repo/EmployeeRepo.h
        Data/Repo/EmployeeRepo.cpp
        Data/Domain/Customer.h
        Data/Domain/Customer.cpp
        Data/Repo/Customer_Repo.h
        Data/Repo/Customer_Repo.cpp
        Data/Repo/IRepo.h
        Presentation/UI/IPresentation.h
        Presentation/UI/Customer_UI.h
        Presentation/UI/EmployeeUI.h
        Presentation/UI/EmployeeUI.cpp
        Presentation/UI/Customer_UI.cpp
        Service/Controller/ProductController.h
        Service/Controller/ProductController.cpp)
