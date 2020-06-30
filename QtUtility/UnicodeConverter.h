/* ----------------------------------------------------------
�ļ����ƣ�UnicodeConverter.h

���ߣ��ؽ���

MSN��splashcn@msn.com

��ǰ�汾��V1.0

��ʷ�汾��
V1.0	2010��03��12��
�����ʽ�汾��

����������
Unicode����ת����������utf-8��utf-16��UCS2����utf-32��UCS4��֮��ı���ת��
------------------------------------------------------------ */
#pragma once

#include <windows.h>
#include <stdio.h>
#include <ostream>

using namespace std;

class CUnicodeConverter
{
	/* -------------------------------------------------------------
	����ת��
	------------------------------------------------------------- */
public:
	/*
	���ܣ���UCS4����ת����UTF8����
	������
	dwUCS4��Ҫת����UCS4����
	pbUTF8�����ڴ洢ת�����UTF8���롣��ΪNULL�����Ի�ȡ������Ϣ���ֽ�����
	����ֵ��
	0����Ч��UCS4����
	1-6��UTF8�������Ч����
	*/
	static INT UCS4_To_UTF8(DWORD dwUCS4, BYTE* pbUTF8);

	/*
	���ܣ���UTF8����ת����UCS4����
	������
	pbUTF8��Ҫת����UTF8����
	dwUCS4���洢ת�����UCS4����
	����ֵ��
	0�������������Ч��UTF8����
	1-6��UTF8�������Ч����
	*/
	static INT UTF8_To_UCS4(const BYTE* pbUTF8, DWORD& dwUCS4);

	/*
	���ܣ���UCS4����ת����UTF16����
	������
	dwUCS4��Ҫת����UCS4����
	pwUTF16�����ڴ洢ת�����UTF16���롣��ΪNULL�����Ի�ȡ������Ϣ���ַ�����
	����ֵ��
	0����Ч��UCS4����
	1��ת����1��UTF16����
	2��ת����2��UTF16����
	*/
	static INT UCS4_To_UTF16(DWORD dwUCS4, WORD* pwUTF16);

	/*
	���ܣ���UTF16����ת����UCS4����
	������
	pwUTF16����Ҫת����UTF16����
	dwUCS4���洢ת�����UCS4����
	����ֵ��
	0�������������Ч��UTF16����
	1��1��UTF16���뱻ת��
	2��2��UTF16���뱻ת��
	*/
	static INT UTF16_To_UCS4(const WORD* pwUTF16, DWORD& dwUCS4);

	/*
	���ܣ���UTF8�ַ���ת����UTF16�ַ���
	������
	pbszUTF8Str����Ҫת����UTF8�ַ���
	pwszUTF16Str���洢ת�����UTF16�ַ�������ΪNULL�����Ի�ȡ���賤����Ϣ���ַ�����
	����ֵ��
	0��ת��ʧ��
	>0��UTF16�ַ�������
	*/
	static INT UTF8Str_To_UTF16Str(const BYTE* pbszUTF8Str, WORD* pwszUTF16Str);

	/*
	���ܣ���UTF16�ַ���ת����UTF8�ַ���
	������
	pwszUTF16Str����Ҫת����UTF16�ַ���
	pbszUTF8Str���洢ת�����UTF8�ַ�������ΪNULL�����Ի�ȡ���賤����Ϣ���ֽ�����
	����ֵ��
	0��ת��ʧ��
	>0��UTF8�ַ������ȣ�������NULL�ַ���
	*/
	static INT UTF16Str_To_UTF8Str(const WORD* pwszUTF16Str, BYTE* pbszUTF8Str);

	/* -------------------------------------------------------------
	C�ļ�д�����
	------------------------------------------------------------- */
public:
	/*
	���ܣ����ļ���д��UTF8����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8_By_UCS4(FILE* out, DWORD dwUCS4);

	/*
	���ܣ����ļ���д��UTF16����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16_By_UCS4(FILE* out, DWORD dwUCS4, BOOL isBigEndian = FALSE);

	/*
	���ܣ���UTF16�ַ�����UTF8����������ļ���
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8Str_By_UTF16Str(FILE* out, const WORD* pwszUTF16Str);

	/*
	���ܣ���UTF8�ַ�����UTF16����������ļ���
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16Str_By_UTF8Str(FILE* out, const BYTE* pbszUTF8Str, BOOL isBigEndian = FALSE);

	/*
	���ܣ����ļ������UTF8�����ֽ�����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8_BOM(FILE* out);

	/*
	���ܣ����ļ������UTF16�����ֽ�����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16_BOM(FILE* out, BOOL isBigEndian = FALSE);

	/* -------------------------------------------------------------
	C++���������
	------------------------------------------------------------- */
public:
	/*
	���ܣ�������д��UTF8����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8_By_UCS4(ostream& os, DWORD dwUCS4);

	/*
	���ܣ�������д��UTF16����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16_By_UCS4(ostream& os, DWORD dwUCS4, BOOL isBigEndian = FALSE);

	/*
	���ܣ���UTF16�ַ�����UTF8�������������
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8Str_By_UTF16Str(ostream& os, const WORD* pwszUTF16Str);

	/*
	���ܣ���UTF8�ַ�����UTF16�������������
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16Str_By_UTF8Str(ostream& os, const BYTE* pbszUTF8Str, BOOL isBigEndian = FALSE);

	/*
	���ܣ����������UTF8�����ֽ�����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF8_BOM(ostream& os);

	/*
	���ܣ����������UTF16�����ֽ�����
	����ֵ��
	д����ֽ���
	*/
	static UINT Print_UTF16_BOM(ostream& os, BOOL isBigEndian = FALSE);
};

/* ------------------------------
END
------------------------------ */
