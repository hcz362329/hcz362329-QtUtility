#include "Font.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "QtFunction.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include "winhttp/utility.h"
#include <QTextStream>
#include "StringHelper.hpp"
#include <QFontDatabase>
#include <QtWidgets/QApplication>
Font::Font(QWidget* parent )
{
	resize(800,800);
	QPushButton * btn10=new QPushButton("Font",this);
	btn10->setGeometry(0,0,200,20);

	QLineEdit* line_1_1 = new QLineEdit(this);
	line_1_1->setPlaceholderText("text");
	line_1_1->setGeometry(210,0,410,40);
	line_1_1->setText("Holy crap");

	QTextEdit* line_1_2 = new QTextEdit(this);
	line_1_2->setPlaceholderText("style sheet");
	line_1_2->setGeometry(0,50,620,80);
	connect(btn10,&QPushButton::clicked,this,[=](){
		QString strText = line_1_2->toPlainText();
		if (!strText.isEmpty())
		{
			line_1_1->setStyleSheet(strText);
		}
	});

	QPushButton * btn20=new QPushButton("Read File",this);
	btn20->setGeometry(0,150,200,20);

	QLineEdit* line_2_1 = new QLineEdit(this);
	line_2_1->setPlaceholderText("input file name");
	line_2_1->setGeometry(210,150,410,40);
	line_2_1->setText("D:/QXHD_NEWPLAT/QX_HD/bin/debug/ui/resources/skin/0/css/lobby.css");
	QTextEdit* line_2_2 = new QTextEdit(this);
	line_2_2->setPlaceholderText("read style sheet from file");
	line_2_2->setGeometry(0,200,620,200);
	connect(btn20,&QPushButton::clicked,this,[=](){
		QString strText = line_2_1->text();
		if (!strText.isEmpty())
		{
			line_2_2->setText(QtFunction::GetStyleSheetFromFile(strText));
		}
	});
	/*
	QPushButton * btn3 = new QPushButton("File Js",this);
	btn3->setGeometry(0,400,100,20);
	QLineEdit* line3 = new QLineEdit(this);
	line3->setGeometry(100,400,200,20);
	line3->setText("{\"url_type\":1,\"mode\":5}");
	QTextEdit* text4 = new QTextEdit(this);
	text4->setGeometry(0,450,300,60);
	connect(btn3,&QPushButton::clicked,this,[=](){
		QString strText = line3->text();
		if (!strText.isEmpty())
		{
			int url_type=0;
			int mode = 6;
			QString strNodeInfo = strText;
			QJsonParseError json_error;
			QJsonDocument parse_doucment = QJsonDocument::fromJson(strNodeInfo.toLocal8Bit(), &json_error); 

			if(json_error.error == QJsonParseError::NoError) 
			{  
				if(parse_doucment.isObject())  
				{  
					QJsonObject obj = parse_doucment.object(); 
					if(obj.contains("url_type"))  
					{  
						QJsonValue urlroot_value = obj.take("url_type");
						if(urlroot_value.isDouble())
						{
							url_type = urlroot_value.toInt();
						}
					}
					if(obj.contains("mode"))  
					{  
						QJsonValue mode_value = obj.take("mode");
						if(mode_value.isDouble())
						{
							mode = mode_value.toInt();
						}
					}
				}
			}
			QString strUrlRoot = (url_type==0)?"\"http://hd.7fgame.com:4032\"":"\"http://10.10.0.20:4032\"";

			QString line1 = QString("var urlroot = ") + strUrlRoot;
			QString line2 = QString("var GameMode = ") + QString::number(mode);
			QString strText3 = line1 + QString("\n") + line2;
			int nError = 0;
			std::wstring root_path;
			bool bGet = common_cz::GetProcessFolderPath(&root_path);
			QString strPath = QString::fromStdWString(root_path)+QString("/common.js");
			
			QFile file(strPath);
			/*bool bOpen = file.open(QIODevice::ReadOnly);
			QTextStream io(&file);
			file.close();

			bOpen = file.open(QIODevice::Truncate);
			file.close();

			bool bOpen = file.open(QIODevice::WriteOnly);
			QTextStream io(&file);
			io<<strText3;
			file.close();

			QFile file2(strPath);
			bOpen = file2.open(QIODevice::ReadOnly);
			QString strRead =  file2.readAll();
			
			text4->setText(strRead);
		}
	});

	QPushButton * btn5 = new QPushButton("Msg Js",this);
	btn5->setGeometry(0,500,100,20);

	QLineEdit* line5 = new QLineEdit(this);
	line5->setGeometry(100,500,200,20);

	char szData[1024]={0};
	strncpy_s(szData,"{\"content\": \"尊敬的群雄逐鹿HD玩家：群雄逐鹿HD上线以来，广大玩家非常期待能推出更加注重竞技的对战模式，我们对此非常重视，竞技模式因运而生\",\"url\": \" \",\"url_content\": \"\"}",1024);

	int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szData, strlen(szData), NULL, 0); 
	wchar_t* wszString = new wchar_t[wcsLen + 1]; 
	::MultiByteToWideChar(CP_ACP, NULL, szData, strlen(szData), wszString, wcsLen);
	wszString[wcsLen] = '\0';


	std::string stData ;
	stData = FuncHelper::UnicodeToUtf8(wszString);

	QString strData =QString::fromLocal8Bit(stData.data());

	
	delete [] wszString;
	wszString = NULL;


	line5->setText(strData);
	QTextEdit* text5 = new QTextEdit(this);
	text5->setGeometry(0,550,300,60);
	connect(btn5,&QPushButton::clicked,this,[=](){
		QString strText = line5->text();

		QString strShow;
		QString strContent;
		QString strUrl;
		QString strUrlContent;
		if (!strText.isEmpty())
		{
			QString strNodeInfo = strText;
			QJsonParseError json_error;
			QJsonDocument parse_doucment = QJsonDocument::fromJson(strNodeInfo.toLocal8Bit(), &json_error); 

			if(json_error.error == QJsonParseError::NoError) 
			{  
				if(parse_doucment.isObject())  
				{  
					QJsonObject obj = parse_doucment.object(); 
					if(obj.contains("content"))  
					{  
						QJsonValue content_ = obj.take("content");
						if(content_.isString())
						{
							strContent = content_.toString();
						}
					}
					if(obj.contains("url"))  
					{  
						QJsonValue url_ = obj.take("url");
						if(url_.isString())
						{
							strUrl = url_.toString();
						}
					}

					if(obj.contains("url_content"))  
					{  
						QJsonValue url_content_ = obj.take("url_content");
						if(url_content_.isString())
						{
							strUrlContent = url_content_.toString();
						}
					}
				}
			}
			
			text5->append(strContent);
			text5->append(strUrl);
			text5->append(strUrlContent);
		}
	});
	*/
	/*
	QTextEdit

	setStyleSheet("border: none; background-color: transparent; color: #000; font-weight: bold;");
	//! 设置字体黑色描边
	QTextCharFormat format;
	format.setTextOutline(QPen(Qt::black, 0.2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	mergeCurrentCharFormat(format);
	setText(text);
	*/

	
	
	QPushButton* font_set = new QPushButton(QString::fromWCharArray(L"设置字体"),this);
	font_set->setGeometry(0,440,100,20);
	QLineEdit* font_input = new QLineEdit(this);
	font_input->setGeometry(120,440,200,20);
	connect(font_set,&QPushButton::clicked,this,[=]{
		QString strFont = font_input->text();
		QString strPath = QString("./font/%1").arg(strFont);
		int index = QFontDatabase::addApplicationFont(strPath);
		if(index != -1) {
			QStringList fontList(QFontDatabase::applicationFontFamilies(index));

			/* font -- LiHei Pro */
			if(fontList.count() > 0) {
				QFont font_zh(fontList.at(0));
				font_zh.setBold(false);
				qApp->setFont(font_zh);
				//a.setFont(font_zh);
			}
		}

	});
}

Font::~Font()
{

}

void Font::InitConnections()
{

}

void Font::InitStyleSheets()
{

}

void Font::LoadTranslator()
{

}

void Font::InitModules()
{

}

void Font::InitPixmap()
{

}
void Font::InitCtrls()
{

}

void Font::InitWindowFlags()
{

}

void Font::LoadStyleSheet(const QString & file_name)
{

}