#include "utfconvert.h"

#include <stdint.h>
#ifdef __GNUC__
#include <endian.h>
#endif // __GNUC__

static inline uint16_t byteswap_ushort(uint16_t number)
{
#if defined(_MSC_VER) && _MSC_VER > 1310
	return _byteswap_ushort(number);
#elif defined(__GNUC__)
	return __builtin_bswap16(number);
#else
	return (number >> 8) | (number << 8);
#endif
}


////////////////////////////////////////
//     以下转换都是在小端序下进行     //
////////////////////////////////////////

// 从UTF16编码字符串构建，需要带BOM标记
std::string utf16_to_utf8(const std::u16string& u16str)
{
	if (u16str.empty()) { return std::string(); }
	//Byte Order Mark
	char16_t bom = u16str[0];
	switch (bom) {
	case 0xFEFF:	//Little Endian
		return utf16le_to_utf8(u16str);
		break;
	case 0xFFFE:	//Big Endian
		return utf16be_to_utf8(u16str);
		break;
	default:
		return std::string();
	}
}


// 从UTF16 LE编码的字符串创建
std::string utf16le_to_utf8(const std::u16string& u16str)
{
	if (u16str.empty()) { return std::string(); }
	const char16_t* p = u16str.data();
	std::u16string::size_type len = u16str.length();
	if (p[0] == 0xFEFF) {
		p += 1;	//带有bom标记，后移
		len -= 1;
	}

	// 开始转换
	std::string u8str;
	u8str.reserve(len * 3);

	char16_t u16char;
	for (std::u16string::size_type i = 0; i < len; ++i) {
		// 这里假设是在小端序下(大端序不适用)
		u16char = p[i];

		// 1字节表示部分
		if (u16char < 0x0080) {
			// u16char <= 0x007f
			// U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
			u8str.push_back((char)(u16char & 0x00FF));	// 取低8bit
			continue;
		}
		// 2 字节能表示部分
		if (u16char >= 0x0080 && u16char <= 0x07FF) {
			// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
		// 代理项对部分(4字节表示)
		if (u16char >= 0xD800 && u16char <= 0xDBFF) {
			// * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
			uint32_t highSur = u16char;
			uint32_t lowSur = p[++i];
			// 从代理项对到UNICODE代码点转换
			// 1、从高代理项减去0xD800，获取有效10bit
			// 2、从低代理项减去0xDC00，获取有效10bit
			// 3、加上0x10000，获取UNICODE代码点值
			uint32_t codePoint = highSur - 0xD800;
			codePoint <<= 10;
			codePoint |= lowSur - 0xDC00;
			codePoint += 0x10000;
			// 转为4字节UTF8编码表示
			u8str.push_back((char)((codePoint >> 18) | 0xF0));
			u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
			u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
			u8str.push_back((char)((codePoint & 0x3F) | 0x80));
			continue;
		}
		// 3 字节表示部分
		{
			// * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
			u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
	}

	return u8str;
}


// 从UTF16BE编码字符串创建
std::string utf16be_to_utf8(const std::u16string& u16str)
{
	if (u16str.empty()) { return std::string(); }
	const char16_t* p = u16str.data();
	std::u16string::size_type len = u16str.length();
	if (p[0] == 0xFEFF) {
		p += 1;	//带有bom标记，后移
		len -= 1;
	}


	// 开始转换
	std::string u8str;
	u8str.reserve(len * 2);
	char16_t u16char;	//u16le 低字节存低位，高字节存高位
	for (std::u16string::size_type i = 0; i < len; ++i) {
		// 这里假设是在小端序下(大端序不适用)
		u16char = p[i];
		// 将大端序转为小端序
		u16char = byteswap_ushort(u16char);

		// 1字节表示部分
		if (u16char < 0x0080) {
			// u16char <= 0x007f
			// U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
			u8str.push_back((char)(u16char & 0x00FF));
			continue;
		}
		// 2 字节能表示部分
		if (u16char >= 0x0080 && u16char <= 0x07FF) {
			// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
		// 代理项对部分(4字节表示)
		if (u16char >= 0xD800 && u16char <= 0xDBFF) {
			// * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
			uint32_t highSur = u16char;
			uint32_t lowSur = byteswap_ushort(p[++i]);
			// 从代理项对到UNICODE代码点转换
			// 1、从高代理项减去0xD800，获取有效10bit
			// 2、从低代理项减去0xDC00，获取有效10bit
			// 3、加上0x10000，获取UNICODE代码点值
			uint32_t codePoint = highSur - 0xD800;
			codePoint <<= 10;
			codePoint |= lowSur - 0xDC00;
			codePoint += 0x10000;
			// 转为4字节UTF8编码表示
			u8str.push_back((char)((codePoint >> 18) | 0xF0));
			u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
			u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
			u8str.push_back((char)((codePoint & 0x3F) | 0x80));
			continue;
		}
		// 3 字节表示部分
		{
			// * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
			u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
	}
	return u8str;
}






// 获取转换为UTF-16 LE编码的字符串
std::u16string utf8_to_utf16le(const std::string& u8str, bool addbom, bool* ok)
{
	std::u16string u16str;
	u16str.reserve(u8str.size());
	if (addbom) {
		u16str.push_back(0xFEFF);	//bom (字节表示为 FF FE)
	}
	std::string::size_type len = u8str.length();

	const unsigned char* p = (unsigned char*)(u8str.data());
	// 判断是否具有BOM(判断长度小于3字节的情况)
	if (len > 3 && p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF) {
		p += 3;
		len -= 3;
	}

	bool is_ok = true;
	// 开始转换
	for (std::string::size_type i = 0; i < len; ++i) {
		uint32_t ch = p[i];	// 取出UTF8序列首字节
		if ((ch & 0x80) == 0) {
			// 最高位为0，只有1字节表示UNICODE代码点
			u16str.push_back((char16_t)ch);
			continue;
		}
		switch (ch & 0xF0)
		{
		case 0xF0: // 4 字节字符, 0x10000 到 0x10FFFF
		{
			uint32_t c2 = p[++i];
			uint32_t c3 = p[++i];
			uint32_t c4 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低3bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x07U) << 18) | ((c2 & 0x3FU) << 12) | ((c3 & 0x3FU) << 6) | (c4 & 0x3FU);
			if (codePoint >= 0x10000)
			{
				// 在UTF-16中 U+10000 到 U+10FFFF 用两个16bit单元表示, 代理项对.
				// 1、将代码点减去0x10000(得到长度为20bit的值)
				// 2、high 代理项 是将那20bit中的高10bit加上0xD800(110110 00 00000000)
				// 3、low  代理项 是将那20bit中的低10bit加上0xDC00(110111 00 00000000)
				codePoint -= 0x10000;
				u16str.push_back((char16_t)((codePoint >> 10) | 0xD800U));
				u16str.push_back((char16_t)((codePoint & 0x03FFU) | 0xDC00U));
			}
			else
			{
				// 在UTF-16中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF 与Unicode代码点值相同.
				// U+D800 到 U+DFFF 是无效字符, 为了简单起见，这里假设它不存在(如果有则不编码)
				u16str.push_back((char16_t)codePoint);
			}
		}
		break;
		case 0xE0: // 3 字节字符, 0x800 到 0xFFFF
		{
			uint32_t c2 = p[++i];
			uint32_t c3 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低4bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x0FU) << 12) | ((c2 & 0x3FU) << 6) | (c3 & 0x3FU);
			u16str.push_back((char16_t)codePoint);
		}
		break;
		case 0xD0: // 2 字节字符, 0x80 到 0x7FF
		case 0xC0:
		{
			uint32_t c2 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低5bit，其余取6bit)
			uint32_t codePoint = ((ch & 0x1FU) << 12) | ((c2 & 0x3FU) << 6);
			u16str.push_back((char16_t)codePoint);
		}
		break;
		default:	// 单字节部分(前面已经处理，所以不应该进来)
			is_ok = false;
			break;
		}
	}
	if (ok != NULL) { *ok = is_ok; }

	return u16str;
}


// 获取转换为UTF-16 BE的字符串
std::u16string utf8_to_utf16be(const std::string& u8str, bool addbom, bool* ok)
{
	// 先获取utf16le编码字符串
	std::u16string u16str = utf8_to_utf16le(u8str, addbom, ok);
	// 将小端序转换为大端序
	for (size_t i = 0; i < u16str.size(); ++i) {
		u16str[i] = byteswap_ushort(u16str[i]);
	}
	return u16str;
}
