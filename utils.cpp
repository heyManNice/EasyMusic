#include "utils.h"

#include <string>

std::string URLEncode(const std::wstring& originalText)
{
    std::string ret;
    constexpr auto hex = L"0123456789abcdef";
    for (auto& ch : originalText)
    {
        if ((L'a' <= ch && ch <= L'z')
            || (L'A' <= ch && ch <= L'Z')
            || (L'0' <= ch && ch <= L'9')) {
            ret += ch;
        }
        else {
            ret += L'%';
            ret += hex[ch >> 4];
            ret += hex[ch & 15];
        }
    }
    return std::move(ret);
}
