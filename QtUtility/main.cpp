#include "music.h"
#include <QtWidgets/QApplication>
#include <QDir>
#include "Font.h"
#include "WinHttpWidget.h"
#include "TreeWidget.h"
#include "Equipment/QxEquipment.h"
#include "Pixmap.h"
#include "Animation.h"
#include "FileDialog.h"
#include "Helper/QtHelper.hpp"
#include "PromoteTest.h"
#include "ExcelOperate.h"
#include "Rotate.h"
#include "PngList.h"
#include <QMovie>
#include "OpacityWidget.h"
#include "ImageHandle.h"

#include <QFontDatabase>
#include <QDebug>
#include <Shlwapi.h>
#include "BannerWidget.h"
#include "imageprocess.h"
#include "AnimationResize.h"
#include "HDTrumpet.h"
#include "HdCharge.h"
#include "WillStarInfo.h"
#include "common_msg_widget.h"
#include "rounded_widget.h"
#include "time_set.h"
#include "user_card.h"
#include "BaseMoveDlg.h"
#include "live_time_set.h"
#include "LiveTimeView.h"
#include "gift_flowlight_manager.h"
#include "official_tip_widget.h"
#include <QProgressBar>
#include <QTextEdit>
#include <iostream>
#include <map>
#include <time.h>
#include "zip/unzip.h"
#include "Circle.h"
#include "StyleSheetWidget.h"
#include "QtApp.h"
#include "emoji.h"
#include "imwidget.h"
//#include<QtPlugin>
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
//Q_IMPORT_PLUGIN(QICOPlugin)

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK,__FILE__,__LINE__)
#else 
#define DEBUG_CLIENTBLOCK
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#define new DEBUG_CLIENTBLOCK
#endif

void TestRoundedWidget();
void TestCommonMsgWidget();
void TestTimeSet();
void TestUserCard();
void TestMoveDlg();
void TestLiveSet();
void TestView();
void CreatePixmap();
void TestFlowLight();
void TestCss();
void TestOfficialTip();
void TestZip();
void TestFuncPtr();
struct T {
	bool isHighFrequency;
	int orderBig;
	int index;
	T() {
		isHighFrequency = false;
		orderBig = 0;
		index = 0;
	}
	bool operator <(const T & other)const {
		return this->orderBig <= other.orderBig;
	}
};

long find_maximum(long* array, size_t size) {
	long max = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] > max)
			max = array[i];
	}
	return max;
}
int _stdcall test_function(int);
void TestDateTime();

int main(int argc, char *argv[])
{
	QtUtilityApp a(argc, argv);
	a.setQuitOnLastWindowClosed(true);
	QDir::setCurrent(QApplication::instance()->applicationDirPath());
	
	
	/*Emoji* emoji = new Emoji;
	emoji->show();*/
	IMWidget* widget = new IMWidget;
	widget->show();

	return a.exec();
}

void TestDateTime() {
	long long startTime = 1588925074876/1000;
	long long endTime = 1588925094876/1000;

	time_t create_time(startTime);
	QDateTime date;
	date = QDateTime::fromTime_t(create_time);
	QString strDate = date.toString("yyyy:MM:dd:hh:mm:ss");

	QDateTime time = QDateTime::currentDateTime();
	QString strTime = time.toString("yyyy:MM:dd:hh:mm:ss");
	QDateTime time1 = QDateTime::fromTime_t(startTime);
	QString strTime1 = time1.toString("yyyy:MM:dd:hh:mm:ss");
	QDateTime time2 = QDateTime::fromTime_t(endTime);
	QString strTime2 = time2.toString("yyyy:MM:dd:hh:mm:ss");
	qint64 secsTo2 = time.secsTo(time1);
	qint64 secsTo = time1.secsTo(time2);
	
}

void TestZip() {
	QString strFileZip = QString("D:/GitHub/hcz362329-QtUtility/Win32/Debug/angelcrown1000.zip");
	WCHAR szFile[MAX_PATH] = { 0 };
	strFileZip.toWCharArray(szFile);
	HZIP hTarget = OpenZip(szFile, "");
	if (hTarget != 0) {
		ZIPENTRY* entry;
		ZRESULT result = GetZipItem(hTarget, 0, entry);
		if (result == 0) {
			result = UnzipItem(hTarget, 0, entry->name);
		}
		CloseZip(hTarget);
	}
}

