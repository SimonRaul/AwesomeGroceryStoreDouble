#include "ProductRepository.h"
#include <iostream>
#include <fstream>

namespace productrepo {

    std::vector<std::vector<std::string>> ProductRepository::readFileSplitByColon(const std::string& filename) {
        std::vector<std::vector<std::string>> result;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return result;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens;
            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ':')) {
                tokens.push_back(token);
            }

            result.push_back(tokens);
        }

        file.close();
        return result;
    }

    void ProductRepository::writeToFile() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
            return;
        }

        for (const auto& product : products) {
            file << product->get_id() << ":"
                 << product->get_name() << ":"
                 << product->get_price() << ":"
                 << product->get_quantity() << "\n";
        }

        file.close();
    }

    ProductRepository::ProductRepository(const std::string& filename) : filename(filename) {
        std::vector<std::vector<std::string>> products_vector = readFileSplitByColon(filename);
        for (const auto& product_data : products_vector) {
            if (product_data.size() >= 4) {
                create_with_id(product_data[0], product_data[1], 
                             std::stof(product_data[2]), std::stof(product_data[3]));
            }
        }
    }

    std::shared_ptr<Product> ProductRepository::create(const std::string& name, float price, float quantity) {
        auto product = std::make_shared<Product>(name, price, quantity);
        products.push_back(product);
        writeToFile();
        return product;
    }

    std::shared_ptr<Product> ProductRepository::create_with_id(const std::string& id, const std::string& name, 
                                                             float price, float quantity) {
        auto product = std::make_shared<Product>(id, name, price, quantity);
        products.push_back(product);
        writeToFile();
        return product;
    }

    bool ProductRepository::update(const std::string& id, const std::string& name, float price, float quantity) {
        for (auto& product : products) {
            if (product->get_id() == id) {
                product->set_name(name);
                product->set_price(price);
                product->set_quantity(quantity);
                writeToFile();
                return true;
            }
        }
        return false;
    }

    bool ProductRepository::remove(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->get_id() == std::to_string(id)) {
                products.erase(it);
                writeToFile();
                return true;
            }
        }
        return false;
    }

    

    std::vector<std::shared_ptr<Product>> ProductRepository::list() {
        return products;
    }

    Product ProductRepository::find_by_email(const string& arg)
    {
        return Product("",0,0,0);
    }

}

