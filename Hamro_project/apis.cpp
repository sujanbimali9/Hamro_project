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

using namespace std;

const string apiKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImZ2b2R4Y2pzc2VyeHJ3bXhpdGRxIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MTI1ODE2MzksImV4cCI6MjAyODE1NzYzOX0.h3XphhMXYFweVASzMnP4jRag9E2k-tXXzDn-TdLriuI";
int getData(std::vector<Product> &products);
int getCart(std::string id, std::vector<ProductCart> &products);
int orderFood(ProductCart &product);
int parseProducts(string &response, std::vector<Product> &products);
int parseProductsCart(string &response, std::vector<ProductCart> &products);
void login(string username, string password);
void signup(string username, string password);

void signup(string username, string password)
{
    // cpr::Response res = cpr::Post(
    //     cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/signup"},
    //     cpr::Header({"apikey", apiKey}),
    //     cpr::Body("{\"email\":\"" + username + "\",\"password\":\"" + password + "\"}"));

    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/signup"},
        cpr::Header{{"apikey", apiKey}},
        cpr::Body("{\"email\":\"" + username + "\",\"password\":\"" + password + "\"}"));
}

void login(string username, string password)
{
    // cpr::Response res = cpr::Post(
    //     cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/token?grant_type=password"},
    //     cpr::Header({"apikey", apiKey}),
    //     cpr::Body("{\"email\":\"" + username + "\",\"password\":\"" + password + "\"}"));
    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/auth/v1/token?grant_type=password"},
        cpr::Header{{"apikey", apiKey}},
        cpr::Body("{\"email\":\"" + username + "\",\"password\":\"" + password + "\"}"));
}

int getData(vector<Product> &product)
{
    cpr::Response res = cpr::Get(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/foods?select=*"},
        cpr::Header{{
                        "apikey",
                        apiKey,
                    },
                    {
                        "Authorization",
                        "Bearer " + apiKey,
                    }});

    cout << res.status_code;
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

int getCart(string id, vector<ProductCart> &product)
{
    string url = "https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/orders?id=" + id;
    cpr::Response res = cpr::Get(
        cpr::Url{url},
        cpr::Header{{
                        "apikey",
                        apiKey,
                    },
                    {
                        "Authorization",
                        "Bearer " + apiKey,
                    }});
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

// int getCart(string id, vector<ProductCart> &product)
// {
//     string json = "{\"userid\": \"" + id + "\"}";

//     cpr::Response res = cpr::Post(cpr::Url{"http://localhost:3000/get-order"}, cpr::Body{json.c_str()}, cpr::Header{{"Content-Type", "application/json"}});

//     if (res.status_code != 200)
//     {
//         throw string("error check your network conncetion and try again");
//         return 1;
//     }
//     else
//     {
//         parseProductsCart(res.text, product);
//         return 0;
//     }
// }

int orderFood(ProductCart &product)
{
    std::string json = product.toJson();

    cpr::Response res = cpr::Post(
        cpr::Url{"https://fvodxcjsserxrwmxitdq.supabase.co/rest/v1/orders"},
        cpr::Body{json},
        cpr::Header{
            {"apikey", apiKey.c_str()},
            {"Authorization", "Bearer " + apiKey},
        });

    if (res.status_code != 200)
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

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < static_cast<int>(doc.Size()); ++i)
    {
        const rapidjson::Value &productJson = doc[i];

        Product product;
        product.fromJson(productJson);
        products.push_back(product);
    }

    return 0;
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
