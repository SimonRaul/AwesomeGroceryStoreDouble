//
// Created by ionut on 5/15/2025.
//

#ifndef EMPLOYEEUI_H
#define EMPLOYEEUI_H
#include <string>

#include "IPresentation.h"


class EmployeeUI: public IPresentation {
public:
    std::string main_menu() override;

    std::string order_menu();

    std::string account_menu();

    std::string user_menu();

    void create_instance() override;

    void remove_instance() override;

    void update_instance() override;
};



#endif //EMPLOYEEUI_H
