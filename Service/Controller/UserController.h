//
// Created by Simon Raul on 5/2/2025.
//

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include <memory>
#include "../../Data/Domain/User.h"
#include "../../Data/Repo/Customer_Repo.h"
#include "../../Data/Repo/EmployeeRepo.h"

using namespace userdomain;

namespace usercontroller {
    class UserController {
    private:
        employeerepo::EmployeeRepository emp_repo;
        Customer_Repo::Customer_Repo cus_repo;
        unique_ptr<User> current_user = nullptr;
    public:
        //Constructor
        UserController(string name, string forename);

        //login related methods
        void login(string introduced_email, string introduced_password);
        bool is_logged_in();
        bool update_password(string introduced_email, string old_password, string new_password);
    };
}



#endif //USERCONTROLLER_H
