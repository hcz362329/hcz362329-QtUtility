#include "content_item_widget.h"

#include <QDebug>
#include <QTextBlock>
#include <QResizeEvent>

const QString styleFriend = QString("background:rgba(46,47,51,1);"
	"border-radius:12px;border:none;"
	"font-size:12px;"
	"font-family:PingFangSC-Regular, PingFang SC;"
	"font-weight:400;"
	"color:rgba(255, 255, 255, 0.6);"
	"line-height:17px;"
);
const QString styleDate = QString("font-size:11px;"
	"font-family:PingFangSC-Regular,PingFang SC;"
	"font-weight:400;"
	"color:rgba(173, 173, 173, 1);"
	"line-height:16px;");
const QString styleContent = QString("padding:4px 4px 4px 4px;border-radius:1px 4px 4px 4px; background:rgba(74,75,78,1);"
	"font-size:12px;"
	"font-family:PingFangSC-Regular,PingFang SC;"
	"font-weight:400;"
	"color:rgba(255, 255, 255, 1);"
	"line-height:17px;");
ContentItemWidget::ContentItemWidget(QWidget* parent,ItemType type, QListWidgetItem* item,const QVariant& var)
	:QWidget(parent),
	lMainLayer(nullptr),
	vMsgLayer(nullptr),
	pBeFriend(nullptr),
	pDate(nullptr),
	pHead(nullptr),
	pStatus(nullptr),
	pContent(nullptr),
	item(nullptr){
	this->item = item;
	setMinimumWidth(364);
	pixDefault.load(":/res/Resources/images/head.png");
	pixSending.load(":/res/Resources/images/status_sending.png");
	pixSendFail.load(":/res/Resources/images/status_send_fail.png");
	lMainLayer = new QHBoxLayout;
	lMainLayer->setSpacing(0);
	lMainLayer->setContentsMargins(0, 0, 0, 0);
	vMsgLayer = new QVBoxLayout;
	vMsgLayer->setSpacing(0);
	vMsgLayer->setContentsMargins(0, 0, 0, 0);
	vMsgLayer->addSpacing(16);
	MsgContent msg = qvariant_cast<MsgContent>(var);
	switch (type)
	{
	case ContentItemWidget::Date: {
		lMainLayer = new QHBoxLayout();
		lMainLayer->setSpacing(0);
		lMainLayer->setContentsMargins(0, 0, 0, 0);
		pDate = new QLabel(this);
		pDate->setText(QString::fromLocal8Bit(msg.content.data()));
		pDate->setFixedHeight(16);
		pDate->setStyleSheet(styleDate);
		pDate->setAlignment(Qt::AlignCenter);
		lMainLayer->addStretch();
		lMainLayer->addWidget(pDate);
		lMainLayer->addStretch();
		vMsgLayer->addLayout(lMainLayer);
		setLayout(vMsgLayer);
		this->setFixedHeight(32);
	}
		break;
	case ContentItemWidget::BeFriend: {
		lMainLayer = new QHBoxLayout();
		lMainLayer->setSpacing(0);
		lMainLayer->setContentsMargins(0, 0, 0, 0);
		pBeFriend = new QLabel(this);
		pBeFriend->setText(QString::fromLocal8Bit(msg.content.data()));
		pBeFriend->setFixedSize(263,24);
		pBeFriend->setStyleSheet(styleFriend);
		pBeFriend->setAlignment(Qt::AlignCenter);
		lMainLayer->addStretch();
		lMainLayer->addWidget(pBeFriend);
		lMainLayer->addStretch();
		vMsgLayer->addLayout(lMainLayer);
		setLayout(vMsgLayer);
		this->setFixedHeight(40);
	}
		break;
	case ContentItemWidget::MsgLeft:
	case ContentItemWidget::MsgRight: {
		
		pHead = new QLabel(this);
		pHead->setFixedSize(32, 32);
		pHead->setPixmap(pixDefault.scaled(pHead->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		pStatus = new QLabel(this);
		pStatus->setFixedSize(16, 16);
		pStatus->setPixmap(pixSending.scaled(pStatus->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		pContent = new QTextEdit(this);
		
		pContent->setText(QString::fromStdString(msg.content.data()));
		pContent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		pContent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		pContent->setEnabled(false);

		QTextDocument *pDoc = nullptr;
		pDoc = pContent->document();
		if (pDoc != nullptr) {
			QTextBlock block = pDoc->lastBlock();
			QTextCursor tc(block);
			QTextBlockFormat fmt = block.blockFormat();
			fmt.setLineHeight(10, QTextBlockFormat::LineDistanceHeight);
			tc.setBlockFormat(fmt);
		}
		pContent->setStyleSheet(styleContent);

		pContentLabel = new QLabel(this);
		pContentLabel->setWordWrap(true);
		pContentLabel->setStyleSheet(styleContent);
		pContentLabel->setFixedHeight(20);
		pContentLabel->setText(QString::fromStdString(msg.content.data()));
		//QString strText = QStringLiteral("大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水大家好我是渣渣灰我今年洗脚水");
		//pContentLabel->setText(strText);
		lMainLayer->addSpacing(16);
		QVBoxLayout* headLayout = new QVBoxLayout;
		headLayout->setSpacing(0);
		headLayout->setContentsMargins(0, 0, 0, 0);
		headLayout->addWidget(pHead,0);
		headLayout->addStretch();

		QVBoxLayout* statusLayout = new QVBoxLayout;
		statusLayout->setSpacing(0);
		statusLayout->setContentsMargins(0, 0, 0, 0);
		statusLayout->addStretch();
		statusLayout->addWidget(pStatus,0);

		if (type == ContentItemWidget::MsgLeft) {
			lMainLayer->addLayout(headLayout);
			lMainLayer->addSpacing(10);
			lMainLayer->addWidget(pContentLabel, 0);
			lMainLayer->addWidget(pContent, 0);
			lMainLayer->addSpacing(10);
			lMainLayer->addLayout(statusLayout);
			lMainLayer->addStretch();
			lMainLayer->addSpacing(100);
		}
		else {
			pStatus->setPixmap(pixSendFail.scaled(pStatus->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			lMainLayer->addSpacing(100);
			lMainLayer->addStretch();
			lMainLayer->addLayout(statusLayout);
			lMainLayer->addSpacing(10);
			lMainLayer->addWidget(pContentLabel, 0);
			lMainLayer->addWidget(pContent, 1);
			lMainLayer->addSpacing(10);
			lMainLayer->addLayout(headLayout);

		}
		vMsgLayer->addLayout(lMainLayer);
		setLayout(vMsgLayer);
		int w = pContentLabel->width();
		int h = pContentLabel->height();
		int w2 = pContentLabel->fontMetrics().width(msg.content.data());
		int line_width = this->width() - pHead->width() - pStatus->width() - 120;
		int h2 = ((w2 - 1) / line_width + 1) * 20;
		
		h2 = h2 < 32 ? 32 : h2;
		pContentLabel->hide();
		w2 = w2 > line_width ? line_width : w2;
		pContent->setFixedSize(w2,h2);
		this->setFixedHeight(h2 +16);
	}
		break;
	default:
		break;
	}
	if (this->item != nullptr) {
		this->item->setSizeHint(this->size());
	}
}

ContentItemWidget::~ContentItemWidget() {

}


void ContentItemWidget::resizeEvent(QResizeEvent* event) {
	qDebug()<<"old size"<<event->oldSize();
	qDebug()<<"new size"<< event->size();
	if (pContent != nullptr) {
		
	}
	__super::resizeEvent(event);
}