void TestFuncPtr() {
	long(*pFunc)(long* arrays, size_t) { find_maximum };
	auto pFunc2{ find_maximum };
	auto pFunc3{ find_maximum };
	std::function<long(long*, size_t)> funcLong;

	long arrays_long[10] = { 9,3,12,8,673,9,2,1,5,9 };
	long max_value = pFunc(arrays_long, _countof(arrays_long));
	long max_value2 = pFunc2(arrays_long, _countof(arrays_long));
	long max_value3 = pFunc3(arrays_long, _countof(arrays_long));
	funcLong = pFunc;
	int max_value4 = funcLong(arrays_long, _countof(arrays_long));
	qDebug() << "max_value:" << max_value;
}
void TestOfficialTip() {
	OfficialTipWidget* widget = new OfficialTipWidget;
	widget->setGeometry(300, 300, 212,120);
	widget->SetTipType(OfficialTipWidget::TYPE_CLOSE);
	widget->show();

}
void TestFlowLight() {
	Mgr::GiftFlowLight* light = new Mgr::GiftFlowLight;
	light->show();
}
void TestCss()
{
	QWidget* pWidget = new QWidget;
	pWidget->setGeometry(500, 500, 300, 300);
	QPushButton* pBtn = new QPushButton(pWidget);
	pBtn->setGeometry(0, 10, 300, 40);
	QString strStyle = QString("QProgressBar{color:rgba(253,88,63,1);}");
	QProgressBar* progress = new QProgressBar(pWidget);
	progress->setGeometry(0, 100, 300, 40);
	progress->setRange(0, 100);
	static int value = 0;
	QTextEdit* pText = new QTextEdit(pWidget);
	pText->setGeometry(0, 150, 300, 150);
	QObject::connect(pBtn, &QPushButton::clicked, [&]() {
		progress->setStyleSheet(pText->toPlainText());
		if (value > 100) value = 0;
		value += 5;
		progress->setValue(value);

	});
	pWidget->show();
}
void CreatePixmap()
{
	QtHelper::GetPixmap1(60,22);
	QtHelper::GetPixmap2(320, 150);
}

void TestView()
{
	QWidget* pWidget = new QWidget;
	pWidget->setStyleSheet("background:rgb(35,36,41);");
	pWidget->setGeometry(300, 300, 600, 800);
	View* view1 = new View(pWidget);
	view1->setGeometry(40, 100, 60, 67);
	QVector<int> vecHour1;
	vecHour1 << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21 << 22 << 23;
	view1->updateAll(vecHour1);
	view1->SetMaxStep(vecHour1.size() - 3);
	

	View* view = new View(pWidget);
	view->setGeometry(100,100,60,66);
	QVector<int> vecHour;
	vecHour << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21 << 22 << 23 << 24 << 25 << 26 << 27 << 28 << 29 << 30 << 31 << 32 << 33 << 34 << 35 << 36 << 37 << 38 << 39 << 40<< 41 << 42 << 43 << 44 << 45 << 46 << 47 << 48 << 49 << 50<< 51 << 52 << 53 << 54 << 55 << 56 << 57 << 58 << 59 ;
	view->updateAll(vecHour);
	view->SetMaxStep(vecHour.size()-3);
	QLabel* pLabel = new QLabel(pWidget);
	pLabel->setGeometry(200, 200, 100, 20);
	pLabel->setStyleSheet("color:white");
	QLabel* pLabel2 = new QLabel(pWidget);
	pLabel2->setGeometry(200, 250, 100, 20);
	pLabel2->setStyleSheet("color:white");

	pWidget->show();
	

	auto slot_view1 = [=](const int & value) {
		pLabel->setText(QString::number(value));
	};
	auto slot_view2 = [=](const int & value) {
		pLabel2->setText(QString::number(value));
	};
	QObject::connect(view1,&View::sigSelect, slot_view1);
	QObject::connect(view, &View::sigSelect, slot_view2);
}

void TestLiveSet()
{
	LiveTimeSet* set = new LiveTimeSet;
	//set->SetRoundedColor(533, 346, 7, 35, 36, 41);
	set->setFixedSize(533, 346);
	set->AddLiveStartEndTime("00:00","00:00");
	set->AddLiveStartEndTime("00:00", "00:00");
	set->AddLiveStartEndTime("00:00", "00:00");
	set->show();
}

void TestMoveDlg()
{
	BaseMoveDlg* pMove = new BaseMoveDlg;
	pMove->setStyleSheet("background:black;");
	pMove->setGeometry(300, 200, 600, 600);
	
	pMove->show();
}

