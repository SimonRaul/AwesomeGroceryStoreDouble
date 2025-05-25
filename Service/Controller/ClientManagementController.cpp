#include "ClientManagementController.h"
#include "../../Data/Repo/Customer_Repo.h"

using namespace std;

namespace controller {

void ClientManagementController::gdprAnonymize(const string &email) {
    Customer_Domain::Customer customer = cus_repo.find_by_email(email);
    ofstream file;
    file.open("gdprdata.txt");
    file << "Kunde-" << customer.get_id() <<" Unbekannt" << ":" << "null" << ":" << "null" << ":" << "gdprDeleted=true" << ":" << "null" << '\n';
    file.close();
}

}