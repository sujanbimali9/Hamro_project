#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "rapidjson/document.h"

class Product
{
public:
    int id;
    std::string title;
    double price;
    std::string description;
    std::string category;
    std::string image;
    double rating;
    int ratingCount;

    int fromJson(const rapidjson::Value &productJson);
};

#endif
