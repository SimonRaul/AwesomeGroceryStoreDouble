//
// Created by anama on 5/22/2025.
//

#include <string>
#include <fstream>

using namespace std;

#ifndef CLIENTMANAGEMENTCONTROLLER_H
#define CLIENTMANAGEMENTCONTROLLER_H

namespace controller {

class ClientManagementController {
  public:
    void gdprAnonymize(const string &email);
};

}

#endif //CLIENTMANAGEMENTCONTROLLER_H
