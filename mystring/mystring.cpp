//
// Created by chenzhigang on 23-11-12.
//

#include "mystring.h"

#include <cstring>

// 计算 C 字符串长度（不含结尾 '\0'）
size_t mystring::str_len(const char *str) {
    size_t n = 0;
    while (str && str[n] != '\0') {
        ++n;
    }
    return n;
}

mystring::mystring() : data_(new char[1]), size_(0) {
    data_[0] = '\0';
}

mystring::mystring(const char *str) {
    size_ = str_len(str);
    data_ = new char[size_ + 1];
    std::memcpy(data_, str ? str : "", size_);
    data_[size_] = '\0';
}

mystring::mystring(const mystring &other) : size_(other.size_) {
    data_ = new char[size_ + 1];
    std::memcpy(data_, other.data_, size_ + 1);
}

mystring &mystring::operator=(const mystring &other) {
    if (this == &other) {
        return *this;
    }
    char *new_data = new char[other.size_ + 1];
    std::memcpy(new_data, other.data_, other.size_ + 1);
    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
    return *this;
}

mystring::~mystring() {
    delete[] data_;
}

// 字符串拼接：把 other 追加到当前字符串末尾
mystring &mystring::concat(const mystring &other) {
    size_t new_size = size_ + other.size_;
    char *new_data = new char[new_size + 1];
    std::memcpy(new_data, data_, size_);
    std::memcpy(new_data + size_, other.data_, other.size_ + 1);
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
    return *this;
}

mystring &mystring::operator+=(const mystring &other) {
    return concat(other);
}

mystring mystring::operator+(const mystring &other) const {
    mystring result(*this);
    result.concat(other);
    return result;
}

const char *mystring::c_str() const {
    return data_;
}

size_t mystring::size() const {
    return size_;
}
