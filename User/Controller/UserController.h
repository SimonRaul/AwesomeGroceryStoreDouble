//
// Created by Simon Raul on 5/2/2025.
//

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include <memory>
#include "../Domain/User.h"
#include "../../Customer/Repo/Customer_Repo.h"
#include "../../Employee/Repo/EmployeeRepo.h"

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
        bool update_password(string email, string password);
    };
}



#endif //USERCONTROLLER_H
