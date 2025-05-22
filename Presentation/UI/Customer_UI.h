//
// Created by ionut on 5/15/2025.
//

#ifndef CUSTOMER_UI_H
#define CUSTOMER_UI_H
#include <string>

#include "IPresentation.h"


class Customer_UI: public IPresentation {
public:
    Customer_UI() = default;

    std::string main_menu() override;

    void create_instance() override;

    void remove_instance() override;

    void update_instance() override;
};



#endif //CUSTOMER_UI_H
