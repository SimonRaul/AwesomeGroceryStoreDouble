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
        ProductRepository productRepository;
    public:
        explicit ProductController(const std::string& filename);
        void addProduct(const std::string& name, float price, float quantity);
        std::vector<std::shared_ptr<Product>> listProducts();
        bool removeProduct(int id);
        bool updateProduct(const std::string& id, const std::string& name, float price, float quantity);

        std::shared_ptr<Product> getProductById(int id);

        bool validate_id(int id);

        bool validate_stock(int id, float amount);
    };
}

#endif //PRODUCTCONTROLLER_H
