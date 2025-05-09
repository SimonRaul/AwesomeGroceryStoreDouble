//
// Created by Simon Raul on 4/30/2025.
//

#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

namespace userdomain {
    class User {
    private:
        string name;
        string forename;
        string email;
        string password;

    public:
        //Constructor
        User(string name = "", string forename = "", string email = "", string password = "");

        //Getters
        string get_name();
        string get_forename();
        string get_email();
        string get_password();

        //Setters
        void set_name(string new_name);
        void set_forename(string new_forname);
        void set_email(string new_email);
        void set_password(string new_password);
    };
}



#endif //USER_H