void TestUserCard()
{
	UserCard* pUserCard = new UserCard;
	pUserCard->SetRoundedColor(365, 270, 4, 35, 36, 41);
	pUserCard->setFixedSize(365, 270);
	pUserCard->show();

	/*RoundedWidget* pRound = new RoundedWidget();
	pRound->setWindowFlags(Qt::FramelessWindowHint);
	pRound->setFixedSize(281,208);
	pRound->SetRoundedColor(281, 208, 4, 35, 36, 41);
	pRound->show();*/
}

void TestTimeSet()
{
	TimeSet* pSet = new TimeSet;
	pSet->show();
}

void TestCommonMsgWidget()
{
	//qDebug()<<"exec:"<<CommonMsgWidget::information(nullptr, QStringLiteral("每个月参加活动可有机会获得全服召唤权益！每个月参加活动可有机会获得全服召唤权益！每个月参加活动可有机会获得全服召唤权益！每个月参加活动可有机会获得全服召唤权益！"));
}

void TestCRTDebug()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
	QtHelper::GetNormalPixmap();
}

void TestRoundedWidget()
{
	RoundedWidget* pRound = new RoundedWidget;
	//pRound->SetPixmap(":/res/Resources/images/lucky_user_bg.png");
	pRound->SetRoundedColor(533, 346, 7, 35, 36, 41);
	pRound->move(600, 100);
	pRound->show();
}

int _stdcall test_function(int value) {
	qDebug() << "value:"<< value;
	return 1;
}

void loadFont()
{
	if (1)
	{
		QDir dir("./Font");
		QStringList lstSuffix;
		lstSuffix.append("*.ttf");
		lstSuffix.append("*.TTF");

		const QFileInfoList& lstFonts = dir.entryInfoList(lstSuffix, QDir::Files);
		foreach(const QFileInfo& fileInfo, lstFonts)
		{

			QString strfilePath = fileInfo.absoluteFilePath();
			QString strFileName = fileInfo.fileName();
			QString strWindowsFile = QString("C:\\Windows\\fonts\\") + strFileName;

			bool bCopy = QFile::copy(strfilePath, strWindowsFile);

			int id = QFontDatabase::addApplicationFont(strWindowsFile);
			QStringList& strlst = QFontDatabase::applicationFontFamilies(id);
			if (strlst.size() > 0)
			{
				//LOG_INFO("font-family: " << strlst[0].toStdWString());
			}

			int nLoadFont = AddFontResourceExA(strWindowsFile.toLocal8Bit(), FR_PRIVATE, 0);

			HKEY   phkResult;
			DWORD  RegResult;
			LONG   Rlt = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts",
				0, L"REG_SZ",
				0,
				KEY_WRITE,
				0,
				&phkResult,
				&RegResult
			);
			if (Rlt != ERROR_SUCCESS)
			{
				int m = 5;
				qDebug() << m;
			}
			QString strFontName;
			QFile file(strWindowsFile);
			QString fileName = file.fileName();
			if (fileName.contains("HanYiXiaoLvShuJian"))
			{
				strFontName = QString::fromWCharArray(L"汉仪小隶书简");
			}
			else if (fileName.contains("JingDianXiLvShuJian"))
			{
				strFontName = QString::fromWCharArray(L"经典细隶书简");
			}
			else
			{
				continue;
			}
			QFileInfo fileinfo(strWindowsFile);
			QString strFontName1 = fileinfo.fileName();
			int length_ = strFontName1.toLocal8Bit().size();
			RegSetValueExA(phkResult, strFontName.toLocal8Bit(), 0, REG_SZ, (const BYTE*)(strFontName1.toLocal8Bit().data()), length_);
			RegCloseKey(phkResult);
			PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
		}
	}
}

