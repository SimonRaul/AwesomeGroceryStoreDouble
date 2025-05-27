include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

file(GLOB DOMAIN_SRC "../Data/Domain/*.cpp")
file(GLOB SERVICE_SRC "../Service/Controller/*.cpp")
File(GLOB REPO_SRC "../Data/Repo/*.cpp")
add_executable(runTests
        UserTests.cpp
        UserControllerTests.cpp
        CustomerTest.cpp
        EmployeeTest.cpp
        ProductTest.cpp
        OrderDomainTest.cpp
        ${DOMAIN_SRC}
        ${SERVICE_SRC}
        ${REPO_SRC}
)

target_include_directories(runTests PRIVATE ../)
target_link_libraries(runTests gtest gtest_main)

configure_file(${CMAKE_SOURCE_DIR}/Tests/AccountsTest AccountsTest COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Tests/clientsTest.txt clientsTest.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Tests/employees_test.txt employees_test.txt COPYONLY)

gtest_discover_tests(runTests)
