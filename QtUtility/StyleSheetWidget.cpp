#include "StyleSheetWidget.h"


StyleSheetWidget::StyleSheetWidget(QWidget* parent):QWidget(parent) {
	pBtn1 = new QPushButton("trigger btn",this);
	pBtn1->setGeometry(0, 10, 300, 40);
	QString strStyle = QString("QProgressBar{color:rgba(253,88,63,1);}");
	progress = new QProgressBar(this);
	progress->setGeometry(0, 100, 300, 40);
	progress->setRange(0, 100);
	static int value = 0;
	pText = new QTextEdit(this);
	pText->setGeometry(0, 150, 300, 150);
	pText->setText("QLabel{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FFDD84,stop:1 #FFB84C);border-radius:8px;font-size:13px;font-family:PingFangSC-Medium,PingFang SC;font-weight:500;color:rgb(244, 96, 78);}");
	pBtn2 = new QLabel("lineargradient",this);
	pBtn2->setGeometry(350,10,200,100);
	pBtn2->setAlignment(Qt::AlignCenter);
	QObject::connect(pBtn1, &QPushButton::clicked, this, &StyleSheetWidget::btn2clicked);
}

StyleSheetWidget::~StyleSheetWidget() {

}

void StyleSheetWidget::btn2clicked() {
	QString strStyle = pText->toPlainText();
	pBtn2->setStyleSheet(strStyle);
}