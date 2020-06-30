#include "emoji.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QTextDocument>
#include <string>
#include <codecvt>
#include <locale>
#include <iostream>
#include "utility.h"
std::string gb2312_to_utf8(std::string const &strGb2312)
{
	std::vector<wchar_t> buff(strGb2312.size());
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	wchar_t* pwszNext = nullptr;
	const char* pszNext = nullptr;
	mbstate_t state = {};
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).in(state,
			strGb2312.data(), strGb2312.data() + strGb2312.size(), pszNext,
			buff.data(), buff.data() + buff.size(), pwszNext);
	if (std::codecvt_base::ok == res)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
		return cutf8.to_bytes(std::wstring(buff.data(), pwszNext));
	}
	return "";
}
std::string utf8_to_gb2312(std::string const &strUtf8)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
	std::wstring wTemp = cutf8.from_bytes(strUtf8);
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	const wchar_t* pwszNext = nullptr;
	char* pszNext = nullptr;
	mbstate_t state = {};
	std::vector<char> buff(wTemp.size() * 2);
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).out(state,
			wTemp.data(), wTemp.data() + wTemp.size(), pwszNext,
			buff.data(), buff.data() + buff.size(), pszNext);
	if (std::codecvt_base::ok == res)
	{
		return std::string(buff.data(), pszNext);
	}
	return "";
}

#if 1
#if _MSC_VER >= 1900
std::u32string to_utf32(std::string utf8_string) {
	std::wstring_convert<std::codecvt_utf8<unsigned int>, unsigned int> convert;
	auto p = reinterpret_cast<const char*>(utf8_string.data());
	auto str = convert.from_bytes(p, p + utf8_string.size());
	std::u32string str32(str.begin(), str.end());
	return str32;
}
#else
std::u32string to_utf32(std::string str) {
	return std::wstring_convert< std::codecvt_utf8<unsigned int>, unsigned int >{}.from_bytes(str);
}
#endif

#endif

bool IsEmoji(int value, int &count)
{
	//0x200d -- 连接符  0xd83c----好像是颜色分割符 或者是旗帜?  0xfe0f ---好像是表情结束符  0xfe0f0x20e3--特殊符号的表情
	if ((value >= 0xd800 && value <= 0xdbff))
	{
		count = 2;
		return true;
	}
	else if ((0x2100 <= value && value <= 0x27ff && value != 0x263b)
		|| (0x2b05 <= value && value <= 0x2b07)
		|| (0x2934 <= value && value <= 0x2935)
		|| (0x3297 <= value && value <= 0x3299)
		|| value == 0xa9 || value == 0xae || value == 0x303d || value == 0x3030
		|| value == 0x2b55 || value == 0x2b1c || value == 0x2b1b || value == 0x2b50
		|| value == 0x231a)
	{
		count = 1;
		return true;
	}
	return false;
}

std::string format(const char* mat, const char* data) {
	char szData[1024] = { 0 };
	sprintf_s(szData, mat, data);
	return std::string(&szData[0]);
}


Emoji::Emoji(QWidget* parent) :
	QWidget(parent) {
	setGeometry(300, 300, 500, 500);
	pBtn = new QPushButton("click", this);
	pBtn->setFixedSize(200,50);
	pBtn->setFont(QFont("EmojiOne Color"));
	
	pEmojiText = new QTextEdit(this);
	pEmojiText->setFontFamily("Segoe UI Emoji");
	pEmojiText->setFixedSize(300, 250);

	connect(pEmojiText, &QTextEdit::textChanged, this, &Emoji::OnTextChanged);
	QString strStyleLinear = QString("QPushButton{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:14px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #FF1270,stop:1 #FD583F);border-radius:10px;}\
									QPushButton::disabled{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:14px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgba(255,18,112,0.5),stop:1 rgba(253,88,63,0.5));border-radius:10px;}");
	

	pText = new QTextEdit(this);
	std::string str1 = "😃";
	qDebug() << "str1:" << str1.data();
	pText->setText("😃");
	std::u32string emo = to_utf32(str1);
	
	QString str = pText->toPlainText();
	std::wstring str2 = str.toStdWString();
	qDebug() << "str:" << str<<",str2:"<< QString::fromStdWString(str2);
	QVBoxLayout* vBox = new QVBoxLayout;
	vBox->setContentsMargins(0, 0, 0, 0);
	vBox->setSpacing(0);
	vBox->addWidget(pBtn);
	vBox->addWidget(pEmojiText);
	vBox->addWidget(pText);
	vBox->addStretch();
	setLayout(vBox);
	auto SlotClicked = [&] {
		QString strEmoji = pEmojiText->toPlainText();
		std::string strUtf8 = strEmoji.toStdString();
		std::string strChin = common_cz::UTF8_GBK(strUtf8, CP_ACP);
		std::wstring str16 = common_cz::MultiToWideStr(strChin, CP_ACP);
		std::u32string u32Str = to_utf32(strUtf8);
		const char32_t* data = u32Str.data();
		qDebug() << "u32Str:" << *data;
		pText->setText(strEmoji);

		QTextDocument *doc = pText->document();
		doc->adjustSize();  //这一步不能少
	};
	connect(pBtn, &QPushButton::clicked, SlotClicked);
}

Emoji::~Emoji() {

}

void Emoji::OnBtnClicked() {
	QString strText = pEmojiText->toPlainText();
	qDebug() << "strText:" << strText;
}

void Emoji::OnTextChanged() {
	QString text = pEmojiText->toPlainText();
	std::string content = text.toStdString();
	qDebug() << "strText:" << text;
}