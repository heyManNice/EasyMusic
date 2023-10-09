#include "utils.h"

#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

#include <Windows.h>

std::string WideStringToString(const std::wstring& wstr)
{
    if (wstr.empty())
    {
        return std::string();
    }
    size_t pos;
    size_t begin = 0;
    std::string ret;

    int size;
    pos = wstr.find(static_cast<wchar_t>(0), begin);
    while (pos != std::wstring::npos && begin < wstr.length())
    {
        std::wstring segment = std::wstring(&wstr[begin], pos - begin);
        size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &segment[0], segment.size(), NULL, 0, NULL, NULL);
        std::string converted = std::string(size, 0);
        WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &segment[0], segment.size(), &converted[0], converted.size(), NULL, NULL);
        ret.append(converted);
        ret.append({ 0 });
        begin = pos + 1;
        pos = wstr.find(static_cast<wchar_t>(0), begin);
    }
    if (begin <= wstr.length())
    {
        std::wstring segment = std::wstring(&wstr[begin], wstr.length() - begin);
        size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &segment[0], segment.size(), NULL, 0, NULL, NULL);
        std::string converted = std::string(size, 0);
        WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &segment[0], segment.size(), &converted[0], converted.size(), NULL, NULL);
        ret.append(converted);
    }
    return ret;
}
