//
// Created by Simon Raul on 5/2/2025.
//

#include "BasicUI.h"
#include <iostream>

using namespace basicUI;

//Displays the message that appears at the start of the program
string BasicUI::display_start_message() {
    return "Welcome!\n"
            "Please insert your name and forename\n";

}

//Method to set the name and forename of the new user
void BasicUI::insert_informations() {
    string name, forename;
    cout << "name: " << endl;
    cin >> name;
    cout << "forename: " << endl;
    cin >> forename;
    new_user.set_name(name);
    new_user.set_forename(forename);
}

//Displays the main menu
string BasicUI::dispaly_main_menu() {
    return "1 - Create an account\n"
            "2 - Log in\n";
}