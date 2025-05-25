//
// Created by anama on 5/22/2025.
//

#include <string>
#include <fstream>

#include "../../Data/Repo/Customer_Repo.h"

using namespace std;

#ifndef CLIENTMANAGEMENTCONTROLLER_H
#define CLIENTMANAGEMENTCONTROLLER_H

namespace controller {

class ClientManagementController {
private:
    Customer_Repo::Customer_Repo cus_repo;
  public:
    void gdprAnonymize(const string &email);
};

}

#endif //CLIENTMANAGEMENTCONTROLLER_H
