#include "apis.h"
#include "Product.h"
#include "ProductCart.h"

#include "httplib/httplib.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getData(std::vector<Product>& products);
int getCart(std::string id, std::vector<ProductCart>& products);
int orderFood(ProductCart& product);
int parseProducts(string& response, std::vector<Product>& products);
int parseProductsCart(string& response, std::vector<ProductCart>& products);

int getData(vector<Product>& product)
{
    httplib::Client client("localhost", 3000);

    httplib::Result res = client.Get("/home");

    if (!res)
    {

        throw string("error check your network conncetion and try again");
        return 1;
    }
    else
    {
        parseProducts(res->body, product);
        return 0;
    }
}

int getCart(string id, vector<ProductCart>& product)
{
    httplib::Client client("localhost", 3000);
    string url = "http://localhost:3000/get-order/" + id;

    httplib::Result res = client.Get(url.c_str());

    if (!res)
    {
        throw string("Error: Failed to fetch data. Check your network connection and try again.");
        return 1;
    }
    else
    {
        parseProductsCart(res->body, product);
        return 0;
    }
}

//int getCart(string id, vector<ProductCart> &product)
//{
//    httplib::Client client("localhost", 3000);
//    string url = "http://localhost:3000/get-order";
//    string json = "{\"userid\": \"" + id + "\"}";
//    httplib::Result res = client.Post(url, json.c_str(), "application/json");
//
//    if (!res)
//    {
//        throw string("error check your network conncetion and try again");
//        return 1;
//    }
//    else
//    {
//        parseProductsCart(res->body, product);
//        return 0;
//    }
//}

int orderFood(ProductCart& product)
{
    httplib::Client client("localhost", 3000);

    std::string json = product.toJson();

    auto res = client.Post("/order-food", json, "application/json");

    if (!res || res->status != 200)
    {
        throw string("Error: Failed to send data to server. Check your network connection and try again.");
        return 1;
    }
    else
    {
        return 0;
    }
}

int parseProducts(string& response, vector<Product>& products)
{
    rapidjson::Document doc;
    doc.Parse(response.c_str());

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < static_cast<int> (doc.Size()); ++i)
    {
        const rapidjson::Value& productJson = doc[i];

        Product product;
        product.fromJson(productJson);
        products.push_back(product);
    }

    return 0;
}

int parseProductsCart(string& response, std::vector<ProductCart>& products)
{
    rapidjson::Document doc;
    doc.Parse(response.c_str());

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < static_cast<int>(doc.Size()); ++i)
    {
        const rapidjson::Value& productJson = doc[i];

        ProductCart product;
        product.fromJson(productJson);
        products.push_back(product);
    }
    return 0;
}