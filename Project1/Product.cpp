#include "Product.h"

void Product::fromJson(const rapidjson::Value &productJson)
{
    id = productJson["foodid"].GetString();
    title = productJson["title"].GetString();
    price = productJson["price"].GetDouble();
    description = productJson["description"].GetString();
    category = productJson["category"].GetString();
    image = productJson["image"].GetString();
    rating = productJson["rating"].GetDouble();
    ratingCount = productJson["ratingCount"].GetInt();
}
