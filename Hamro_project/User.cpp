#include "User.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int User::getPassword()
{
    return password;
}
std::string User::getUsername()
{
    return username;
}
int User::getUserId()
{
    return userId;
}
std::string User::getEmail()
{
    return email;
}
std::string User::getName()
{
    return username;
}
void User::setUsername(std::string username)
{
    this->username = username;
}
void User::setEmail(std::string email)
{
    this->email = email;
}
void User::setPassword(int password)
{
    this->password = password;
}
void User::setUserId(int userId)
{
    this->userId = userId;
}
std::string User::toJson() const
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("email");
    writer.String(this->email.c_str());
    writer.Key("password");
    writer.String(std::to_string(this->password).c_str());
    if (this->username != "")
    {
        writer.Key("data");
        writer.StartObject();
        writer.Key("username");
        writer.String(this->username.c_str());
        writer.Key("id");
        writer.Int(this->userId);
        writer.EndObject();
    }

    writer.EndObject();
    return s.GetString();
}
void User::fromJson(const rapidjson::Value &json)
{
    if (json["user"].HasMember("user_metadata"))
    {
        this->email = json["user"]["user_metadata"]["email"].GetString();
        this->userId = json["user"]["user_metadata"]["id"].GetInt();
        this->username = json["user"]["user_metadata"]["username"].GetString();
    }
}