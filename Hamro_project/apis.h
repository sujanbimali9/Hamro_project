#ifndef APIS_H
#define APIS_H

#include <vector>
#include <string>
#include "Product.h"
#include "ProductCart.h"

int getData(std::vector<Product> &product);

int orderFood(ProductCart &product);

int getCart(std::string id, std::vector<ProductCart> &product);

void login(std::string username, std::string password);

void signup(std::string username, std::string password);

#endif
