
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
}