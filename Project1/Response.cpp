#include "Response.h"

void Response::appendData(const char* data, size_t size) {
    data_.append(data, size);

}

std::string Response::getData() const {
    return data_;
}
