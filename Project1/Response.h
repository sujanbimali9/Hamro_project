#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response
{
public:
    void appendData(const char *data, size_t size);
    std::string getData() const;

private:
    std::string data_;
};

#endif
