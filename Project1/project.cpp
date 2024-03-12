 #define CURL_STATICLIB
 #include"ListData.h"
 #include <iostream>
 #include "curl/curl.h"
 #include <conio.h>
 #include <Windows.h>
 #include <vector>
 #include "rapidjson/document.h"
 #include<string>
 #include "rapidjson/writer.h"
 #include "rapidjson/stringbuffer.h"
using namespace std;



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

     void fromJson(const rapidjson::Value& productJson) {
         id = productJson["foodid"].GetString();
         title = productJson["title"].GetString();
         price = productJson["price"].GetDouble();
         description = productJson["description"].GetString();
         category = productJson["category"].GetString();
         image = productJson["image"].GetString();
         rating = productJson["rating"].GetDouble();
         ratingCount = productJson["ratingCount"].GetInt();
     }
 };

 class ProductCart: public Product{
 public:
	 int quantity;
     string userid;
     string location;
     string name;

     string toJson() const {
         rapidjson::StringBuffer s;
         rapidjson::Writer<rapidjson::StringBuffer> writer(s);
         writer.StartObject();
         writer.Key("id"); writer.String(id.c_str());
         writer.Key("title"); writer.String(title.c_str());
         writer.Key("price"); writer.Double(price);
         writer.Key("description"); writer.String(description.c_str());
         writer.Key("category"); writer.String(category.c_str());
         writer.Key("image"); writer.String(image.c_str());
         writer.Key("rating"); writer.Double(rating);
         writer.Key("ratingCount"); writer.Int(ratingCount);
         writer.Key("quantity"); writer.Int(quantity);
         writer.Key("userid"); writer.String(userid.c_str());
         writer.Key("name"); writer.String(name.c_str());
         writer.Key("location"); writer.String(location.c_str());
         writer.EndObject();
         return s.GetString();
     }
     void fromJson(const rapidjson::Value& productJson) {
         id = productJson["foodid"].GetString();
         title = productJson["title"].GetString();
         price = productJson["price"].GetDouble();
         description = productJson["description"].GetString();
         category = productJson["category"].GetString();
         image = productJson["image"].GetString();
         rating = productJson["rating"].GetDouble();
         ratingCount = productJson["ratingCount"].GetInt();
         userid = productJson["userid"].GetString();
         name = productJson["name"].GetString();
         location = productJson["location"].GetString();
         quantity = productJson["quantity"].GetInt();

     }

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
 int parseProductsCart(Response response, std::vector<ProductCart>& products);
 int getData();
 int orderFood(ProductCart product);
 int getCart(string id);


// Callback function to write received data into a Response object
 static size_t write_callback(void* contents, size_t size, size_t nmemb, Response* response) {
     size_t total_size = size * nmemb;
     response->appendData((char*)contents, total_size);
     return total_size;
 }

 int getData() {
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
             return 1;
         }
         else {
             // Now response.getData() contains the received data, you can store/process it further
             std::cout << "Received data: " << response.getData() << std::endl;
         }
	    cout << "data received successfully" << endl<<endl<<endl;

         parseProducts(response, products);
         curl_easy_cleanup(curl);

     }
     else {
         std::cerr << "Error initializing libcurl" << std::endl;
         return 1;
     }
     return 0;
 }




  int getCart(string id)
 {     
     CURL* curl = curl_easy_init();
     vector<ProductCart> products;

     if (curl)
     {
         string url = "http://localhost:3000/get-order/12345";
         cout<< url << endl;
         Response response;
         curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/get-order/12345");

         // Set the write callback function
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

         // Pass the address of the Response object
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

         CURLcode res = curl_easy_perform(curl);
         if (res != CURLE_OK)
         {
             std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
         }
         else
         {
             // Now response.getData() contains the received data, you can store/process it further
             std::cout << "Received data: " << response.getData() << std::endl;
         }
          parseProductsCart(response, products);

          curl_easy_cleanup(curl);
          return  0;
     }
     else
     {
         cerr << "Error initializing libcurl" << std::endl;
         return 1;
     }
 }


   int orderFood(ProductCart product) {

     CURL* curl;
          curl = curl_easy_init();
          CURLcode res;
     string json = product.toJson();

     if (curl)
     {
         // Set cURL options
         curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/order-food");
         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
         curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.length());

         // Set request headers
         struct curl_slist* headers = NULL;
         headers = curl_slist_append(headers, "Content-Type: application/json");
         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

         // Perform the POST request
         CURLcode res = curl_easy_perform(curl);

         // Cleanup
         curl_slist_free_all(headers);
         curl_easy_cleanup(curl);


         if (res != CURLE_OK)
         {
             std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
             return 1;
         }
         return 0;;
     }
     else {
		 std::cerr << "Error initializing libcurl" << std::endl;
		 return 1;
	 }
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
         product.fromJson(productJson);
         products.push_back(product);
     }

     return 0;
 }


 int parseProductsCart(Response response, std::vector<ProductCart>& products)
 {
     rapidjson::Document doc;
     doc.Parse(response.getData().c_str());

     if (!doc.IsArray())
     {
        cout<< response.getData()<<endl;
         std::cerr << "Invalid JSON format: Not an array" << std::endl;
         return 1;
     }

     // Iterate over each product in the JSON array
     for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
     {
         const rapidjson::Value& productJson = doc[i];

         // Create a Product object and populate its fields
         ProductCart product;
         product.fromJson(productJson);
         products.push_back(product);
     }
     return 0;
 }
