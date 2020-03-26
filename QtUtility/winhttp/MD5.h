#ifndef SYSBASE_TEXTENCODE_MD5_H
#define SYSBASE_TEXTENCODE_MD5_H

#include <windows.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

#define MD5_LENGTH 32

#define MD5_STRING_SIZE 33


class  Cmd5
{
public:

	//功能:MD5编码[ANSII]
	//参数:
	//      char *pszOutput OUT 输出的MD5字符串，该参数的数组长度必须大于等于 MD5_STRING_SIZE [否则内存异常]
	//      UCHAR *pBytes IN 需要进行编码的缓冲区地址
	//      UINT uBytesLen IN 需要进行编码的缓冲区大小
	//返回值: 编码失败时返回NULL，成功时返回参数pszOutput指向的地址指针
	static char *EncodeBytesA(char *pszOutput, UCHAR *pBytes, UINT uBytesLen);

	//功能:MD5编码[UNICODE]
	//参数:
	//      char *pszOutput OUT 输出的MD5字符串，该参数的数组长度必须大于等于 MD5_STRING_SIZE [否则内存异常]
	//      UCHAR *pBytes IN 需要进行编码的缓冲区地址
	//      UINT uBytesLen IN 需要进行编码的缓冲区大小
	//返回值: 编码失败时返回NULL，成功时返回参数pszOutput指向的地址指针
	static WCHAR *EncodeBytesW(WCHAR *pszOutput, UCHAR *pBytes, UINT uBytesLen);

	static char* MDStringA(char *pszOutput, const char *pszText);

	static WCHAR* MDStringW(WCHAR *pszOutput, const WCHAR *pszText);

	static char* MDFileA(char *pszOutput,char *pszFilename);

	static WCHAR* MDFileW(WCHAR *pszOutput,WCHAR *pszFilename);

	static char* hmac_md5A(char *pszOutput, char* pszText, char* pszKey);

	static WCHAR* hmac_md5W(WCHAR *pszOutput, WCHAR* pszText, WCHAR* pszKey);
};


#endif