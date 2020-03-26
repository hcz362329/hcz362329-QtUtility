/*************************************************************************************************
time:2018/10/22
**************************************************************************************************/
#pragma once
#pragma pack(push,1)
#include <Windows.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;
class FuncHelper
{
public:
	static WCHAR * CommandLine_AnalysisW(WCHAR* argv,WCHAR* sub_str)
	{
		if ( argv == NULL || sub_str == NULL )
		{
			return NULL;
		}
		WCHAR *pszFind = NULL;
		pszFind = wcsstr(argv,sub_str);
		if ( wcsstr(argv,sub_str) )
		{
			pszFind += lstrlenW(sub_str);
		}
		if ( pszFind )
		{
			return pszFind;
		}
		return NULL;
	}

	static char * CommandLine_Analysis(char* argv,char* sub_str)
	{
		if ( argv == NULL || sub_str == NULL )
		{
			return NULL;
		}
		char *pszFind = NULL;
		pszFind = strstr(argv,sub_str);
		if ( strstr(argv,sub_str) )
		{
			pszFind += lstrlenA(sub_str);
		}
		if ( pszFind )
		{
			return pszFind;
		}
		return NULL;
	}

	static WCHAR *utf8ToUnicode(const char *pszStrUtf8){
		int nChar;
		WCHAR *pszWideStr;

		nChar = MultiByteToWideChar(CP_UTF8, 0, pszStrUtf8, -1, NULL, 0);
		pszWideStr = (WCHAR *)malloc( nChar*sizeof(pszWideStr[0]) );
		if( pszWideStr==NULL ){
			return NULL;
		}
		nChar = MultiByteToWideChar(CP_UTF8, 0, pszStrUtf8, -1, pszWideStr, nChar);
		if( nChar==0 ){
			free(pszWideStr);
			pszWideStr = NULL;
		}
		return pszWideStr;
	}

	/*
	** Convert microsoft unicode to UTF-8.  Space to hold the returned string is
	** obtained from malloc().
	*/
	static std::string UnicodeToUtf8(const WCHAR *pszWideStr)
	{
		int nLength = WideCharToMultiByte(CP_UTF8, 0, pszWideStr, -1, 0, 0, 0, 0);
		if ( nLength > 0 )
		{
			std::vector<char> vecChar(nLength);
			nLength = WideCharToMultiByte(CP_UTF8, 0, pszWideStr, -1, &vecChar[0], nLength,0, 0);
			if( nLength == 0 ){
				return std::string();
			}
			return std::string(&vecChar[0]);
		}
		return std::string();
	}

	//返回值替换的次数
	static int Replace(char* src,const char need_replace,const char replace_to )
	{
		int n = 0;
		if (src==NULL)
			return n;
		size_t length = strlen(src);
		for (int i=0;i<length;++i)
		{
			if (src[i]==need_replace)
			{
				src[i]=replace_to;
				n++;
			}
		}
		return n;
	}
	/*
	====== _tcstol unicode: wcstol  
	====== _tcstol ansci  : strtol	
	====== base_decimal :进制 2 8 10 16 
	*/
	static long StringToLong(const char* szStart,char** szEnd,int base_decimal=10)
	{
		long value_ret = 0;
		if ( szStart == NULL )
		{
			return value_ret;
		}
		value_ret = strtol(szStart,szEnd,base_decimal);
		return value_ret;
	}
	static long StringToLongW(const WCHAR* szStart,WCHAR** szEnd,int base_decimal=10)
	{
		long value_ret = 0;
		if ( szStart == NULL )
		{
			return value_ret;
		}
		value_ret = wcstol(szStart,szEnd,base_decimal);
		return value_ret;
	}

	static std::string UnicodeToAscii(const std::wstring& in_str)
	{
		int nNeedLength = WideCharToMultiByte(CP_ACP,0,in_str.c_str(),-1,0,0,0,0);
		if ( nNeedLength > 0 )
		{
			std::vector<char> vecChar(nNeedLength);
			::WideCharToMultiByte(CP_ACP,0,in_str.c_str(),-1,&vecChar[0],nNeedLength,0,0);
			return std::string(&vecChar[0]);
		}
		return std::string();
	}

	static std::wstring AnsciiToUnicode(const std::string& in_str)
	{
		int nNeedLength = MultiByteToWideChar(CP_ACP,0,in_str.c_str(),-1,0,0);
		if ( nNeedLength > 0 )
		{
			std::vector<wchar_t> vecWChar(nNeedLength);
			::MultiByteToWideChar(CP_ACP,0,in_str.c_str(),-1,&vecWChar[0],nNeedLength);
			return std::wstring(&vecWChar[0]);
		}
		return std::wstring();
	}

	std::string Anscii2Utf8(const char* data)
	{
		std::wstring strUnicode = AnsciiToUnicode(data);
		std::string strUtf = UnicodeToUtf8(strUnicode.c_str());
		return strUtf;
	}
};

#pragma pack(pop)