//
// Created by ionut on 5/15/2025.
//

#ifndef CUSTOMER_UI_H
#define CUSTOMER_UI_H
#include <string>

#include "IPresentation.h"
#include "../../Service/Controller/ProductController.h"
#include "../../Service/Controller/OrderController.h"
#include "BasicUI.h"


class Customer_UI: public IPresentation { friend class BasicUi;
private:
    Customer_Repo::Customer_Repo cus_repo;
    productcontroller::ProductController product_cont;
    controller::OrderController order_cont;

public:
    Customer_UI(const std::string& cus_file, std::string& prod_file, std::string& order_file);

    std::string main_menu() override;

    void create_instance() override;

    void remove_instance() override;

    void update_instance() override;

    int input_integer();

    std::string input_string();

    void run(Customer* current_customer);
};



#endif //CUSTOMER_UI_H
