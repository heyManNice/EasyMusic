#ifndef EASYMUSIC_UTILS_H_
#define EASYMUSIC_UTILS_H_

#include <string>

//https://www.cnblogs.com/oloroso/p/6801076.html
#include "utfconvert.h"

//字符集转换
std::string URLEncode(std::wstring originalText);
std::string WideStringToString(const std::wstring& wstr);

#endif // !EASYMUSIC_UTILS_H_
