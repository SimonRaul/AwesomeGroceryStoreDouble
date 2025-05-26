#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H
#include "../../Data/Repo/ProductRepository.h"
#include "../../Data/Domain/Product.h"
#include <vector>
#include <memory>

using namespace productrepo;
using namespace productdomain;

namespace productcontroller {
    class ProductController {
    private:
        std::shared_ptr<ProductRepository> productRepository;
    public:
        explicit ProductController(std::shared_ptr<ProductRepository> productRepo);
        void addProduct(const std::string& name, float price, float quantity);
        std::vector<std::shared_ptr<Product>> listProducts();
        bool removeProduct(int id);
        bool updateProduct(const std::string& id, const std::string& name, float price, float quantity);
    };
}

#endif //PRODUCTCONTROLLER_H
