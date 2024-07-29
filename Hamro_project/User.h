#ifndef USER_H
#define USER_H
#include <string>
#include "rapidjson/document.h"

class User
{
private:
    std::string username;
    std::string email;
    int password;
    int userId;

public:
    User(){};
    User(std::string username, std::string email, int password, int userId) : username(username), email(email), password(password), userId(userId){};
    void setUsername(std::string username);
    void setEmail(std::string email);
    void setPassword(int password);
    void setUserId(int userId);
    std::string getUsername();
    int getPassword();
    int getUserId();
    std::string getEmail();
    std::string getName();
    std::string toJson() const;
    void fromJson(const rapidjson::Value &json);
};
#endif
