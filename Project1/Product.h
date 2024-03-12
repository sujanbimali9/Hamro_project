#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "rapidjson/document.h"

class Product {
public:
    std::string id;
    std::string title;
    double price;
    std::string description;
    std::string category;
    std::string image;
    double rating;
    int ratingCount;

    void fromJson(const rapidjson::Value& productJson);
};

#endif
