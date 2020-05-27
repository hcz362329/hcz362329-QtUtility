#include "imwidget.h"
#include "chat_list_widget.h"
#include "chat_content_widget.h"
#include <QMessageBox>
#include <QMouseEvent>
const QString strStyle = QString("\
							QLabel#TopBg{background:rgba(38,40,46,1);border-radius:7px; }\
							QLabel#MsgTitle{padding:0px;padding-left:0px;padding-right:0px;background:transparent;color:white;font-size:16px;font-weight:500;line-height:22px;}\
							QDialog#IMWidgetObj{background:rgba(35,36,42,1);border-radius:7px;}\
							QWidget#ChatList{background:blue;border-radius:0px;}\
							QWidget#ChatContent{background:green;}\
							QTextEdit{background:white;color:black;}");
#define CHATLIST_WIDTH 260
IMWidget::IMWidget(QWidget* parent)
	:QDialog(parent),
	vMainLayer(nullptr), 
	lTopLayer(nullptr), 
	pTopBg(nullptr),
	pTitle(nullptr) ,
	pCloseBtn(nullptr),
	lChatLayer(nullptr),
	contentLayout(nullptr),
	pChatList(nullptr){
	//setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	this->setStyleSheet(strStyle);
	this->setObjectName("IMWidgetObj");
	this->setMinimumSize(736,477);
	m_pressed = false;
	Init();
}

IMWidget::~IMWidget() {

}

void IMWidget::Init() {
	vMainLayer		= new QVBoxLayout(this);
	lTopLayer		= new QHBoxLayout;
	lChatLayer		= new QHBoxLayout;
	struct stLayout {
		QBoxLayout* pLayout;
	}layouts[] = {
		{ vMainLayer },
		{ lTopLayer },
		{ lChatLayer },
	};
	for(auto layout : layouts) {
		layout.pLayout->setSpacing(0);
		layout.pLayout->setContentsMargins(0, 0, 0, 0);
	}
	pTopBg = new QLabel(this);
	pTopBg->setFixedHeight(44);
	pTopBg->setObjectName("TopBg");
	pTitle = new QLabel(QStringLiteral("消息列表"),this);
	pTitle->setFixedHeight(22);
	pTitle->setAlignment(Qt::AlignLeft);
	pTitle->setObjectName("MsgTitle");
	pCloseBtn = new QPushButton(pTopBg);
	pCloseBtn->setFixedSize(12,12);
	pCloseBtn->setStyleSheet("border-image: url(:/res/Resources/images/item_close.png);");
	
	lTopLayer->addSpacing(10);
	lTopLayer->addWidget(pTitle);
	lTopLayer->addStretch();
	lTopLayer->addWidget(pCloseBtn);
	lTopLayer->addSpacing(13);
	pTopBg->setLayout(lTopLayer);
	vMainLayer->addWidget(pTopBg);
	pChatList = new ChatListWidget(this);
	pChatList->setFixedWidth(CHATLIST_WIDTH);
	lChatLayer->addWidget(pChatList);
	contentLayout = new QStackedLayout;
	contentLayout->setSpacing(0);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	pChatContent = new ChatContentWidget(this);
	contentLayout->insertWidget(1,pChatContent);
	lChatLayer->addLayout(contentLayout);
	vMainLayer->addLayout(lChatLayer);
	InitConnect();
}

void IMWidget::OnCloseBtn() {
	this->close();
}

void IMWidget::InitConnect() {
	QMetaObject::Connection con;
	con = connect(pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtn()));
	if (con == NULL) {
#if _DEBUG
		QMessageBox::information(NULL,"error","connect error");
#endif
	}
}

void IMWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_pressPoint = event->globalPos();
		m_pressed = true;
	}
	event->ignore();
}

void IMWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_pressed = false;
	}
	event->ignore();
}

void IMWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (m_pressed)
	{
		m_movePoint = event->globalPos();
		this->move(this->pos() + m_movePoint - m_pressPoint);
		m_pressPoint = m_movePoint;
	}
	event->ignore();
}