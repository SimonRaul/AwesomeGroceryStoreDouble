//
// Created by Simon Raul on 5/2/2025.
//

#include "UserController.h"
#include <iostream>
#include <fstream>

using namespace usercontroller;
using namespace std;
using namespace employeerepo;

//Constructor implementation
UserController::UserController(string name, string forename)
    : current_user(new User(name, forename)){}

//Login method implementation
void UserController::login(string introduced_email, string introduced_password) {
    string email, password, role;

    ifstream file("Accounts");
    while (getline(file, email, ':') && getline(file, password, ':')
        && getline(file, role)) {
        if (introduced_email == email && introduced_password == password) {
            if (role ==  "employee") {
                try {
                    Employee emp = emp_repo.find_employee_by_email(email);
                    current_user = make_unique<Employee>(emp);
                    cout << "Logged in as an Employee" << endl;
                } catch (const exception& e) {
                    cerr << "Employee login error: " << e.what() << endl;
                }
            }
            if (role == "client") {
                try {
                    Customer cli = cus_repo.find_client_by_email(email);
                    current_user = make_unique<Customer>(cli);
                    cout << "Logged in as Customer" << endl;
                } catch (const exception& e) {
                    cerr << "Customer login error: " << e.what() << endl;
                }
            }
            file.close();
            return;
        }
    }

    file.close();
    cout << "The email or password are wrong, please try again!" << endl;
}

//verifies if the current user is logged in or not
bool UserController::is_logged_in() {
    if (current_user != nullptr) {
        cout << "You are allready logged in." << endl;
        return true;
    }
    cout << "You are not logged in." << endl;
    return false;
}

