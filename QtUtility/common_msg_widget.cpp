#include "common_msg_widget.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QBitmap>
#include<QPainter>

CommonMsgWidget::CommonMsgWidget(QString strText, EMsgType eType, QWidget* parent)
	: QDialog(parent)
	, pLabeText(nullptr)
	, pBtnOk(nullptr)
	, pBtnClose(nullptr)
	, pBtnCancle(nullptr)
{
	setWindowFlags(Qt::Tool | windowFlags());
	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addStretch();
	pBtnClose = new QPushButton(this);
	pBtnClose->setFixedSize(28, 28);
	QString strClose = strBtnStyle.arg(":/res/Resources/images/close_0.png").arg(":/res/Resources/images/close_1.png").arg(":/res/Resources/images/close_1.png");
	pBtnClose->setStyleSheet(strClose);
	hlayout->addWidget(pBtnClose);

	QVBoxLayout* vlayout = new QVBoxLayout;
	vlayout->addSpacing(2);
	vlayout->addLayout(hlayout);
	vlayout->addSpacing(7);

	QHBoxLayout *hlayout2 = new QHBoxLayout;
	pLabeText = new QLabel(this);
	pLabeText->setAlignment(Qt::AlignCenter);
	pLabeText->setFixedWidth(200);
	pLabeText->setWordWrap(true);
	pLabeText->setStyleSheet("background:rgba(255,255,255,0);font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(92,92,92);line-height:18px;");
	pLabeText->setText(strText);
	pLabeText->adjustSize();
	hlayout2->addStretch();
	hlayout2->addWidget(pLabeText);
	hlayout2->addStretch();

	vlayout->addLayout(hlayout2);
	vlayout->addSpacing(10);

	auto ok_slot = [this]() {this->accept(); };
	auto close_slot = [this]() {this->reject(); };

	if (eType==eMsgKnow)
	{
		pBtnOk = new QPushButton(this);
		pBtnOk->setFixedSize(248, 40);
		pBtnOk->setStyleSheet("QPushButton{width:248px;height:40px;color:white;background:rgba(255,60,112,255);border-radius:20px;}QPushButton::hover{width:248px;height:40px;background:rgba(255,18,112,255);border-radius:20px;}QPushButton::pressed{width:248px;height:40px;background:rgba(255,18,112,255);border-radius:20px;}");
		pBtnOk->setText(QStringLiteral("我知道了"));
		
		connect(pBtnOk, &QPushButton::clicked, ok_slot);
		QHBoxLayout *hlayout3 = new QHBoxLayout;
		hlayout3->addStretch();
		hlayout3->addWidget(pBtnOk);
		hlayout3->addStretch();
		vlayout->addLayout(hlayout3);
	}
	else if (eType == eMsgCancleOk)
	{
		QString strOk = strBtnStyle.arg(":/res/Resources/images/ok_0.png").arg(":/res/Resources/images/ok_1.png").arg(":/res/Resources/images/ok_1.png");
		QString strCancle = strBtnStyle.arg(":/res/Resources/images/cancle_0.png").arg(":/res/Resources/images/cancle_1.png").arg(":/res/Resources/images/cancle_1.png");
		pBtnOk = new QPushButton(this);
		pBtnOk->setFixedSize(116, 42);
		pBtnOk->setStyleSheet(strOk);
		pBtnCancle = new QPushButton(this);
		pBtnCancle->setFixedSize(116, 42);
		pBtnCancle->setStyleSheet(strCancle);

		connect(pBtnOk, &QPushButton::clicked, ok_slot);
		connect(pBtnCancle, &QPushButton::clicked, close_slot);

		QHBoxLayout *hlayout3 = new QHBoxLayout;
		hlayout3->addSpacing(24);
		hlayout3->addWidget(pBtnCancle);
		hlayout3->addSpacing(16);
		hlayout3->addWidget(pBtnOk);
		hlayout3->addSpacing(24);
		vlayout->addLayout(hlayout3);
	}

	connect(pBtnClose, &QPushButton::clicked, close_slot);
	setLayout(vlayout);
	
	CreateBg();
}


CommonMsgWidget::~CommonMsgWidget()
{

}

int CommonMsgWidget::information(QWidget* parent, QString strText, EMsgType eType)
{
	CommonMsgWidget widget(strText, eType, parent);
	return widget.exec();
}

void CommonMsgWidget::CreateBg()
{
	bool bSave = false;
	if (pixmap.isNull())
	{
		int w = this->width();
		int h = this->height();
		pixmap = QPixmap(w, h);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(255, 255, 255, 255));
		painter.drawRoundedRect(QRect(0, 0, w, h), 6, 6);

		painter.end();
	}
}

void CommonMsgWidget::paintEvent(QPaintEvent* event)
{
	if (!pixmap.isNull())
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
		QBitmap bmp(this->size());
		bmp.fill();
		QPainter p(&bmp);
		p.setPen(Qt::NoPen);
		p.setBrush(Qt::black);
		p.drawRoundedRect(bmp.rect(), 6, 6);
		setMask(bmp);
	}
}