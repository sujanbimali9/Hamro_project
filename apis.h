#ifndef APIS_H
#define APIS_H

#include <vector>
#include <string>
#include "Product.h"
#include "ProductCart.h"
#include "User.h"

int getData(std::vector<Product> &product);

int orderFood(ProductCart &product);

int getCart(int id, std::vector<ProductCart> &product);

int login(User &user);

int signup(User &user);

#endif
