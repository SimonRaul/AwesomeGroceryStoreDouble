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
    : current_user(new User(name, forename)), cus_repo(Customer_Repo::Customer_Repo("clients.txt")){}

//Login method implementation
void UserController::login(string introduced_email, string introduced_password) {
    string email, password, role;

    ifstream file("Accounts");
    while (getline(file, email, ':') && getline(file, password, ':')
        && getline(file, role)) {
        if (introduced_email == email && introduced_password == password) {
            if (role ==  "employee") {
                try {
                    Employee emp = emp_repo.find_by_email(email);
                    current_user = make_unique<Employee>(emp);
                    cout << "Logged in as an Employee" << endl;
                } catch (const exception& e) {
                    cerr << "Employee login error: " << e.what() << endl;
                }
            }
            if (role == "client") {
                try {
                    Customer cli = cus_repo.find_by_email(email);
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

bool UserController::update_password(string introduced_email, string old_password, string new_password) {
    string email, password, role;
    vector<string> updated_lines;

    bool changed = false;
    ifstream file("Accounts");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, email, ':');
        getline(ss, password, ':');
        getline(ss, role);
        if (introduced_email == email && old_password == password) {
            changed = true;
            password = new_password;
            updated_lines.push_back(email + ":" + password + ":" + role);
        }
        else {
            updated_lines.push_back(email + ":" + password + ":" + role);
        }
    }

    file.close();
    ofstream out_file("Accounts");

    for (const auto& updatedLine : updated_lines) {
        out_file << updatedLine << '\n';
    }
    out_file.close();

    if (!changed) {
        cout << "The email or old password are wrong, please try again!" << endl;
    }

    return changed;
}

unique_ptr<User> UserController::get_current_user() {
    return move(current_user);
}

template<typename Entity>
void UserController::set_current_user(Entity& user) {
    current_user = make_unique<Entity>(user);
}

bool UserController::create_account(const string &name, const string &forename,
        const string &introduced_email, const string &introduced_password, const string &address) {
    string email, password, role;
    vector<string> initial_lines;

    ifstream file("Accounts");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, email, ':');
        getline(ss, password, ':');
        getline(ss, role);
        initial_lines.push_back(email + ":" + password + ":" + role);
    }
    file.close();

    shared_ptr<Customer> new_cus = cus_repo.create(name, forename, introduced_email, introduced_password, address);

    initial_lines.push_back(introduced_email + ":" + introduced_password + ":" + "client");

    ofstream out_file("Accounts");
    for (const auto& updatedLine : initial_lines) {
        out_file << updatedLine << '\n';
    }
    out_file.close();

    return true;
}

