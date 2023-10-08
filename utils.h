#ifndef EASYMUSIC_UTILS_H_
#define EASYMUSIC_UTILS_H_

#include <string>

//字符集转换
std::string Utf8ToGbk(const char* src_str);
std::string GbkToUtf8(const char* src_str);

inline std::string Utf8ToGbk(std::string str) { return Utf8ToGbk(str.c_str()); };


#endif // !EASYMUSIC_UTILS_H_
