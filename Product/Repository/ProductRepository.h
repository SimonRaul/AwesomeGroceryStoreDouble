
#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H
#include <vector>
#include "../Domain/Product.h"

namespace Product{

class ProductRepository {
private:
    std::vector<Product> Products;

public:
  ProductRepository(std::vector<Product> products);
  bool addProduct(Product product);
  std::vector<Product> listProducts();
};

}

#endif //PRODUCTREPOSITORY_H
