#include "utility.h"

#include <windows.h>
#include <algorithm>
#include <shellapi.h>
#include <vector>

namespace common_cz
{
	std::wstring cp_encode(const std::string& src, const UINT cp /*= CP_UTF8*/)
	{
		const int len = static_cast<int>(src.length());
		std::wstring enc;
		const int req = MultiByteToWideChar(cp, 0, src.c_str(), len, NULL, 0);
		if (req > 0) {
			enc.resize(static_cast<size_t>(req));
			MultiByteToWideChar(cp, 0, src.c_str(), len, &enc[0], req);
		}
		return enc;
	}

	std::string cp_encode(const std::wstring& src, const UINT cp /*= CP_UTF8*/)
	{
		const int len = static_cast<int>(src.length());
		std::string enc;
		const int req = WideCharToMultiByte(cp, 0, src.c_str(), len, 0, 0, NULL, NULL);
		if (req > 0) {
			enc.resize(static_cast<size_t>(req));
			WideCharToMultiByte(cp, 0, src.c_str(), len, &enc[0], req, NULL, NULL);
		}
		return enc;
	}

	std::string UnicodeToAscii( const std::wstring& in_str )
	{
		int nNeedChars = WideCharToMultiByte( CP_ACP, 0, in_str.c_str(), -1, 0, 0, 0, 0 );
		if (nNeedChars > 0)//再次判断一下
		{	
			std::vector<char> temp(nNeedChars);
			::WideCharToMultiByte( CP_ACP, 0, in_str.c_str(), -1, &temp[0], nNeedChars, 0, 0 );
			return std::string(&temp[0]);
		}

		return std::string();
	}

	bool GetProcessFolderPath(std::wstring* folder_path) {
		std::wstring process_path;
		process_path.resize(MAX_PATH * 2);
		DWORD chars =
			::GetModuleFileNameW(NULL, &process_path[0], static_cast<DWORD>(process_path.size()));
		if (chars <= 0 || chars >= MAX_PATH * 2) {
			return false;
		}

		*folder_path = process_path;
		std::wstring::size_type position = folder_path->find_last_of(L"\\");
		if (position == std::wstring::npos) {
			return false;
		}

		folder_path->erase(position);
		return true;
	}

	bool IsDirectoryExist(const std::wstring& directory) {
		DWORD attr = GetFileAttributesW(directory.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
			return false;

		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	bool IsDirectoryExist(const std::string& directory) {
		return IsDirectoryExist(cp_encode(directory));
	}

	std::wstring GetMac()
	{
		static std::wstring strMac;
		strMac = L"00-55-66-77";
		return strMac;
	}

	std::string StringFormat(const char *fmt, ...) 
	{
		va_list ap;
		va_start(ap, fmt);
		const size_t SIZE = 4096;     
		char buffer[SIZE] = { 0 };
		vsnprintf_s( buffer, SIZE, _TRUNCATE, fmt, ap);
		va_end(ap);

		return std::string(buffer); 
	} 
	/*
#if _MSC_VER >= 1900
	std::u32string to_utf32(std::string utf8_string) {
		std::wstring_convert<std::codecvt_utf8<unsigned int>, unsigned int> convert;
		auto p = reinterpret_cast<const char*>(utf8_string.data());
		auto str = convert.from_bytes(p, p + utf8_string.size());
		std::u32string str32(str.begin(), str.end());
		return str32;
	}

	std::wstring to_utf16(std::string utf8_string) {
		return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t >{}.from_bytes(utf8_string);
	}
#else
	std::u32string to_utf32(std::string str) {
		return std::wstring_convert< std::codecvt_utf8<unsigned int>, unsigned int >{}.from_bytes(str);
	}
	std::wstring to_utf16(std::string utf8_string) {
		return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t >{}.from_bytes(str);
	}
#endif
*/
	std::string UTF8_GBK(const std::string& src, const UINT cp) {
		//multi->wide->multi
		UINT codePage1 = (cp == CP_ACP ? CP_UTF8 : CP_ACP);
		UINT codePage2 = cp;
		const int len = static_cast<int>(src.length());
		std::wstring enc;
		const int req = MultiByteToWideChar(codePage1, 0, src.c_str(), len, NULL, 0);
		if (req > 0) {
			enc.resize(static_cast<size_t>(req));
			MultiByteToWideChar(codePage1, 0, src.c_str(), len, &enc[0], req);
		}
		
		const int req2 = WideCharToMultiByte(codePage2, 0, enc.c_str(),-1,0,0,0,0);
		std::string dec;
		if (req2 > 0) {
			dec.resize(static_cast<size_t>(req2));
			WideCharToMultiByte(codePage2, 0, enc.c_str(), -1, &dec[0], req2, NULL, NULL);
		}
		return dec;
	}

	std::wstring MultiToWideStr(const std::string & gbkString, UINT  codePage) {
		const int len = static_cast<int>(gbkString.length());
		std::wstring enc;
		const int req = MultiByteToWideChar(codePage, 0, gbkString.c_str(), -1, NULL, 0);
		if (req > 0) {
			enc.resize(static_cast<size_t>(req));
			MultiByteToWideChar(codePage, 0, gbkString.c_str(), -1, &enc[0], req);
		}
		return enc;
	}
}