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

        //getters & setters
        unique_ptr<User> get_current_user();
        template<typename Entity>
        void set_current_user(Entity& user);

        bool create_account(const string &name, const string &forename,
        const string &introduced_email, const string &introduced_password, const string &address);
    };
}



#endif //USERCONTROLLER_H
