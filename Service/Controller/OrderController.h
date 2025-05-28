#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include "../../Data/Repo/OrderRepo.h"
#include "ProductController.h"

using namespace productcontroller;

namespace controller {

    class OrderController {
       private:
        repository::OrderRepo orderRepo;
        ProductController productContr;

       public:
         OrderController(const std::string& filename, const ProductController& prod_contr);

        const std::vector<domain::OrderDomain>& getOrders();

        //returns all the orders with a specified status
         std::vector<domain::OrderDomain> getOrdersByStatus(domain::OrderStatus status);

        std::vector<domain::OrderDomain> getOrdersByCustomer(Customer* customer);

        bool validateID(int id);

        domain::OrderDomain getOrderByID(int id);

        std::vector<pair<Product, float>> get_products_from_id(int id);

        //calculates the number of orders in a specified year
        double getTotalOrdersInYear(int year) const;

        //calculates the number of orders in a specified month
        double getTotalOrdersInMonth(int month) const;

        //checks if the order number is unique
        bool isOrderNumberUnique(int orderNumber) const;

        //checks if an employee can modify an order
        bool canModifyOrder(int orderNumber, const employeedomain::Employee& employee) const;

        //adds a new order
        void addOrder(const domain::OrderDomain& order);

        //Updates the list of products in an order
        bool updateOrder(int orderNumber, const std::vector<std::pair<Product, float>>& newProducts);

        //Changes the status of an order (unless it's already "Completed")
        bool setOrderStatus(int orderNumber, domain::OrderStatus newStatus);

        //Assigns an employee to an order (unless the order is already assigned to someone)
        bool assignEmployeeIfUnassigned(int orderNumber, const employeedomain::Employee& employee);

        //creates a reservation
        bool createReservation(const Customer_Domain::Customer& customer, const std::vector<std::pair<Product, float>>& products);

		void assignEmployeeIfUnassigned(int id, employeedomain::Employee ** employee);
	};
}

#endif //ORDERCONTROLLER_H
