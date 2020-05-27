#include "emoji.h"
#include <QDebug>
Emoji::Emoji(QWidget* parent) :
	QWidget(parent) {
	setGeometry(300, 300, 500, 500);
	pBtn = new QPushButton("click", this);
	pBtn->setGeometry(0, 0, 100, 50);
	pBtn->setFont(QFont("EmojiOne Color"));
	
	pEmojiText = new QTextEdit(this);
	pEmojiText->setFontFamily("Segoe UI Emoji");
	pEmojiText->setGeometry(0, 50, 300, 250);

	connect(pEmojiText, &QTextEdit::textChanged, this, &Emoji::OnTextChanged);
	
	
	/*QString strImg = QString("<img src='%1'  width='32' height='32'/>").arg("./emoji/8ball.png");
	QString strImg2 = QString("<img src='%1' width='32' height='32'/>").arg("./emoji/100.png");
	QString strImg3 = QString("<img src='%1' width='32' height='32'/>").arg("./emoji/aries.png");
	pEmojiText->append("8ball.png:"+strImg + strImg2);
	pEmojiText->append("100png:"+ strImg2+ strImg3);*/
	QString strStyleLinear = QString("QPushButton{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:14px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #FF1270,stop:1 #FD583F);border-radius:10px;}\
									QPushButton::disabled{text-align:center;font-size:14px;font-weight:400;\
									color:rgba(255,255,255,1);padding:0px; \
									margin:0px;border-radius:14px;\
									background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgba(255,18,112,0.5),stop:1 rgba(253,88,63,0.5));border-radius:10px;}");
	btn = new QPushButton(QStringLiteral("邀请"),this);
	btn->setGeometry(10,400,60,20);
	btn->setStyleSheet(strStyleLinear);
	auto SlotClicked = [&] {
		btn->setEnabled(!btn->isEnabled());
		OnBtnClicked();
	};
	auto SlotClicked2 = [&] {
		qDebug() << "1";
	};
	connect(btn, &QPushButton::clicked, SlotClicked2);
	connect(pBtn, &QPushButton::clicked, SlotClicked);
}

Emoji::~Emoji() {

}

void Emoji::OnBtnClicked() {
	QString strText = pEmojiText->toPlainText();
	qDebug() << "strText:" << strText;
}

void Emoji::OnTextChanged() {
	QString text = pEmojiText->toPlainText();
	qDebug() << "strText:" << text;
}