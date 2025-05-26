//
// Created by Bianca Sava on 15.05.2025.
//

#include "ProductController.h"

using namespace productcontroller;
using namespace productrepo;
using namespace productdomain;

ProductController::ProductController(std::shared_ptr<ProductRepository> productRepo) 
    : productRepository(productRepo) {
}

void ProductController::addProduct(const std::string& name, float price, float quantity) {
    productRepository->create(name, price, quantity);
}

std::vector<std::shared_ptr<Product>> ProductController::listProducts() {
    return productRepository->listProducts();
}

bool ProductController::removeProduct(int id) {
    return productRepository->remove(id);
}

bool ProductController::updateProduct(const std::string& id, const std::string& name, float price, float quantity) {
    return productRepository->update(id, name, price, quantity);
}


