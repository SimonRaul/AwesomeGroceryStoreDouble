#include "ProductRepository.h"
#include <vector>


namespace Product{

 ProductRepository::ProductRepository(std::vector<Product> products){
  this->Products = products;
 }

 bool ProductRepository::addProduct(Product product){
  for (auto it = this->Products.begin(); it!= this->Products.end(); it++ ){
    if (it->ID == product.ID){
      return false;
    }
   }
   this->Products.push_back(product);
   return true;
 }

 std::vector<Product> ProductRepository::listProducts() {
  return Products;
 }

}