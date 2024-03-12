#ifndef API_H
#define API_H

#include <vector>
#include <string>

class Product;
class ProductCart;

int getData(std::vector <Product>& product);

int orderFood(ProductCart& product);

int getCart(std::string id, std::vector<ProductCart>& product);

#endif 

