 #define CURL_STATICLIB
 #include <iostream>
 #include "curl/curl.h"
 #include <conio.h>
 #include <Windows.h>
 #include <vector>
 #include "rapidjson/document.h"




 using namespace std;



 class Product {
 public:
     string id;
     std::string title;
     double price;
     std::string description;
     std::string category;
     std::string image;
     double rating;
     int ratingCount;
 };

 class ProductCart: Product{
 public:
	 int quantity;
     string loation;


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
     vector<Product> products;

     if (curl) {
         Response response;
         curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/home");

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

         int a = products.size();
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
         case 7:
             cout << 6 << endl;
             break;
         case 8:
             cout << 9 << endl;
             break;
         case 10:
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
         product.id = productJson["foodid"].GetString();
         product.title = productJson["title"].GetString();
         product.price = productJson["price"].GetDouble();
         product.description = productJson["description"].GetString();
         product.category = productJson["category"].GetString();
         product.image = productJson["image"].GetString();
         product.rating = productJson["rating"].GetDouble();
          product.ratingCount = productJson["ratingCount"].GetInt();


         products.push_back(product);
     }

     return 0;
 }


//
// #define curl_staticlib
//
//#include <iostream>
//#include <string>
//#include "curl/curl.h"
//
// Callback function to handle response data
//size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *response)
//{
//    size_t total_size = size * nmemb;
//    response->append((char *)contents, total_size);
//    return total_size;
//}
//
// Class representing product details
//class Product
//{
//public:
//    std::string title;
//    double price;
//    std::string description;
//    std::string image;
//    std::string category;
//};
//
// Class representing HTTP response
//class Response
//{
//public:
//    void appendData(const char *data, size_t size)
//    {
//        data_.append(data, size);
//    }
//
//    std::string getData() const
//    {
//        return data_;
//    }
//
//private:
//    std::string data_;
//};
//
// Function to perform a PUT request to update a product
//CURLcode updateProduct(const Product &product, Response &response)
//{
//    CURL *curl = curl_easy_init();
//    if (curl)
//    {
//         Set the URL for the PUT request
//        curl_easy_setopt(curl, CURLOPT_URL, "https://fakestoreapi.com/products/7");
//
//         Specify the HTTP method as PUT
//        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
//
//         Set the JSON payload
//        std::string json_data = "{\"title\":\"" + product.title + "\",\"price\":" + std::to_string(product.price) +
//                                ",\"description\":\"" + product.description + "\",\"image\":\"" + product.image +
//                                "\",\"category\":\"" + product.category + "\"}";
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
//
//         Set the write callback function to handle response data
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//         Perform the PUT request
//        CURLcode res = curl_easy_perform(curl);
//
//         Clean up
//        curl_easy_cleanup(curl);
//
//        return res;
//    }
//    else
//    {
//        std::cerr << "Failed to initialize libcurl" << std::endl;
//        return CURLE_FAILED_INIT;
//    }
//}
//
//int main()
//{
//    Response response;
//
//     Create an instance of the Product class with the desired details
//    Product product;
//    product.title = "test product";
//    product.price = 13.5;
//    product.description = "lorem ipsum set";
//    product.image = "https://i.pravatar.cc";
//    product.category = "electronic";
//
//     Example usage of the updateProduct function
//    CURLcode res = updateProduct(product, response);
//
//    if (res != CURLE_OK)
//    {
//        std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
//    }
//    else
//    {
//         Request successful, print the response
//        std::cout << "Response: " << response.getData() << std::endl;
//    }
//
//    return 0;
//}
