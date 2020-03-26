#include "user_card.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
UserCard::UserCard(QWidget *parent)
	: RoundedWidget(parent)
	, pLabelHead(nullptr)
	, pLabelName(nullptr)
	, pLabelGender(nullptr)
	, pLabelYork(nullptr)
	, pLabelLevel(nullptr)
	, pFunsGroup(nullptr)
	, pLabelGroupId(nullptr)
	, pLabelUqid(nullptr)
	, pLabelSign(nullptr)
	, pFocusOnNum(nullptr)
	, pFocusOn(nullptr)
	, pFunsNum(nullptr)
	, pFuns(nullptr)
	, pGiftsNum(nullptr)
	, pGifts(nullptr)
	, pSendGiftsNum(nullptr)
	, pSendGifts(nullptr)
	, pSeprateLine(nullptr)
	, pOpenRoomTime(nullptr)
	, pOpenTime1(nullptr)
	, pOpenTime2(nullptr)
	, pOpenTime3(nullptr)
{
	resize(280,208);
	setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet("QLabel{background:rgba(255,255,255,0);color:white;}");
	pLabelHead			= new QLabel(this);
	pLabelHead->setFixedSize(58, 58);
	pLabelHead->setPixmap(ScaledPixmap(":/res/Resources/images/1.png", pLabelHead->size()));
	pLabelName			= new QLabel(QStringLiteral("主播昵称"),this);
	pLabelName->setStyleSheet("font-size:16px;font-family:PingFangSC-Medium,PingFang SC;font-weight:500;line-height:22px;");
	pLabelName->setFixedHeight(22);
	pLabelName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLabelGender		= new QLabel(this);
	pLabelGender->setFixedSize(21, 21);
	pLabelGender->setPixmap(ScaledPixmap(":/res/Resources/images/1.png",QSize(16, 16)));
	pLabelYork			= new QLabel(this);
	pLabelYork->setFixedSize(24, 24);
	pLabelYork->setPixmap(ScaledPixmap(":/res/Resources/images/1.png", QSize(18, 18)));
	pLabelLevel			= new QLabel("   12",this);
	pLabelLevel->setFixedSize(44, 18);
	pLabelLevel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	pLabelLevel->setStyleSheet("border-image:url(:/res/Resources/images/car.png);font-size:10px;font-family:PingFangSC-Semibold,PingFang SC;font-weight:600;color:rgb(255,255,255);");
	//pLabelLevel->setPixmap(ScaledPixmap(":/res/Resources/images/car.png", QSize(35, 14)));
	
	pFunsGroup			= new QLabel(QStringLiteral("    粉丝团"),this);
	pFunsGroup->setFixedSize(64, 18);
	pFunsGroup->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pFunsGroup->setStyleSheet("border-image:url(:/res/Resources/images/biz_live_fans_level_icon_1.png);font-size:11px;font-family:PingFangSC-Semibold,PingFang SC;font-weight:400;color:rgb(255,255,255);line-height:12px;");
	QString strStyleId = QString("font-size:14px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(153,153,153);line-height:20px;");
	pLabelGroupId		= new QLabel(QStringLiteral("工会ID:33231"), this);
	pLabelGroupId->setFixedHeight(20);
	pLabelGroupId->setStyleSheet(strStyleId);

	pLabelUqid			= new QLabel(QStringLiteral("趣ID:33231"), this);
	pLabelUqid->setFixedHeight(20);
	pLabelUqid->setStyleSheet(strStyleId);

	pLabelSign			= new QLabel(QStringLiteral("前半生我浪荡不羁，余生为你保驾护航前半生我浪荡不羁，余生为你保驾护航前半生我浪荡不羁，余生为你保驾护航前半生我浪荡不羁，余生为你保驾护航"), this);
	QString strStyleSign = QString("font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(153,153,153);line-height:22px;");
	pLabelSign->setStyleSheet(strStyleId);

	QString strNumStyle = QString("font-size:18px;font - family:PingFangSC - Regular, PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:25px;");
	QString strTextStyle = QString("font-size:14px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(153, 153, 153);line-height:20px;");
	pFocusOnNum			= new QLabel(QStringLiteral("9999万"),this);
	pFocusOnNum->setAlignment(Qt::AlignCenter);
	pFocusOn			= new QLabel(QStringLiteral("关注"), this);
	pFocusOn->setAlignment(Qt::AlignCenter);
	pFocusOnNum->setStyleSheet(strNumStyle);
	pFocusOn->setStyleSheet(strTextStyle);
	pFunsNum			= new QLabel(QStringLiteral("9999万"), this);
	pFuns				= new QLabel(QStringLiteral("粉丝"), this);
	pFunsNum->setAlignment(Qt::AlignCenter);
	pFuns->setAlignment(Qt::AlignCenter);
	pFunsNum->setStyleSheet(strNumStyle);
	pFuns->setStyleSheet(strTextStyle);
	pGiftsNum			= new QLabel(QStringLiteral("9999万"), this);
	pGifts				= new QLabel(QStringLiteral("收礼"), this);
	pGiftsNum->setAlignment(Qt::AlignCenter);
	pGifts->setAlignment(Qt::AlignCenter);
	pGiftsNum->setStyleSheet(strNumStyle);
	pGifts->setStyleSheet(strTextStyle);
	pSendGiftsNum		= new QLabel(QStringLiteral("9999万"), this);
	pSendGifts			= new QLabel(QStringLiteral("送礼"), this);
	pSendGiftsNum->setAlignment(Qt::AlignCenter);
	pSendGifts->setAlignment(Qt::AlignCenter);
	pSendGiftsNum->setStyleSheet(strNumStyle);
	pSendGifts->setStyleSheet(strTextStyle);
	pSeprateLine		= new QLabel(this);

	QString strOpen = QString("font-size:14px;font-weight:400;color:rgb(153,153,153);line-height:20px;");
	pOpenRoomTime		= new QLabel(QStringLiteral("我的开播时间"), this);
	pOpenRoomTime->setFixedHeight(20);
	pOpenTime1			= new QLabel(QStringLiteral("00:30"), this);
	pOpenTime1->setFixedHeight(22);
	pOpenTime2			= new QLabel(QStringLiteral("13:30"), this);
	pOpenTime2->setFixedHeight(22);
	pOpenTime3			= new QLabel(QStringLiteral("18:30"), this);
	pOpenTime3->setFixedHeight(22);

	pOpenRoomTime->setStyleSheet(strOpen);
	QString strTime = QString("font-size:16px;font-weight:400;color:rgb(153,153,153);line-height:22px;");
	pOpenTime1->setStyleSheet(strTime);
	pOpenTime2->setStyleSheet(strTime);
	pOpenTime3->setStyleSheet(strTime);

	pSeprateLine->setStyleSheet(QString("background:#313131;"));

	OpenTest();
	//main layout
	QVBoxLayout* pVLayoutMain = new QVBoxLayout;
	pVLayoutMain->setContentsMargins(0, 0, 0, 0);
	pVLayoutMain->addSpacing(10);
	//头像,主播昵称,icon栏
	QHBoxLayout* pHlauoutLine1 = new QHBoxLayout;
	
	pHlauoutLine1->addSpacing(12);
	pHlauoutLine1->addWidget(pLabelHead);
	pHlauoutLine1->addSpacing(10);
	QVBoxLayout* pVLayout1 = new QVBoxLayout;
	pVLayout1->setSpacing(0);
	pVLayout1->addWidget(pLabelName);
	//性别,爵位,等级,粉丝团icon

	QHBoxLayout* pHlauout2 = new QHBoxLayout;
	pHlauout2->setSpacing(2);
	pHlauout2->addWidget(pLabelGender);
	pHlauout2->addWidget(pLabelYork);
	pHlauout2->addWidget(pLabelLevel);
	pHlauout2->addWidget(pFunsGroup);
	pVLayout1->addLayout(pHlauout2);
	pHlauoutLine1->addLayout(pVLayout1);
	pHlauoutLine1->addStretch();

	pVLayoutMain->addLayout(pHlauoutLine1);
	pVLayoutMain->addSpacing(8);
	
	QHBoxLayout* pHlauout3 = new QHBoxLayout;
	pHlauout3->addSpacing(16);
	pHlauout3->addWidget(pLabelGroupId);
	pHlauout3->addSpacing(14);
	pHlauout3->addWidget(pLabelUqid);
	pHlauout3->addStretch();
	pVLayoutMain->addLayout(pHlauout3);
	pVLayoutMain->addSpacing(7);
	QHBoxLayout* pHlauoutSign = new QHBoxLayout;
	pHlauoutSign->addSpacing(16);
	pHlauoutSign->addWidget(pLabelSign);
	pVLayoutMain->addLayout(pHlauoutSign);
	pVLayoutMain->addSpacing(19);

	QHBoxLayout* pHlauout4 = new QHBoxLayout;
	pHlauout4->addSpacing(32);
	

	QVBoxLayout* pVlayout_4_1 = new QVBoxLayout;
	pVlayout_4_1->setSpacing(8);
	pFocusOnNum->setFixedHeight(20);
	pFocusOn->setFixedHeight(14);
	pVlayout_4_1->addWidget(pFocusOnNum);
	pVlayout_4_1->addWidget(pFocusOn);
	pHlauout4->addLayout(pVlayout_4_1,1);

	QVBoxLayout* pVlayout_4_2 = new QVBoxLayout;
	pVlayout_4_2->setSpacing(8);
	pFunsNum->setFixedHeight(20);
	pFuns->setFixedHeight(14);
	pVlayout_4_2->addWidget(pFunsNum);
	pVlayout_4_2->addWidget(pFuns);
	pHlauout4->addLayout(pVlayout_4_2, 1);

	QVBoxLayout* pVlayout_4_3 = new QVBoxLayout;
	pVlayout_4_3->setSpacing(8);
	pGiftsNum->setFixedHeight(20);
	pGifts->setFixedHeight(14);
	pVlayout_4_3->addWidget(pGiftsNum);
	pVlayout_4_3->addWidget(pGifts);
	pHlauout4->addLayout(pVlayout_4_3, 1);

	QVBoxLayout* pVlayout_4_4 = new QVBoxLayout;
	pVlayout_4_4->setSpacing(8);
	pSendGiftsNum->setFixedHeight(20);
	pSendGifts->setFixedHeight(14);
	pVlayout_4_4->addWidget(pSendGiftsNum);
	pVlayout_4_4->addWidget(pSendGifts);
	pHlauout4->addLayout(pVlayout_4_4, 1);

	pVLayoutMain->addLayout(pHlauout4);
	pVLayoutMain->addSpacing(18);

	QHBoxLayout* pHlauout5 = new QHBoxLayout;

	pSeprateLine->setFixedHeight(1);
	pHlauout5->addSpacing(12);
	pHlauout5->addWidget(pSeprateLine);
	pHlauout5->addSpacing(10);
	pVLayoutMain->addLayout(pHlauout5);

	QHBoxLayout* pHlauout6 = new QHBoxLayout;
	pHlauout6->addSpacing(11);
	pHlauout6->addWidget(pOpenRoomTime);
	pHlauout6->addSpacing(16);
	pHlauout6->addWidget(pOpenTime1);
	pHlauout6->addSpacing(16);
	pHlauout6->addWidget(pOpenTime2);
	pHlauout6->addSpacing(16);
	pHlauout6->addWidget(pOpenTime3);
	pHlauout6->addStretch();
	pVLayoutMain->addLayout(pHlauout6);
	pVLayoutMain->addSpacing(14);
	this->setLayout(pVLayoutMain);
}

UserCard::~UserCard()
{
}

void UserCard::OpenTest()
{
	
}

QPixmap UserCard::ScaledPixmap(const QString & strPixmap, QSize size)
{
	return QPixmap(strPixmap).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
