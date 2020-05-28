#include "user_item_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

const QString styleName = QString("font-size:14px;font-weight:400;"
	"color:white;line-height:20px;");
const QString styleWeekDay = QString("font-size:11px;font-weight:400;"
	"color:rgba(173,173,173,1);line-height:16px;");
const QString styleUnKnown = QString("border-radius:7px;line-height:16px;"
	"color:white;font-weight:400px;font-size:11px;"
	"background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgb(32,148,249),stop:1 rgb(118,209,255));");
const QString styleWhisper = QString("border-radius:7px;line-height:16px;"
	"color:white;font-weight:400px;font-size:11px;"
	"background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgb(180,104,242),stop:1 rgb(207,129,255));");
const QString styleOfficial = QString("border-radius:7px;line-height:16px;"
	"color:white;font-weight:400px;font-size:11px;"
	"background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgb(255,18,112),stop:1 rgb(253,88,63));");
const QString styleOfficialName = QString("font-size:14px;font-weight:400;"
	"color:rgb(255,28,117);line-height:20px;");
const QString styleReddot = QString("background:rgba(250,109,109,1);"
	"border-radius:7px;font-size:11px;line-height:13px;color:white; ");
UserItemWidget::UserItemWidget(QWidget* parent)
	: QWidget(parent),
	pHead(nullptr),
	pName(nullptr),
	pUnKnown(nullptr),
	pWhisper(nullptr),
	pWeekDay(nullptr),
	pSign(nullptr),
	redDot(nullptr),
	pOfficial(nullptr){
	Init();
}

UserItemWidget::~UserItemWidget() {

}

void UserItemWidget::Init() {
	setFixedSize(255, 56);
	pHead = new QLabel(this);
	pHead->setFixedSize(32, 32);
	pName = new QLabel(QStringLiteral("用户昵称"),this);
	pName->setAlignment(Qt::AlignLeft);
	pName->setStyleSheet(styleName);
	pUnKnown = new QLabel(QStringLiteral("陌生人"),this);
	pUnKnown->setFixedSize(41,16);
	pUnKnown->setStyleSheet(styleUnKnown);
	pUnKnown->setAlignment(Qt::AlignCenter);
	pOfficial = new QLabel(QStringLiteral("官方"), this);
	pOfficial->setFixedSize(33, 16);
	pOfficial->setStyleSheet(styleOfficial);
	pOfficial->setAlignment(Qt::AlignCenter);
	pOfficial->hide();
	pWhisper = new QLabel(QStringLiteral("悄悄话"), this);
	pWhisper->setFixedSize(41, 16);
	pWhisper->setStyleSheet(styleWhisper);
	pWhisper->setAlignment(Qt::AlignCenter);
	pWeekDay = new QLabel(QStringLiteral("周三"), this);
	pWeekDay->setStyleSheet(styleWeekDay);
	pSign = new QLabel(QStringLiteral("我想要一个有缘的朋友"), this);
	redDot = new QLabel(QStringLiteral("3"), this);
	redDot->setStyleSheet(styleReddot);
	redDot->setAlignment(Qt::AlignCenter);
	QPixmap pixDefault; 
	pixDefault.load(":/res/Resources/images/head.png");
	pHead->setPixmap(pixDefault.scaled(pHead->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	pName->setFixedHeight(20);
	pWeekDay->setFixedHeight(20);
	pSign->setFixedHeight(20);
	redDot->setFixedSize(14, 14);

	QHBoxLayout* lMainLayout = new QHBoxLayout(this);
	lMainLayout->setSpacing(0);
	lMainLayout->setContentsMargins(0, 0, 0, 0);
	lMainLayout->addSpacing(14);
	lMainLayout->addWidget(pHead);
	lMainLayout->addSpacing(14);
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	QHBoxLayout* lLine1 = new QHBoxLayout(this);
	lLine1->setSpacing(0);
	lLine1->setContentsMargins(0, 0, 0, 0);
	lLine1->addWidget(pName);
	lLine1->addSpacing(5);
	lLine1->addWidget(pOfficial);
	lLine1->addSpacing(5);
	lLine1->addWidget(pUnKnown);
	lLine1->addSpacing(5);
	lLine1->addWidget(pWhisper);
	lLine1->addStretch();
	lLine1->addWidget(pWeekDay);
	
	QHBoxLayout* lLine2 = new QHBoxLayout(this);
	lLine2->setSpacing(0);
	lLine2->setContentsMargins(0, 0, 0, 0);
	lLine2->addWidget(pSign);
	lLine2->addStretch();
	lLine2->addWidget(redDot);
	vLayout->addSpacing(10);
	vLayout->addLayout(lLine1);
	vLayout->addStretch();
	vLayout->addLayout(lLine2);
	vLayout->addSpacing(10);

	lMainLayout->addLayout(vLayout);
	lMainLayout->addSpacing(8);
}

void UserItemWidget::SetOfficial(bool official) {
	if (official) {
		if (pName != nullptr && pOfficial!=nullptr) {
			pName->setStyleSheet(styleOfficialName);
			pOfficial->show();
		}
	}
}