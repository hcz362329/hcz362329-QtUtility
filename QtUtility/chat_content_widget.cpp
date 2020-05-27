#include "chat_content_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QScrollBar>
#include "content_item_widget.h"
const QString styleName = QString("padding:0px;padding-left:0px;padding-right:0px;\
								background:transparent;color:white;font-size:14px;\
								font-family:PingFangSC-Regular,PingFang SC;\
								font-weight:400;line-height:20px;");
const QString styleStatus = QString("padding:0px;padding-left:0px;padding-right:0px;\
								background:transparent;font-size:14px;\
								font-family:PingFangSC-Regular,PingFang SC;\
								font-weight:400;\
								color:rgba(255, 255, 255, 0.6);\
								line-height:20px;");

const QString styleBtn = QString("QPushButton{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:2px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #FF1270,stop:1 #FD583F);}\
									QPushButton::hover{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:2px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgba(255,18,112,0.5),stop:1 rgba(253,88,63,0.5));}");
const QString styleEdit = QString("background:rgba(216,216,216,0.34);border-radius:2px;\
								   border:1px solid rgba(151, 151, 151, 1); padding-top:2px;");
const QString styleList = QString("background:rgba(24,24,26,1);border:1px solid rgba(24,24,26,1);");
const QString scrollBarStyle = QString("QScrollBar:vertical\
									{\
										width: 8px;\
										min-height: 60px;\
										margin: 0px;\
										padding: 0px;\
										background-color: transparent;\
									}\
									QScrollBar::handle:vertical\
									{\
										width: 8px;\
										min-height: 20px;\
										border: 0px;\
										border-radius: 2px;\
										background-color: rgb(89,89,89);\
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

QString strListStye = QString("QListWidget{padding:0px;padding-top:0px; background:rgba(24,24,26,1);"
	"border-radius:2px;}"
	"QListWidget::Item{padding:0 0px;background:rgba(24,24,26,1);}"
	"QListWidget::Item:hover{background:rgba(24,24,26,1);padding:0 0px;}"
	"QListWidget::item:selected{background:rgba(24,24,26,1);padding:0 0px;}"
	"QListWidget::item:selected:!active{background:rgba(24,24,26,1);padding:0 0px;}");
const QString strScroll = QString("QScrollBar:vertical{\
						width:8px;\
						background:rgba(0,0,0,0 % );\
						margin:0px,0px,0px,0px;\
							padding - top:9px;  \
							padding - bottom:9px;\
						}");
std::vector<QString> vecContent = {QStringLiteral("2月24日 21:19"),
QStringLiteral("你们已成为好友,快聊天吧"),
QStringLiteral("你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你"),
QStringLiteral("你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你你好，很高兴认识你。你好，很高兴认识你")};
ChatContentWidget::ChatContentWidget(QWidget* parent)
	:QWidget(parent),
	vMainLayer(nullptr),
	lTopLayer(nullptr),
	pNameLabel(nullptr),
	pStatusLabel(nullptr),
	optionBtn(nullptr),
	sendLayer(nullptr),
	sendBtn(nullptr),
	contentEdit(nullptr),
	listLayout(nullptr),
	listWidget(nullptr){
	//setObjectName("ChatContent");
	Init();
}

ChatContentWidget::~ChatContentWidget() {

}

void ChatContentWidget::Init() {
	
	vMainLayer = new QVBoxLayout(this);
	vMainLayer->setContentsMargins(0, 0, 0, 0);
	vMainLayer->setSpacing(0);
	vMainLayer->addSpacing(10);
	lTopLayer = new QHBoxLayout;
	lTopLayer->setContentsMargins(0, 0, 0, 0);
	lTopLayer->setSpacing(0);
	lTopLayer->addSpacing(3);
	pNameLabel = new QLabel(QStringLiteral("用户昵称"),this);
	pNameLabel->setStyleSheet(styleName);
	pStatusLabel = new QLabel(QStringLiteral("(在线)"), this);
	pStatusLabel->setStyleSheet(styleStatus);
	optionBtn = new QPushButton(QString("..."), this);
	optionBtn->hide();
	pNameLabel->setFixedHeight(20);
	pStatusLabel->setFixedHeight(20);
	optionBtn->setFixedSize(60, 30);
	lTopLayer->addWidget(pNameLabel);
	lTopLayer->addSpacing(4);
	lTopLayer->addWidget(pStatusLabel);
	lTopLayer->addStretch();
	lTopLayer->addWidget(optionBtn);
	vMainLayer->addLayout(lTopLayer);
	vMainLayer->addSpacing(10);

	listLayout = new QHBoxLayout;
	listLayout->setContentsMargins(0, 0, 0, 0);
	listLayout->setSpacing(0);
	listWidget = new QListWidget(this);
	listWidget->setAutoScroll(true);
	listWidget->setStyleSheet(strListStye);
	listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	QScrollBar* scroll = nullptr;
	scroll = listWidget->verticalScrollBar();
	if (scroll != nullptr) {
		scroll->setStyleSheet(scrollBarStyle);
	}
	for (int i = 0; i < 100; i++) {
		QListWidgetItem* item = new QListWidgetItem(listWidget);
		ContentItemWidget* itemWidget = nullptr;
		ContentItemWidget::ItemType type =(ContentItemWidget::ItemType) (i % 4);
		QVariant var;
		MsgContent msg;
		msg.content = vecContent[type].toStdString();
		var.setValue(msg);
		itemWidget = new ContentItemWidget(listWidget, type, item, var);
		
		listWidget->addItem(item);
		/*QSize size = itemWidget->size();
		item->setSizeHint(size);*/
		listWidget->setItemWidget(item, itemWidget);
	}
	
	/*scroll = listWidget->verticalScrollBar();
	if (scroll != nullptr) {
		scroll->setStyleSheet(scrollBarStyle);
	}*/
	listLayout->addWidget(listWidget);
	listLayout->addSpacing(12);
	vMainLayer->addLayout(listLayout);
	vMainLayer->addSpacing(10);
	sendLayer = new QHBoxLayout;
	sendLayer->setContentsMargins(0, 0, 0, 0);
	sendLayer->setSpacing(0);
	sendLayer->addSpacing(12);
	contentEdit = new QTextEdit(this);
	contentEdit->setFixedHeight(28);
	contentEdit->setStyleSheet(styleEdit);
	contentEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	sendLayer->addWidget(contentEdit);
	sendBtn = new QPushButton(QStringLiteral("发送"), this);
	sendBtn->setFixedSize(60,28);
	sendBtn->setStyleSheet(styleBtn);
	sendLayer->addWidget(sendBtn);
	sendLayer->addSpacing(12);
	vMainLayer->addLayout(sendLayer);
	vMainLayer->addSpacing(10);

	connect(sendBtn, SIGNAL(clicked()), this, SLOT(OnSendBtnClicked()));
}

void ChatContentWidget::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void ChatContentWidget::OnSendBtnClicked() {
	QString strText = contentEdit->toPlainText();
	QListWidgetItem* item = new QListWidgetItem(listWidget);
	ContentItemWidget* itemWidget = nullptr;
	static int i = 1;
	i++;
	ContentItemWidget::ItemType type;
	if(i%2==0)
		type = ContentItemWidget::MsgRight;
	else
		type = ContentItemWidget::MsgLeft;
	QVariant var;
	MsgContent msg;
	msg.content = strText.toStdString();
	var.setValue(msg);
	itemWidget = new ContentItemWidget(listWidget, type, item, var);

	listWidget->addItem(item);
	/*QSize size = itemWidget->size();
	item->setSizeHint(size);*/
	listWidget->setItemWidget(item, itemWidget);
	contentEdit->clear();
	listWidget->scrollToBottom();
}