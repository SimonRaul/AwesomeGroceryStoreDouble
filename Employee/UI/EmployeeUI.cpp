//
// Created by ionut on 5/15/2025.
//

#include "EmployeeUI.h"

std::string EmployeeUI::main_menu() {
    return "Choose an option:\n1 - Order management\n2 - Client management\n3 - Account management\n4 - Exit\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}

std::string EmployeeUI::order_menu() {
    return "Choose an option:\n1 - List reservations\n2 - Process order by ID\n3 - Mark order as completed\n4 - Delete orders\n5 - Back\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}

std::string EmployeeUI::account_menu() {
    return "Choose an option:\n1 - Edit password\n2 - Edit details\n3 - Back\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}

std::string EmployeeUI::user_menu() {
    return "Choose an option:\n1 - List clients\n2 - Edit client by ID\n3 - Add client\n4 - Remove client\n5 - Back\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}