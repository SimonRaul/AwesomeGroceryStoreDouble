//
// Created by Simon Raul on 4/30/2025.
//

#include "User.h"

using namespace userdomain;

//Constrcutor implementation
User::User(string name, string forename, string email, string password)
    : name(name), forename(forename), email(email), password(password) {}

//Name getter
string User::get_name() {
    return name;
}

//Forename getter
string User::get_forename() {
    return forename;
}


//Email getter
string User::get_email() {
    return email;
}

//Password getter
string User::get_password() {
    return password;
}

//Name setter
void User::set_name(string new_name) {
    name = new_name;
}

//Forename setter
void User::set_forename(string new_forname) {
    forename = new_forname;
}

//Email setter
void User::set_email(string new_email) {
    email = new_email;
}

//Password setter
void User::set_password(string new_password) {
    password = new_password;
}
