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

// 字符串匹配：查找子串 pattern 首次出现的位置，未找到返回 npos
size_t mystring::find(const mystring &pattern, size_t from) const {
    // 空串在 from 处匹配（from 不超过 size_ 时返回 from）
    if (pattern.size_ == 0) {
        return from <= size_ ? from : npos;
    }
    // 模式比剩余字符多则不可能匹配
    if (from > size_ || pattern.size_ > size_ - from) {
        return npos;
    }
    // 朴素匹配：以每个可能的起点 i 逐字符比较
    for (size_t i = from; i <= size_ - pattern.size_; ++i) {
        size_t j = 0;
        // 从起点 i 开始比较，直到失配或匹配完整个模式
        while (j < pattern.size_ && data_[i + j] == pattern.data_[j]) {
            ++j;
        }
        // j 走完整个模式说明在 i 处完整匹配
        if (j == pattern.size_) {
            return i;
        }
    }
    return npos;
}

// 字符串匹配：C 风格子串重载，转成 mystring 后复用上面的查找逻辑
size_t mystring::find(const char *pattern, size_t from) const {
    return find(mystring(pattern), from);
}

// 是否包含子串 pattern
bool mystring::contains(const mystring &pattern) const {
    return find(pattern) != npos;
}

const char *mystring::c_str() const {
    return data_;
}

size_t mystring::size() const {
    return size_;
}
