//
// Created by Bianca Sava on 15.05.2025.
//

#include "ProductController.h"

using namespace productcontroller;
using namespace productrepo;
using namespace productdomain;

ProductController::ProductController(ProductRepository &productRepo): productRepository()
{
    productRepository = productRepo;
}

void ProductController::addProduct(Product product)
{
    productRepository.addProduct(product);
}

std::vector<Product> ProductController::listProducts()
{
    return productRepository.listProducts();
}


