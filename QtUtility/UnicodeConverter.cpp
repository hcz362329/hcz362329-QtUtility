#include "UnicodeConverter.h"

/* -------------------------------------------------------------
����ת��
------------------------------------------------------------- */

// ת��UCS4���뵽UTF8����
INT CUnicodeConverter::UCS4_To_UTF8(DWORD dwUCS4, BYTE* pbUTF8)
{
	const BYTE	abPrefix[] = { 0, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
	const DWORD adwCodeUp[] = {
		0x80,			// U+00000000 �� U+0000007F
		0x800,			// U+00000080 �� U+000007FF
		0x10000,		// U+00000800 �� U+0000FFFF
		0x200000,		// U+00010000 �� U+001FFFFF
		0x4000000,		// U+00200000 �� U+03FFFFFF
		0x80000000		// U+04000000 �� U+7FFFFFFF
	};

	INT	i, iLen;

	// ����UCS4���뷶Χȷ����Ӧ��UTF-8�����ֽ���
	iLen = sizeof(adwCodeUp) / sizeof(DWORD);
	for (i = 0; i < iLen; i++)
	{
		if (dwUCS4 < adwCodeUp[i])
		{
			break;
		}
	}

	if (i == iLen)return 0;	// ��Ч��UCS4����

	iLen = i + 1;	// UTF-8�����ֽ���
	if (pbUTF8 != NULL)
	{	// ת��ΪUTF-8����
		for (; i > 0; i--)
		{
			pbUTF8[i] = static_cast<BYTE>((dwUCS4 & 0x3F) | 0x80);
			dwUCS4 >>= 6;
		}

		pbUTF8[0] = static_cast<BYTE>(dwUCS4 | abPrefix[iLen - 1]);
	}

	return iLen;
}

// ת��UTF8���뵽UCS4����
INT CUnicodeConverter::UTF8_To_UCS4(const BYTE* pbUTF8, DWORD& dwUCS4)
{
	INT		i, iLen;
	BYTE	b;

	if (pbUTF8 == NULL)
	{	// ��������
		return 0;
	}

	b = *pbUTF8++;
	if (b < 0x80)
	{
		dwUCS4 = b;
		return 1;
	}

	if (b < 0xC0 || b > 0xFD)
	{	// �Ƿ�UTF8
		return 0;
	}

	if (b < 0xE0)
	{
		dwUCS4 = b & 0x1F;
		iLen = 2;
	}
	else if (b < 0xF0)
	{
		dwUCS4 = b & 0x0F;
		iLen = 3;
	}
	else if (b < 0xF8)
	{
		dwUCS4 = b & 7;
		iLen = 4;
	}
	else if (b < 0xFC)
	{
		dwUCS4 = b & 3;
		iLen = 5;
	}
	else
	{
		dwUCS4 = b & 1;
		iLen = 6;
	}

	for (i = 1; i < iLen; i++)
	{
		b = *pbUTF8++;
		if (b < 0x80 || b > 0xBF)
		{	// �Ƿ�UTF8
			break;
		}

		dwUCS4 = (dwUCS4 << 6) + (b & 0x3F);
	}

	if (i < iLen)
	{	// �Ƿ�UTF8
		return 0;
	}
	else
	{
		return iLen;
	}
}

// ת��UCS4���뵽UCS2����
INT CUnicodeConverter::UCS4_To_UTF16(DWORD dwUCS4, WORD* pwUTF16)
{
	if (dwUCS4 <= 0xFFFF)
	{
		if (pwUTF16 != NULL)
		{
			*pwUTF16 = static_cast<WORD>(dwUCS4);
		}

		return 1;
	}
	else if (dwUCS4 <= 0xEFFFF)
	{
		if (pwUTF16 != NULL)
		{
			pwUTF16[0] = static_cast<WORD>(0xD800 + (dwUCS4 >> 10) - 0x40);	// ��10λ
			pwUTF16[1] = static_cast<WORD>(0xDC00 + (dwUCS4 & 0x03FF));		// ��10λ
		}

		return 2;
	}
	else
	{
		return 0;
	}
}

// ת��UCS2���뵽UCS4����
INT CUnicodeConverter::UTF16_To_UCS4(const WORD* pwUTF16, DWORD& dwUCS4)
{
	WORD	w1, w2;

	if (pwUTF16 == NULL)
	{	// ��������
		return 0;
	}

	w1 = pwUTF16[0];
	if (w1 >= 0xD800 && w1 <= 0xDFFF)
	{	// �������������Surrogate Area��
		if (w1 < 0xDC00)
		{
			w2 = pwUTF16[1];
			if (w2 >= 0xDC00 && w2 <= 0xDFFF)
			{
				dwUCS4 = (w2 & 0x03FF) + (((w1 & 0x03FF) + 0x40) << 10);
				return 2;
			}
		}

		return 0;	// �Ƿ�UTF16����	
	}
	else
	{
		dwUCS4 = w1;
		return 1;
	}
}

// ת��UTF8�ַ�����UTF16�ַ���
INT CUnicodeConverter::UTF8Str_To_UTF16Str(const BYTE* pbszUTF8Str, WORD* pwszUTF16Str)
{
	INT		iNum, iLen;
	DWORD	dwUCS4;

	if (pbszUTF8Str == NULL)
	{	// ��������
		return 0;
	}

	iNum = 0;	// ͳ����Ч�ַ�����
	while (*pbszUTF8Str)
	{	// UTF8����ת��ΪUCS4����
		iLen = UTF8_To_UCS4(pbszUTF8Str, dwUCS4);
		if (iLen == 0)
		{	// �Ƿ���UTF8����
			return 0;
		}

		pbszUTF8Str += iLen;

		// UCS4����ת��ΪUTF16����
		iLen = UCS4_To_UTF16(dwUCS4, pwszUTF16Str);
		if (iLen == 0)
		{
			return 0;
		}

		if (pwszUTF16Str != NULL)
		{
			pwszUTF16Str += iLen;
		}

		iNum += iLen;
	}

	if (pwszUTF16Str != NULL)
	{
		*pwszUTF16Str = 0;	// д���ַ����������
	}

	return iNum;
}

// ת��UTF16�ַ�����UTF8�ַ���
INT CUnicodeConverter::UTF16Str_To_UTF8Str(const WORD* pwszUTF16Str, BYTE* pbszUTF8Str)
{
	INT		iNum, iLen;
	DWORD	dwUCS4;

	if (pwszUTF16Str == NULL)
	{	// ��������
		return 0;
	}

	iNum = 0;
	while (*pwszUTF16Str)
	{	// UTF16����ת��ΪUCS4����
		iLen = UTF16_To_UCS4(pwszUTF16Str, dwUCS4);
		if (iLen == 0)
		{	// �Ƿ���UTF16����
			return 0;
		}

		pwszUTF16Str += iLen;

		// UCS4����ת��ΪUTF8����
		iLen = UCS4_To_UTF8(dwUCS4, pbszUTF8Str);
		if (iLen == 0)
		{
			return 0;
		}

		if (pbszUTF8Str != NULL)
		{
			pbszUTF8Str += iLen;
		}

		iNum += iLen;
	}

	if (pbszUTF8Str != NULL)
	{
		*pbszUTF8Str = 0;	// д���ַ����������
	}

	return iNum;
}

/* -------------------------------------------------------------
C�ļ�д�����
------------------------------------------------------------- */

// ���ļ������UTF8����
UINT CUnicodeConverter::Print_UTF8_By_UCS4(FILE* out, DWORD dwUCS4)
{
	INT		iLen;
	BYTE	abUTF8[8];

	if (out == NULL)
	{
		return 0;
	}

	iLen = UCS4_To_UTF8(dwUCS4, abUTF8);
	if (iLen == 0)return 0;

	fwrite(abUTF8, 1, iLen, out);

	return iLen;
}

// ���ļ������UTF16����
UINT CUnicodeConverter::Print_UTF16_By_UCS4(FILE* out, DWORD dwUCS4, BOOL isBigEndian)
{
	INT		i, iLen;
	WORD	wCode, awUTF16[2];

	if (out == NULL)
	{
		return 0;
	}

	iLen = UCS4_To_UTF16(dwUCS4, awUTF16);
	if (iLen == 0)return 0;

	for (i = 0; i < iLen; i++)
	{
		wCode = awUTF16[i];
		if (isBigEndian)
		{
			fputc(wCode >> 8, out);	// �����λ
			fputc(wCode & 0xFF, out);	// �����λ
		}
		else
		{
			fputc(wCode & 0xFF, out);	// �����λ
			fputc(wCode >> 8, out);	// �����λ
		}
	}

	return (iLen << 1);
}

// ��UTF16�ַ�����UTF8����������ļ���
UINT CUnicodeConverter::Print_UTF8Str_By_UTF16Str(FILE* out, const WORD* pwszUTF16Str)
{
	INT		iCount, iLen;
	DWORD	dwUCS4;

	if ((out == NULL) || (pwszUTF16Str == NULL))
	{
		return 0;
	}

	iCount = 0;
	while (*pwszUTF16Str)
	{	// ��UTF16����ת����UCS4����
		iLen = UTF16_To_UCS4(pwszUTF16Str, dwUCS4);
		if (iLen == 0)
		{
			break;
		}

		pwszUTF16Str += iLen;

		// ���ļ������UTF8����
		iCount += Print_UTF8_By_UCS4(out, dwUCS4);
	}

	return iCount;	// ������ֽ���
}

// ��UTF8�ַ�����UTF16����������ļ���
UINT CUnicodeConverter::Print_UTF16Str_By_UTF8Str(FILE* out, const BYTE* pbszUTF8Str, BOOL isBigEndian)
{
	INT		iCount, iLen;
	DWORD	dwUCS4;

	if ((out == NULL) || (pbszUTF8Str == NULL))
	{
		return 0;
	}

	iCount = 0;
	while (*pbszUTF8Str)
	{	// ��UTF16����ת����UCS4����
		iLen = UTF8_To_UCS4(pbszUTF8Str, dwUCS4);
		if (iLen == 0)
		{
			break;
		}

		pbszUTF8Str += iLen;

		// ���ļ������UTF8����
		iCount += Print_UTF16_By_UCS4(out, dwUCS4, isBigEndian);
	}

	return iCount;	// ������ֽ���
}

// ���ļ������UTF8�ֽ�����
UINT CUnicodeConverter::Print_UTF8_BOM(FILE* out)
{
	if (out == NULL)
	{
		return 0;
	}

	fputc(0xEF, out);
	fputc(0xBB, out);
	fputc(0xBF, out);

	return 3;
}

// ���ļ������UTF16�ֽ�����
UINT CUnicodeConverter::Print_UTF16_BOM(FILE* out, BOOL isBigEndian)
{
	if (out == NULL)
	{
		return 0;
	}

	if (isBigEndian)
	{
		fputc(0xFE, out);
		fputc(0xFF, out);
	}
	else
	{
		fputc(0xFF, out);
		fputc(0xFE, out);
	}

	return 2;
}

/* -------------------------------------------------------------
C++���������
------------------------------------------------------------- */

// ���������UTF8����
UINT CUnicodeConverter::Print_UTF8_By_UCS4(ostream& os, DWORD dwUCS4)
{
	INT		iLen;
	BYTE	abUTF8[8];

	if (!os)return 0;

	iLen = UCS4_To_UTF8(dwUCS4, abUTF8);
	if (iLen == 0)return 0;

	os.write(reinterpret_cast<CHAR*>(abUTF8), iLen);

	return iLen;
}

// ���������UTF16����
UINT CUnicodeConverter::Print_UTF16_By_UCS4(ostream& os, DWORD dwUCS4, BOOL isBigEndian)
{
	INT		i, iLen;
	WORD	wCode, awUTF16[2];

	if (!os)return 0;

	iLen = UCS4_To_UTF16(dwUCS4, awUTF16);
	if (iLen == 0)return 0;

	for (i = 0; i < iLen; i++)
	{
		wCode = awUTF16[i];
		if (isBigEndian)
		{
			os.put(wCode >> 8);		// �����λ
			os.put(wCode & 0xFF);		// �����λ
		}
		else
		{
			os.put(wCode & 0xFF);		// �����λ
			os.put(wCode >> 8);		// �����λ
		}
	}

	return (iLen << 1);
}

// ��UTF16�ַ�����UTF8�������������
UINT CUnicodeConverter::Print_UTF8Str_By_UTF16Str(ostream& os, const WORD* pwszUTF16Str)
{
	INT		iCount, iLen;
	DWORD	dwUCS4;

	if (!os || (pwszUTF16Str == NULL))return 0;

	iCount = 0;
	while (*pwszUTF16Str)
	{	// ��UTF16����ת����UCS4����
		iLen = UTF16_To_UCS4(pwszUTF16Str, dwUCS4);
		if (iLen == 0)
		{
			break;
		}

		pwszUTF16Str += iLen;

		// ���������UTF8����
		iCount += Print_UTF8_By_UCS4(os, dwUCS4);
	}

	return iCount;	// ������ֽ���
}

// ��UTF8�ַ�����UTF16�������������
UINT CUnicodeConverter::Print_UTF16Str_By_UTF8Str(ostream& os, const BYTE* pbszUTF8Str, BOOL isBigEndian)
{
	INT		iCount, iLen;
	DWORD	dwUCS4;

	if (!os || (pbszUTF8Str == NULL))return 0;

	iCount = 0;
	while (*pbszUTF8Str)
	{	// ��UTF16����ת����UCS4����
		iLen = UTF8_To_UCS4(pbszUTF8Str, dwUCS4);
		if (iLen == 0)
		{
			break;
		}

		pbszUTF8Str += iLen;

		// ���������UTF8����
		iCount += Print_UTF16_By_UCS4(os, dwUCS4, isBigEndian);
	}

	return iCount;	// ������ֽ���
}

// ���������UTF8�ֽ�����
UINT CUnicodeConverter::Print_UTF8_BOM(ostream& os)
{
	if (!os)return 0;

	os.put(0xEF);
	os.put(0xBB);
	os.put(0xBF);

	return 3;
}

// ���������UTF16�ֽ�����
UINT CUnicodeConverter::Print_UTF16_BOM(ostream& os, BOOL isBigEndian)
{
	if (!os)return 0;

	if (isBigEndian)
	{
		os.put(0xFE);
		os.put(0xFF);
	}
	else
	{
		os.put(0xFF);
		os.put(0xFE);
	}

	return 2;
}

/* ------------------------------
END
------------------------------ */
