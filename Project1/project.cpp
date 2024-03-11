#define CURL_STATICLIB
#include <iostream>
#include "curl/curl.h"
#include <conio.h>
#include <Windows.h>
#include <vector>
#include "rapidjson/document.h"


#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif

#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "advapi32.lib")

using namespace std;



class Product {
public:
    int id;
    std::string title;
    double price;
    std::string description;
    std::string category;
    std::string image;
    double rating;
    int ratingCount;
};



class Response {
public:
    void appendData(const char* data, size_t size) {
        data_.append(data, size);
    }

    std::string getData() const {
        return data_;
    }

private:
    std::string data_;
};


int parseProducts(Response response, std::vector<Product>& products) ;

// Callback function to write received data into a Response object
size_t write_callback(void* contents, size_t size, size_t nmemb, Response* response) {
    size_t total_size = size * nmemb;
    response->appendData((char*)contents, total_size);
    return total_size;
}

int main() {
    CURL* curl = curl_easy_init();
    
    if (curl) {
        Response response;
        vector<Product> products;
        curl_easy_setopt(curl, CURLOPT_URL, "https://fakestoreapi.com/products");

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Pass the address of the Response object
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Now response.getData() contains the received data, you can store/process it further
            std::cout << "Received data: " << response.getData() << std::endl;
        }
        system("cls");
	    cout << "data received successfully" << endl<<endl<<endl;
        parseProducts(response, products);


        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Error initializing libcurl" << std::endl;
    }

    char opt;

    do {
        int a = 0;
        cout << "enter a no"<<endl;
        cin >> a;
        opt = 'n';

        switch (a) {
        case 1:
            cout << 1 << endl;
            break;
        case 2:
            cout << 2 << endl;       
            break;

        case 3:
            cout << 3 << endl;
            break;

        case 4:
            cout << 4 << endl;
            break;

        case 5:
            cout << 5 << endl;
            break;

        case 6:
            cout << 6 << endl;
            break;


        }
       
        cout << "do you want to continue"<<endl;
        cin >> opt;
    } while (opt == 'y' || opt == 'Y');

    system("cls");
    cout << "program exit successfullly"<<endl;

    return 0;
}

int parseProducts(Response response, std::vector<Product>& products) {
    rapidjson::Document doc;
    doc.Parse(response.getData().c_str());

    if (!doc.IsArray()) {
        std::cerr << "Invalid JSON format: Not an array" << std::endl;
        return 1;
    }

    // Iterate over each product in the JSON array
    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i) {
        const rapidjson::Value& productJson = doc[i];

        // Create a Product object and populate its fields
        Product product;
        product.id = productJson["id"].GetInt();
        product.title = productJson["title"].GetString();
        product.price = productJson["price"].GetDouble();
        product.description = productJson["description"].GetString();
        product.category = productJson["category"].GetString();
        product.image = productJson["image"].GetString();
        product.rating = productJson["rating"]["rate"].GetDouble();
        product.ratingCount = productJson["rating"]["count"].GetInt();

        cout << "id: " << product.id << endl;
        cout << "title: " << product.title << endl;
        cout << "price: " << product.price << endl;
        cout << "description: " << product.description << endl;
        cout << "category: " << product.category << endl;
        cout << "image: " << product.image << endl;
        cout << "rating: " << product.rating << endl;
        cout << "ratingCount: " << product.ratingCount << endl;
        cout << "-----------------------------------" << endl;

        products.push_back(product);
    }

    return 0;
}


