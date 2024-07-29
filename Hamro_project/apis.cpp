#include "apis.h"
#include "Product.h"
#include "ProductCart.h"

#include <cpr/cpr.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <vector>
#include <string>
#include "User.h"

using namespace std;

string apiKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImZ2b2R4Y2pzc2VyeHJ3bXhpdGRxIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MTI1ODE2MzksImV4cCI6MjAyODE1NzYzOX0.h3XphhMXYFweVASzMnP4jRag9E2k-tXXzDn-TdLriuI";
string bearer = "Bearer " + apiKey;
int getData(std::vector<Product> &products);
int getCart(int id, std::vector<ProductCart> &products);
int orderFood(ProductCart &product);
int parseProducts(string &response, std::vector<Product> &products);
int parseProductsCart(string &response, std::vector<ProductCart> &products);
int parseUser(string &response, User &user);
int login(User &user);
int signup(User &user);

int signup(User &user)
{

    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/signup"},
        cpr::Header{
            {"apikey", apiKey.c_str()},
            {"Content-Type", "application/json"}},
        cpr::Body(user.toJson()));

    if (res.status_code == 400)
    {
        throw string("Unable to validate email address, invalid format ");
        return 1;
    }
    else if (res.status_code != 200)
    {
        // throw string("error check your network conncetion and try again");
        throw string(res.text);
        return 1;
    }
    else
    {
        parseUser(res.text, user);
        return 0;
    }
}

int login(User &user)
{

    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/token?grant_type=password"},
        cpr::Header{
            {"apikey", apiKey.c_str()},
            {"Content-Type", "application/json"}},
        cpr::Body(user.toJson()));
    if (res.status_code == 400)
    {
        throw string("Invalid login credentials");
        return 1;
    }
    else if (res.status_code != 200)
    {
        // throw string("error check your network conncetion and try again");
        cout << res.text << endl;
        throw string(res.text);
        return 1;
    }
    else if (res.text == "{}")
    {
        return 1;
    }
    else
    {
        parseUser(res.text, user);
        return 0;
    }
}

int getData(vector<Product> &product)
{
    cpr::Response res = cpr::Get(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/foods?select=*"},
        cpr::Header{{
                        "apikey",
                        apiKey.c_str(),
                    },
                    {
                        "Authorization",
                        bearer.c_str(),
                    }});

    if (res.status_code != 200)
    {
        throw string("error check your network conncetion and try again");
        return 1;
    }
    else
    {
        parseProducts(res.text, product);
        return 0;
    }
}

int getCart(int id, vector<ProductCart> &product)
{
    string url = "https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/orders?userid=eq." + to_string(id) + "&select=*";
    cpr::Response res = cpr::Get(
        cpr::Url{url},
        cpr::Header{
            {"apikey", apiKey.c_str()},
            {"Authorization", bearer.c_str()}});
    if (res.status_code != 200)
    {
        throw string("Error: Failed to fetch data. Check your network connection and try again.");
        return 1;
    }
    else
    {
        parseProductsCart(res.text, product);
        return 0;
    }
}

int orderFood(ProductCart &product)
{
    std::string json = product.toJson();
    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/orders"},
        cpr::Header{
            {"apikey", apiKey.c_str()},
            {"Authorization", bearer.c_str()},
            {"Content-Type", "application/json"},
            {"Prefer", "return=minimal"}},
        cpr::Body{json.c_str()});
    if (res.error)
    {
        throw string("Error: Failed to send data to server. Check your network connection and try again.");
        return 1;
    }
    else
    {
        return 0;
    }
}

int parseProducts(string &response, vector<Product> &products)
{
    rapidjson::Document doc;

    doc.Parse(response.c_str());

    if (doc.HasParseError())
    {
        cerr << "JSON parse error: " << rapidjson::GetParseErrorFunc(doc.GetParseError()) << endl;
        return 1;
    }

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < static_cast<int>(doc.Size()); ++i)
    {

        const rapidjson::Value &productJson = doc[i];

        Product product;

        if (product.fromJson(productJson))
        {
            cerr << "Error converting JSON to Product at index " << i << endl;
            return 1;
        }

        products.push_back(product);
    }

    return 0;
}

int parseUser(string &response, User &user)
{
    try
    {
        rapidjson::Document doc;
        doc.Parse(response.c_str());
        if (doc.HasParseError())
        {
            cerr << "JSON parse error: " << rapidjson::GetParseErrorFunc(doc.GetParseError()) << endl;
            return 1;
        }
        if (!doc.IsObject())
        {

            throw string("Invalid JSON format: Not an object");
            return 1;
        }
        if (doc.HasMember("error"))
        {
            throw string(doc["error_description"].GetString());
            return 1;
        }
        user.fromJson(doc);
        return 0;
    }
    catch (...)
    {
        return 1;
    }
}

int parseProductsCart(string &response, std::vector<ProductCart> &products)
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
        const rapidjson::Value &productJson = doc[i];

        ProductCart product;
        product.fromJson(productJson);
        products.push_back(product);
    }
    return 0;
}
