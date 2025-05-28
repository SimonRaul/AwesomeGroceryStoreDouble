//
// Created by ionut on 5/15/2025.
//

#ifndef CUSTOMER_UI_H
#define CUSTOMER_UI_H
#include <string>

#include "IPresentation.h"
#include "../../Service/Controller/ProductController.h"
#include "../../Service/Controller/OrderController.h"
#include "../../Data/Repo/Customer_Repo.h"


class Customer_UI: public IPresentation {
private:
    Customer_Repo::Customer_Repo cus_repo;
    productcontroller::ProductController product_cont;
    controller::OrderController order_cont;

public:
    Customer_UI(const std::string& cus_file, const std::string& prod_file, const std::string& order_file);

    std::string main_menu() override;

    void create_instance() override;

    void remove_instance() override;

    void update_instance() override;

    int input_integer();

    std::string input_string();

    float input_float();

    vector<pair<Product,float>> from_id_and_quantity_to_product_and_quantity_list();

    void run(Customer* current_customer);
};



#endif //CUSTOMER_UI_H