void test()
{
	/*music w;
	w.show();*/

	/*WinHttpWidget h;
	h.show();*/

	/*TreeWidget t;
	t.show();*/


	/*CAnimation ani ;
	ani.SetSeconds(2);
	ani.show();
	*/
	//FileSaveAS *file=new FileSaveAS;
	//QVariantList list;
	//QVariant v;
	//v.setValue(QString("https://pic2.7fgame.com/qxhdmaster/20190712/d91ea479e70c4ef591ee864c4fc54a73.jpg"));
	//QVariant v2;
	//v2.setValue(QString("Invite"));
	//list.push_back(v);
	//list.push_back(v2);
	//file->SetWebUrl(list);
	//
	////file->SetWebUrl("http://qxzlhd.7fgame.com/platform/taskhd/images/bg-Wegame.png");
	//file->show();
	/*
	QPixmap pixmap = QtHelper::GetPixmapByColor(QColor(Qt::red),10,10);

	QCursor cursor(pixmap);
	QApplication::setOverrideCursor(cursor);


	eRankStateNormal						= 0,//普通
	eRankStateLargePromotion				= 100,//大段晋级中
	eRankStateLarge1Defeat					= 101,//大段1败
	eRankStateLarge1Win						= 110,//大段晋级1胜
	eRankStateLarge1Defeat1Win				= 111,//大段1胜1败
	eRankStateSmallPromotion				= 200,//小段晋级中
	eRankStateAvoidRelegation				= 300,//保级赛中
	*/

	PromoteTest p;
	p.show();
	/*ExcelOperate e;
	e.show();*/

	/*Pixmap pixmap;
	pixmap.show();*/
	/*Rotate rotate;
	rotate.show();*/

	/*CAnimation ani ;
	ani.SetSeconds(1.24);
	ani.show();*/
	/*PngList * pnglist = new PngList(nullptr,1.24);
	pnglist->setGeometry(0,0,967,679);
	pnglist->show();*/
	/*QLabel* pLabel = new QLabel(nullptr);
	pLabel->setGeometry(0,0,1000,1000);
	QMovie *movie = new QMovie("./Animation/11.swf");
	pLabel->setMovie(movie);
	pLabel->show();*/

	/*QPixmap pixmap;
	bool bLoad = pixmap.load("./Animation/light3.png");
	OpacityWidget* flash1 = new OpacityWidget(nullptr,"./Animation/light3.png",0.16,0.2);
	flash1->setGeometry(600,400,pixmap.width(),pixmap.height());
	flash1->show();*/
	/*OpacityWidget* flash2 = new OpacityWidget(this,"./Animation/light3.png",0.16,1);
	QPixmap pixmap2 = pixmap.scaled(QSize(pixmap.width()*0.8,pixmap.height()*0.8),Qt::KeepAspectRatio,Qt::SmoothTransformation);
	flash2->setGeometry(467,317,pixmap2.width(),pixmap2.height());*/

	/*图片处理*/

	/*
	int index = QFontDatabase::addApplicationFont("./font/hyxlsf.ttf");

	if (::PathFileExistsA("./font/1.ttf"))
	{
	qDebug()<<"file exist";
	}
	if(index != -1) {
	QStringList fontList(QFontDatabase::applicationFontFamilies(index));

	/* font -- LiHei Pro */

	//加载字体

	//加载字体文件到程序中

	/*loadFont();

	QImage image = QtHelper::GetGrayPixmap("./Images/btn_baocun.png");
	image.save("./Images/btn_baocun2.png");
	ImageHandle* imagehandle = new ImageHandle;
	imagehandle->setGeometry(100,100,1500,1000);
	imagehandle->show();
	QtHelper::GetTrumpetPixmap2();*/
	/*QtHelper::CreatePurchaseClose();*/
	/*QtHelper::CreatePurchaseBg(1012,714);
	QtHelper::CreatePurchaseClose();
	QtHelper::GetPixmapHalfOpacity();*/
	/*QxEquipment equipment;
	equipment.show();*/
	/*BannerWidget b;
	b.show();*/

	/*CImageProcess c;
	c.show();*/

	/*AnimationResize a_;
	a_.show();*/

	/*HDTrumpet h;
	h.show();*/
	/*HdCharge h ;
	h.show();

	QPixmap pix222 = QtHelper::GetPixmapBySmallBg2("1111.png",60,60,360,210);
	pix222.save("222.png");*/
	/*
	QWidget* background = new QWidget();
	background->setWindowFlags(Qt::FramelessWindowHint);
	background->setGeometry(400,400,1280,768);
	background->setObjectName("ControllerSelector_bg");
	background->setStyleSheet("QWidget#ControllerSelector_bg{border-width:60px;border-image:url(./halfopacity.png) 60px 60px 60px 60px stretch stretch;}");
	background->show();
	*/
	/*QtHelper::CreatePurchaseBuy();*/
	/*WillStarInfo *ws = new WillStarInfo;;
	ws->show();
	QtHelper::createtext1();
	QtHelper::createtext2();
	QtHelper::createtext3();
	QtHelper::createtext4();
	QtHelper::createtext5();
	QtHelper::createtext6();
	QtHelper::createtext7();
	QtHelper::createtext8();
	QtHelper::createtext9();*/
}
