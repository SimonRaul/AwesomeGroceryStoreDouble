//
// Created by Bianca Sava on 15.05.2025.
//

#include "ProductController.h"

using namespace productcontroller;
using namespace productrepo;
using namespace productdomain;

ProductController::ProductController(const std::string& filename)
    : productRepository(ProductRepository(filename)) {
}

void ProductController::addProduct(const std::string& name, float price, float quantity) {
    productRepository.create(name, price, quantity);
}

std::vector<std::shared_ptr<Product>> ProductController::listProducts() {
    return productRepository.list();
}

bool ProductController::removeProduct(int id) {
    return productRepository.remove(id);
}

bool ProductController::updateProduct(const std::string& id, const std::string& name, float price, float quantity) {
    return productRepository.update(id, name, price, quantity);
}

std::shared_ptr<Product> ProductController::getProductById(int id) {
    auto products = productRepository.list();
    for (const auto& product : products) {
        try {
            if (std::stoi(product->get_id()) == id) {
                return product;
            }
        } catch (const std::invalid_argument&) {
            continue;
        }
    }
    return nullptr;
}

