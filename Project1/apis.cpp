#define CURL_STATICLIB

#include "apis.h"
#include "Product.h"
#include "ProductCart.h"
#include "Response.h"

#include <iostream>
#include "curl/curl.h"
#include <vector>
#include "rapidjson/document.h"
#include <string>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

int getData(std::vector<Product> &products);
int getCart(std::string id, std::vector<ProductCart> &products);
int orderFood(ProductCart &product);
int parseProducts(Response response, std::vector<Product> &products);
int parseProductsCart(Response response, std::vector<ProductCart> &products);

static size_t write_callback(void *contents, size_t size, size_t nmemb, Response *response)
{
    size_t total_size = size * nmemb;
    response->appendData((char *)contents, total_size);
    return total_size;
}

int getData(vector<Product> &product)
{
    CURL *curl = curl_easy_init();

    if (curl)
    {
        Response response;
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/home");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            throw "error check your network conncetion and try again";
            return 1;
        }
        else
        {
            parseProducts(response, product);
            return 0;
        }
    }
    else
    {
        throw "curl not initialized properly";
        return 1;
    }
}

int getCart(string id, vector<ProductCart> &product)
{
    CURL *curl = curl_easy_init();

    if (curl)
    {
        string url = "http://localhost:3000/get-order/" + id;
        Response response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if (res == CURLE_URL_MALFORMAT)
        {
            throw "empty";
        }
        else if (res != CURLE_OK)
        {
            throw "error check your network conncetion and try again";
            return 1;
        }
        else
        {
            parseProductsCart(response, product);
            return 0;
        }
    }
    else
    {
        throw "curl not initialized properly";
        return 1;
    }
}

// int getCart(string id, vector<ProductCart>& product)
//{
//     CURL* curl;
//     curl = curl_easy_init();
//     Response response;
//     if (curl) {
//         curl_easy_setopt(curl,CURLOPT_URL, "http://localhost:3000/get-order");
//         string json = "{\"userid\": \"" + id + "\"}";

//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,json.c_str());
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.length());
//        struct curl_slist* headers = NULL;
//        headers = curl_slist_append(headers, "Content-Type: application/json");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//        CURLcode res = curl_easy_perform(curl);

//        curl_slist_free_all(headers);
//        curl_easy_cleanup(curl);
//        if (res != CURLE_OK) {
//		 throw "error check your network conncetion and try again";
//		 return 1;
//	 }
//        else {
//		 parseProductsCart(response, product);
//		 return 0;
//	 }
//    }
//    else {
//        throw "curl not initialized properly";
//        return 0;
//    }
//}

int orderFood(ProductCart &product)
{
    CURL *curl;
    curl = curl_easy_init();
    string json = product.toJson();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/order-food");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.length());

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);

        curl_slist_free_all(headers);

        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            throw "check your network connection and try again";
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        throw "curl not initialized properly";
        return 1;
    }
}

int parseProducts(Response response, vector<Product> &products)
{
    rapidjson::Document doc;
    doc.Parse(response.getData().c_str());

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < doc.Size(); ++i)
    {
        const rapidjson::Value &productJson = doc[i];

        Product product;
        product.fromJson(productJson);
        products.push_back(product);
    }

    return 0;
}

int parseProductsCart(Response response, std::vector<ProductCart> &products)
{
    rapidjson::Document doc;
    doc.Parse(response.getData().c_str());

    if (!doc.IsArray())
    {
        cerr << "Invalid JSON format: Not an array" << endl;
        return 1;
    }

    for (int i = 0; i < doc.Size(); ++i)
    {
        const rapidjson::Value &productJson = doc[i];

        ProductCart product;
        product.fromJson(productJson);
        products.push_back(product);
    }
    return 0;
}