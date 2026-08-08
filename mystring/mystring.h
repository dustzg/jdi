//
// Created by chenzhigang on 23-11-12.
//

#ifndef JDI_MYSTRING_H
#define JDI_MYSTRING_H

#include <cstddef>

/**
 * @brief 一个简易的字符串类，内部使用以 '\0' 结尾的动态字符数组管理内存。
 *
 * 支持拷贝语义与字符串拼接。所有会改变内容的操作都会重新分配缓冲区，
 * 因此对同一对象自身进行拼接（如 @c s += s）也是安全的。
 */
class mystring {
public:
    /** @brief 构造空字符串，size() 为 0。 */
    mystring();

    /**
     * @brief 由 C 风格字符串构造。
     * @param str 以 '\0' 结尾的字符串；传入 @c nullptr 时视为空字符串。
     */
    mystring(const char *str);

    /**
     * @brief 拷贝构造，深拷贝对方的字符数据。
     * @param other 被拷贝的对象。
     */
    mystring(const mystring &other);

    /**
     * @brief 拷贝赋值，深拷贝对方的字符数据（可安全自赋值）。
     * @param other 被赋值的对象。
     * @return 对当前对象的引用。
     */
    mystring &operator=(const mystring &other);

    /** @brief 析构，释放内部缓冲区。 */
    ~mystring();

    /**
     * @brief 字符串拼接：把 @p other 追加到当前字符串末尾。
     * @param other 要追加的字符串。
     * @return 对当前对象的引用，便于链式调用。
     * @note 会重新分配缓冲区，故 @c s.concat(s) 这类自拼接也是安全的。
     */
    mystring &concat(const mystring &other);

    /**
     * @brief 运算符形式的原地拼接，等价于 concat()。
     * @param other 要追加的字符串。
     * @return 对当前对象的引用。
     */
    mystring &operator+=(const mystring &other);

    /**
     * @brief 运算符形式的拼接，返回拼接后的新对象，不修改任一操作数。
     * @param other 要追加的字符串。
     * @return 拼接结果的新对象。
     */
    mystring operator+(const mystring &other) const;

    /**
     * @brief 获取底层的 C 风格字符串。
     * @return 以 '\0' 结尾的只读字符指针，始终非空。
     */
    const char *c_str() const;

    /**
     * @brief 获取字符个数。
     * @return 不含结尾 '\0' 的字符个数。
     */
    size_t size() const;

private:
    char *data_;   ///< 以 '\0' 结尾的字符数组。
    size_t size_;  ///< 不含结尾 '\0' 的字符个数。

    /**
     * @brief 计算 C 字符串长度。
     * @param str 以 '\0' 结尾的字符串，可为 @c nullptr。
     * @return 不含结尾 '\0' 的字符个数；@p str 为 @c nullptr 时返回 0。
     */
    static size_t str_len(const char *str);
};

#endif //JDI_MYSTRING_H
