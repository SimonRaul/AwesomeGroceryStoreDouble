//
// Created by Simon Raul on 5/2/2025.
//

#ifndef BASICUI_H
#define BASICUI_H

#include <string>
#include "../../Service/Controller//UserController.h"
#include "Customer_UI.h"
#include "EmployeeUI.h"

using namespace std;
using namespace userdomain;
using namespace usercontroller;

namespace basicUI {
    class BasicUI {
        friend class Customer_UI;
        friend class EmployeeUI;
    private:
        string name, forename;
        Customer_UI cus_ui;
        EmployeeUI emp_ui;
        UserController user_crt{ name, forename, "Accounts",
            "clients.txt", "employees.txt"};
    public:
        //Constructor
        BasicUI();

        //Messages
        string display_start_message();
        string dispaly_main_menu();

        //Method to set the name and forename of the new user
        pair<string,string> insert_name_and_forename();
        pair<string,string> insert_email_and_password();

        //Run method
        void run_program();
    };
}



#endif //BASICUI_H
