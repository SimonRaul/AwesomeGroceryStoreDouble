
#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H
#include "../Repository/ProductRepository.h"
#include "../Domain/Product.h"
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
