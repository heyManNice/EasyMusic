#ifndef __UTFCONVERT_H__
#define __UTFCONVERT_H__
#include <string>


// 从UTF16编码字符串构建，需要带BOM标记
std::string utf16_to_utf8(const std::u16string& u16str);

// 从UTF16 LE编码的字符串创建
std::string utf16le_to_utf8(const std::u16string& u16str);

// 从UTF16BE编码字符串创建
std::string utf16be_to_utf8(const std::u16string& u16str);

// 获取转换为UTF-16 LE编码的字符串
std::u16string utf8_to_utf16le(const std::string& u8str, bool addbom = false, bool* ok = NULL);

// 获取转换为UTF-16 BE的字符串
std::u16string utf8_to_utf16be(const std::string& u8str, bool addbom = false, bool* ok = NULL);

#endif //! __UTFCONVERT_H__
