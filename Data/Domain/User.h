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

        virtual ~User() = default;

        //Constructor
        User(string name = "", string forename = "", string email = "", string password = "");

        //Getters
        const string get_name();
        const string get_forename();
        const string get_email();
        const string get_password();

        //Setters
        void set_name(string new_name);
        void set_forename(string new_forname);
        void set_email(string new_email);
        void set_password(string new_password);
    };
}



#endif //USER_H
