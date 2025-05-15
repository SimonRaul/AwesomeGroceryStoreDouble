//
// Created by Simon Raul on 5/2/2025.
//

#ifndef BASICUI_H
#define BASICUI_H

#include <string>
#include "../../User/Domain/User.h"

using namespace std;
using namespace userdomain;

namespace basicUI {
    class BasicUI {
    private:
        User new_user;
    public:
        //Constructor
        BasicUI() = default;

        //Messages
        string display_start_message();
        string dispaly_main_menu();

        //Method to set the name and forename of the new user
        void insert_informations();

        //Run method
        void run();
    };
}



#endif //BASICUI_H
