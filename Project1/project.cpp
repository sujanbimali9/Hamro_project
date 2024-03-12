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
 };

 class ProductCart: public Product{
 public:
	 int quantity;
     string userid;
     string location;
     string name;
    

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
 //string serializeProductCart(const ProductCart& productCart);
 string convertToJSON(const ProductCart& cart);
 int orderFood();



// Callback function to write received data into a Response object
 size_t write_callback(void* contents, size_t size, size_t nmemb, Response* response) {
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
     }

     char opt;

     do {

         int a = products.size();
         cout << "enter a no"<<endl;
         cin >> a;
         opt = 'n';

         switch (a) {
         case 1:        
             getCartData("12345");
             cout << 1 << endl;
             break;
         case 2:
             getData();
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


 static int getCartData(string id)
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
         std::cerr << "Error initializing libcurl" << std::endl;
         return 1;
     }
 }



 string convertToJSON(const ProductCart& cart) {
     rapidjson::StringBuffer s;
     rapidjson::Writer < rapidjson:: StringBuffer > writer(s);
     writer.StartObject();
     writer.Key("id"); writer.String(cart.id.c_str());
     writer.Key("title"); writer.String(cart.title.c_str());
     writer.Key("price"); writer.Double(cart.price);
     writer.Key("description"); writer.String(cart.description.c_str());
     writer.Key("category"); writer.String(cart.category.c_str());
     writer.Key("image"); writer.String(cart.image.c_str());
     writer.Key("rating"); writer.Double(cart.rating);
     writer.Key("ratingCount"); writer.Int(cart.ratingCount);
     writer.Key("quantity"); writer.Int(cart.quantity);
     writer.Key("userid"); writer.String(cart.userid.c_str());
     writer.Key("name"); writer.String(cart.name.c_str());
     writer.Key("location"); writer.String(cart.location.c_str());
     writer.EndObject();
     return s.GetString();
 }




 int main() {

     ProductCart product;
     product.id = "12345";
     product.title = "Pizza";
     product.price = 9.99;
     product.description = "Delicious pizza";
     product.category = "Food";
     product.image = "pizza.jpg";
     product.rating = 4.5;
     product.ratingCount = 100;
     product.quantity = 2;
     product.userid = "user123";
     product.name = "sujan";
     product.location = "Location";
     CURL* curl;
     CURLcode res;
     curl = curl_easy_init();
     string json = convertToJSON(product);
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
         res = curl_easy_perform(curl);

         // Cleanup
         curl_slist_free_all(headers);
         curl_easy_cleanup(curl);
     }

     if (res != CURLE_OK)
     {
		 std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
	 }
     return res;
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
         product.id = productJson["foodid"].GetString();
         product.title = productJson["title"].GetString();
         product.price = productJson["price"].GetDouble();
         product.description = productJson["description"].GetString();
         product.category = productJson["category"].GetString();
         product.image = productJson["image"].GetString();
         product.rating = productJson["rating"].GetDouble();
         product.ratingCount = productJson["ratingCount"].GetInt();
         product.quantity = productJson["quantity"].GetInt();
         product.location = productJson["location"].GetString();

         cout<< "Product id: " << product.id << endl;
         cout<< "Product title: " << product.title << endl;
         cout<< "Product price: " << product.price << endl;
         cout<< "Product description: " << product.description << endl;

         products.push_back(product);
     }
     cout<< "cart data received successfully" << endl;

     return 0;
 }

 //
 //string serializeProductCart(const ProductCart& productCart)
 //{
 //    rapidjson::Document document;
 //    document.SetObject();
 //    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

 //    document.AddMember("id", productCart.id, allocator);
 //    document.AddMember("title", productCart.title, allocator);
 //    document.AddMember("price", to_string(productCart.price), allocator);
 //    document.AddMember("description", productCart.description, allocator);
 //    document.AddMember("category", productCart.category, allocator);
 //    document.AddMember("image", productCart.image, allocator);
 //    document.AddMember("rating", to_string(productCart.rating), allocator);
 //    document.AddMember("ratingCount", productCart.ratingCount, allocator);
 //    document.AddMember("quantity", to_string(productCart.quantity), allocator);
 //    document.AddMember("location", productCart.location, allocator);

 //    rapidjson::StringBuffer buffer;
 //    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
 //    document.Accept(writer);
 //    cout<< buffer.GetString()<<endl;

 //    return buffer.GetString();
 //}

