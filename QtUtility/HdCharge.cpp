#include "HdCharge.h"
#include <QPainter>
#include <QLabel>
#include "QLabelPainter.h"
HdCharge::HdCharge(QWidget* parent)
	:QWidget(parent)
{
	resize(360,210);
	setWindowFlags(Qt::FramelessWindowHint|windowFlags());
	setAttribute(Qt::WA_TranslucentBackground);
	m_pixBg.load("./222.png");
	m_pixTitle.load("./bg_title_all.png");
	QLabel * label = new QLabel(this);
	label->setGeometry(2,2,356,33);
	label->setStyleSheet("background:#2d3034;");

	QLabel * label_title = new QLabel(this);
	label_title->setGeometry(2,2,m_pixTitle.width(),m_pixTitle.height());
	label_title->setPixmap(m_pixTitle);

	QLabelPainter* title_tip = new QLabelPainter(this);
	title_tip->setGeometry(8,2,100,33);
	STRenderText stRender;
	stRender.bold = false;
	stRender.is_TextFlag = true;
	stRender.flag = Qt::AlignLeft | Qt::AlignVCenter;
	stRender.strFamilyName = QString::fromWCharArray(L"汉仪小隶书简");
	stRender.font_size = 18;
	stRender.text_color = QColor("#F2DDBA");
	stRender.strRenderText = QString::fromWCharArray(L"升级提示");
	title_tip->SetRenderText(stRender);
	QPushButton* close_btn = new QPushButton(this);
	close_btn->setGeometry(338,5,22,21);
	QString strSheet = QString("QPushButton{border-width: 0;border-radius: 0;border-image: url(./1.png) 0 0 0 0 repeat;}\
							   QPushButton:hover {border-image: url(./2.png) 0 0 0 0 repeat;}\
							   QPushButton:pressed{border-image: url(./3.png) 0 0 0 0 repeat;}");
	close_btn->setStyleSheet(strSheet);
	connect(close_btn,&QPushButton::clicked,this,[=]{hide();});

	QLabel* content = new QLabel(this);
	content->setGeometry(0,89,width(),20);
	content->setStyleSheet("font-size:16px;font-family:Microsoft YaHei;font-weight:400;color:rgba(44,44,44,1);line-height:36px;");
	content->setText(QString::fromWCharArray(L"更新还未完成，请稍后！"));
	content->setAlignment(Qt::AlignCenter);
	content->setWordWrap(true);

	QPushButton* close_btn2 = new QPushButton(this);
	close_btn2->setText(QString::fromWCharArray(L"确定"));
	close_btn2->setGeometry(120,140,120,30);
	QString strSheet2 = QString("QPushButton{font-size:16px;font-family:Microsoft YaHei;font-weight:400;color:rgba(44,44,44,1);border-width: 0;border-radius: 0;border-image: url(./Btn_120x302.png) 0 0 0 0 repeat;}\
							   QPushButton:hover {border-image: url(./Btn_120x302.png) 30 0 0 0 repeat;}\
							   QPushButton:pressed{border-image: url(./Btn_120x302.png) 30 0 0 0 repeat;}");
	close_btn2->setStyleSheet(strSheet2);
	connect(close_btn2,&QPushButton::clicked,this,[=]{hide();});

}


HdCharge::~HdCharge(void)
{
}

void HdCharge::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.drawPixmap(0,0,m_pixBg);
}

QPixmap HdCharge::GetPixmapByColor(QColor color,int w,int h)
{
	QPixmap pixmap = QPixmap(w, h);
	pixmap.fill(Qt::transparent);
	QPainter painter;
	painter.setBrush(color);
	painter.begin(&pixmap);
	painter.drawRect(QRect(0, 0, w-1, h-1));
	painter.end();
	return pixmap;
}
