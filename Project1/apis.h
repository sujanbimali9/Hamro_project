#ifndef API_H
#define API_H

#include <vector>
#include <string>
#include "Product.h"
#include "ProductCart.h"

int getData(std::vector <Product>& product);

int orderFood(ProductCart& product);

int getCart(std::string id, std::vector<ProductCart>& product);


#endif 

