
#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H
#include "../../Data/Repo//ProductRepository.h"
#include "../../Data/Domain/Product.h"
#include <vector>

using namespace productrepo;
using namespace productdomain;

namespace productcontroller{
class ProductController {
private:
  ProductRepository productRepository;
public:
  ProductController(ProductRepository &productRepo);
  void addProduct(Product product);
  std::vector<Product > listProducts();
};

}

#endif //PRODUCTCONTROLLER_H
