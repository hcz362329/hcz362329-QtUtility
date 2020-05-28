#include "chat_list_widget.h"
#include <QPainter>
#include <QScrollBar>
#include <QStyleOption>
#include "user_item_widget.h"
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
const QString scrollBarStyle2 = QString("QScrollBar:vertical\
									{\
										width: 5px;\
										min-height: 60px;\
										margin: 0px;\
										padding: 0px;\
										background-color: transparent;\
									}\
									QScrollBar::handle:vertical\
									{\
										width: 5px;\
										min-height: 20px;\
										border: 0px;\
										border-radius: 2px;\
										background-color: rgb(65,66,70);\
									}\
									QScrollBar::sub-line:vertical\
									{\
										height: 0px;\
										border-width: 0px;\
										subcontrol-position: top;\
									}\
									QScrollBar::add-line:vertical\
									{\
										height: 0px;\
										border-width: 0px;\
										subcontrol-position: bottom;\
									}\
									QScrollBar::down-arrow:vertical, QScrollBar::up-arrow:vertical\
									{\
										background: none;\
									} \
									QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
									{\
										margin: 0px 1px 0px 1px;\
										background-color: transparent;\
									}");

QString strListStye2 = QString("QListWidget{padding:0px;padding-top:0px; background:rgba(24,24,26,1);"
	"border-radius:2px;}"
	"QListWidget::Item{padding:0 0px;background:rgba(46,47,51,1);}"
	"QListWidget::Item:hover{background:rgba(24,24,26,1);padding:0 0px;}"
	"QListWidget::item:selected{background:rgba(24,24,26,1);padding:0 0px;border:1px solid red;}"
	"QListWidget::item:selected:!active{background:rgba(24,24,26,1);padding:0 0px;}");
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

	listWidget = new QListWidget(this);
	listWidget->setAutoScroll(true);
	listWidget->setStyleSheet(strListStye2);
	listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	listWidget->setFocusPolicy(Qt::NoFocus);
	QScrollBar* scroll = nullptr;
	scroll = listWidget->verticalScrollBar();
	if (scroll != nullptr) {
		scroll->setStyleSheet(scrollBarStyle2);
	}
	for (int i = 0; i < 7; i++) {
		QListWidgetItem* item = new QListWidgetItem(listWidget);
		UserItemWidget* itemWidget = nullptr;
		itemWidget = new UserItemWidget(listWidget);
		if (i % 5 == 0) {
			itemWidget->SetOfficial(true);
		}
		listWidget->addItem(item);
		QSize size = itemWidget->size();
		item->setSizeHint(size);
		listWidget->setItemWidget(item, itemWidget);
	}
	vLayer->addWidget(listWidget);
	vLayer->addSpacing(10);
}

void ChatListWidget::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}