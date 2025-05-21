//
// Created by Simon Raul on 5/20/2025.
//

#ifndef IPRESENTATION_H
#define IPRESENTATION_H
#include <string>

class IPresentation {
public:

    virtual std::string main_menu() = 0;

    virtual void create_instance() = 0;

    virtual void remove_instance() = 0;

    virtual void update_instance() = 0;
};

#endif //IPRESENTATION_H