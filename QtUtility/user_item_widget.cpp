#include "user_item_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
UserItemWidget::UserItemWidget(QWidget* parent)
	: QWidget(parent),
	pHead(nullptr),
	pName(nullptr),
	pUnKnown(nullptr),
	pWhisper(nullptr),
	pWeekDay(nullptr),
	pSign(nullptr),
	redDot(nullptr){
	Init();
}

UserItemWidget::~UserItemWidget() {

}

void UserItemWidget::Init() {
	setFixedSize(255, 56);
	pHead = new QLabel(this);
	pHead->setFixedSize(32, 32);
	pName = new QLabel(this);
	pUnKnown = new QLabel(QStringLiteral("陌生人"),this);
	pWhisper = new QLabel(QStringLiteral("悄悄话"), this);
	pWeekDay = new QLabel(QStringLiteral("周三"), this);
	pSign = new QLabel(QStringLiteral("我想要一个有缘的朋友"), this);
	redDot = new QLabel(QStringLiteral("3"), this);
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
	lMainLayout->addSpacing(0);
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
}