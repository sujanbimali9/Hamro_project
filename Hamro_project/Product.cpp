#include "Product.h"
#include <iostream>

int Product::fromJson(const rapidjson::Value &productJson)
{
    try
    {

        id = productJson["foodid"].GetInt();

        title = productJson["title"].GetString();

        price = productJson["price"].GetDouble();

        description = productJson["description"].GetString();

        category = productJson["category"].GetString();

        image = productJson["image"].GetString();

        rating = productJson["rating"].GetDouble();

        ratingCount = productJson["ratingCount"].GetInt();

        return 0;
    }
    catch (...)
    {
        std::cerr << "Error converting JSON to Product" << std::endl;
        return 1;
    }
}
