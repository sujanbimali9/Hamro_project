#ifndef PRODUCTCART_H
#define PRODUCTCART_H

#include <string>
#include "Product.h"
#include "rapidjson/document.h"

class ProductCart : public Product {
public:
    int quantity;
    std::string userid;
    std::string location;
    std::string name;

    std::string toJson() const;
    void fromJson(const rapidjson::Value& productJson);
    ProductCart(const Product& product, int quantity, const std::string& userid, const std::string& location, const std::string& name);
    ProductCart();
};

#endif
