//
// Created by chenzhigang on 23-11-12.
//

#ifndef JDI_MYSTRING_H
#define JDI_MYSTRING_H

#include <cstddef>

class mystring {
public:
    mystring();
    mystring(const char *str);
    mystring(const mystring &other);
    mystring &operator=(const mystring &other);
    ~mystring();

    // 字符串拼接：把 other 追加到当前字符串末尾
    mystring &concat(const mystring &other);

    // 运算符形式的拼接
    mystring &operator+=(const mystring &other);
    mystring operator+(const mystring &other) const;

    const char *c_str() const;
    size_t size() const;

private:
    char *data_;   // 以 '\0' 结尾的字符数组
    size_t size_;  // 不含结尾 '\0' 的字符个数

    static size_t str_len(const char *str);
};

#endif //JDI_MYSTRING_H
