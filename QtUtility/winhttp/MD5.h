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

	//����:MD5����[ANSII]
	//����:
	//      char *pszOutput OUT �����MD5�ַ������ò��������鳤�ȱ�����ڵ��� MD5_STRING_SIZE [�����ڴ��쳣]
	//      UCHAR *pBytes IN ��Ҫ���б���Ļ�������ַ
	//      UINT uBytesLen IN ��Ҫ���б���Ļ�������С
	//����ֵ: ����ʧ��ʱ����NULL���ɹ�ʱ���ز���pszOutputָ��ĵ�ַָ��
	static char *EncodeBytesA(char *pszOutput, UCHAR *pBytes, UINT uBytesLen);

	//����:MD5����[UNICODE]
	//����:
	//      char *pszOutput OUT �����MD5�ַ������ò��������鳤�ȱ�����ڵ��� MD5_STRING_SIZE [�����ڴ��쳣]
	//      UCHAR *pBytes IN ��Ҫ���б���Ļ�������ַ
	//      UINT uBytesLen IN ��Ҫ���б���Ļ�������С
	//����ֵ: ����ʧ��ʱ����NULL���ɹ�ʱ���ز���pszOutputָ��ĵ�ַָ��
	static WCHAR *EncodeBytesW(WCHAR *pszOutput, UCHAR *pBytes, UINT uBytesLen);

	static char* MDStringA(char *pszOutput, const char *pszText);

	static WCHAR* MDStringW(WCHAR *pszOutput, const WCHAR *pszText);

	static char* MDFileA(char *pszOutput,char *pszFilename);

	static WCHAR* MDFileW(WCHAR *pszOutput,WCHAR *pszFilename);

	static char* hmac_md5A(char *pszOutput, char* pszText, char* pszKey);

	static WCHAR* hmac_md5W(WCHAR *pszOutput, WCHAR* pszText, WCHAR* pszKey);
};


#endif