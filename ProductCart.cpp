#include "ProductCart.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string ProductCart::toJson() const
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("foodid");
    writer.Int(id);
    writer.Key("title");
    writer.String(title.c_str());
    writer.Key("price");
    writer.Double(price);
    writer.Key("description");
    writer.String(description.c_str());
    writer.Key("category");
    writer.String(category.c_str());
    writer.Key("image");
    writer.String(image.c_str());
    writer.Key("rating");
    writer.Double(rating);
    writer.Key("ratingCount");
    writer.Int(ratingCount);
    writer.Key("quantity");
    writer.Int(quantity);
    writer.Key("userid");
    writer.Int(userid);
    writer.Key("name");
    writer.String(name.c_str());
    writer.Key("location");
    writer.String(location.c_str());
    writer.Key("quantity");
    writer.Int(quantity);
    writer.EndObject();
    return s.GetString();
}

void ProductCart::fromJson(const rapidjson::Value &productJson)
{
    id = productJson["foodid"].GetInt();
    title = productJson["title"].GetString();
    price = productJson["price"].GetDouble();
    description = productJson["description"].GetString();
    category = productJson["category"].GetString();
    image = productJson["image"].GetString();
    rating = productJson["rating"].GetDouble();
    ratingCount = productJson["ratingCount"].GetInt();
    userid = productJson["userid"].GetInt();
    name = productJson["name"].GetString();
    location = productJson["location"].GetString();
    quantity = productJson["quantity"].GetInt();
}

ProductCart::ProductCart(const Product &product, int quantity, const int &userid, const std::string &location, const std::string &name)
    : Product(product), quantity(quantity), userid(userid), location(location), name(name) {}

ProductCart::ProductCart() : quantity(0) {}
