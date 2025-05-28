//
// Created by ionut on 5/15/2025.
//

#ifndef EMPLOYEEUI_H
#define EMPLOYEEUI_H
#include <string>

#include "IPresentation.h"
#include "../../Data/Repo/EmployeeRepo.h"
#include "../../Service/Controller/ClientManagementController.h"
#include "../../Service/Controller/OrderController.h"
#include "../../Service/Controller/ProductController.h"


class EmployeeUI: public IPresentation {
private:
    productcontroller::ProductController prod_contr;
    controller::OrderController order_contr;
    controller::ClientManagementController client_mgn;
public:
    EmployeeUI(const std::string& prod_file, const std::string& order_file, const std::string& cus_file);

    std::string main_menu() override;

    std::string client_menu();

    std::string product_menu();

    std::string order_menu();

    void run_main_menu(Employee *employee);

    void run_client_menu(Employee *employee);

    void run_order_menu(Employee *employee);

    void run_product_menu(Employee *employee);

    int input_integer();

    float input_float();

    std::string input_string();

    void create_instance() override;

    void remove_instance() override;

    void update_instance() override;
};



#endif //EMPLOYEEUI_H
