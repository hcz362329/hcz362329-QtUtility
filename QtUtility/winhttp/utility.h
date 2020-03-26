// Copyright (c) 2019, cz. All rights reserved.
// file: common_cz/utility.h

#ifndef UTILITY_H
#define UTILITY_H
#include <windows.h>
#include <string>
#include <vector>

namespace common_cz
{
	/*default_cp= CP_UTF8*/
	std::wstring cp_encode(const std::string& src, const UINT cp = CP_UTF8);
	std::string cp_encode(const std::wstring& src, const UINT cp = CP_UTF8);

	std::string UnicodeToAscii( const std::wstring& in_str );

	bool GetProcessFolderPath(std::wstring* folder_path);
	bool IsDirectoryExist(const std::string& directory);
	bool IsDirectoryExist(const std::wstring& directory);

	std::wstring GetMac();
	std::string StringFormat(const char *fmt, ...);
}
#endif