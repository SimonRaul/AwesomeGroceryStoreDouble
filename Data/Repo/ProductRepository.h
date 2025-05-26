#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "IRepo.h"
#include "../Domain/Product.h"

using namespace productdomain;

namespace productrepo {
    class ProductRepository : public IRepo<ProductRepository, Product> {
    private:
        std::vector<std::shared_ptr<Product>> products;
        std::string filename;

    public:
        explicit ProductRepository(const std::string& filename);
        
        static std::vector<std::vector<std::string>> readFileSplitByColon(const std::string& filename);
        void writeToFile();
        
        std::shared_ptr<Product> create(const std::string& name, float price, float quantity);
        std::shared_ptr<Product> create_with_id(const std::string& id, const std::string& name, float price, float quantity);
        
        bool update(const std::string& id, const std::string& name, float price, float quantity);
        bool remove(int id) override;
        
        std::vector<std::shared_ptr<Product>> list() override;

        Product find_by_email(const string& arg) override;
    };
}

#endif //PRODUCTREPOSITORY_H
