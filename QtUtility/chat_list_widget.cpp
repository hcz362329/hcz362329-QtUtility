#include "chat_list_widget.h"
#include <QPainter>
#include <QStyleOption>
const QString strDesc = QString("padding:0px;padding-left:0px;padding-right:0px;\
								background:transparent;color:white;font-size:14px;\
								font-family:PingFangSC-Regular,PingFang SC;\
								font-weight:400;line-height:22px;");
const QString styleCount = QString("padding:0px;padding-left:0px;padding-right:0px;\
								background:transparent;font-size:14px;\
								font-family:PingFangSC-Regular,PingFang SC;\
								font-weight:400;\
								color:rgba(255, 255, 255, 0.6);\
								line-height:20px;");
ChatListWidget::ChatListWidget(QWidget* parent)
	:QWidget(parent),
	vLayer(nullptr){
	Init();
}

ChatListWidget::~ChatListWidget() {

}

void ChatListWidget::Init() {
	vLayer = new QVBoxLayout(this);
	QHBoxLayout* hListLayout = new QHBoxLayout;
	hListLayout->setSpacing(0);
	hListLayout->setContentsMargins(0, 0, 0, 0);
	QLabel* desc = new QLabel(QStringLiteral("ÁÄÌìÁÐ±í"), this);
	desc->setStyleSheet(strDesc);
	desc->setFixedHeight(20);
	desc->setAlignment(Qt::AlignLeft);
	hListLayout->addSpacing(10);
	hListLayout->addWidget(desc);

	pListCount = new QLabel(QStringLiteral("(24)"), this);
	pListCount->setStyleSheet(styleCount);
	pListCount->setFixedHeight(20);
	pListCount->setAlignment(Qt::AlignLeft);
	hListLayout->addSpacing(4);
	hListLayout->addWidget(pListCount);
	hListLayout->addStretch();

	vLayer->setSpacing(0);
	vLayer->setContentsMargins(0, 0, 0, 0);
	vLayer->addSpacing(10);
	vLayer->addLayout(hListLayout);
	vLayer->addStretch();
}

void ChatListWidget::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}