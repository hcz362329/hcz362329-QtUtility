#include "Pixmap.h"
#include "Helper/QtHelper.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include <QProgressBar>
#include <QSlider>
Pixmap::Pixmap(QWidget* parent)
	: QWidget(parent)
	, m_nRCircle(0)
{
	resize(600,400);
	
	m_pixBg = QtHelper::GetPartPixmap("./loading.png",0,0,56,56);
	//m_pixBg = QtHelper::GetPixmapByColor(Qt::black,56,56);
	m_nRCircle = 28*sqrt((double)2);
	m_pixRed.load("./redline.png");
	QPixmap pixmap;
	pixmap.load("./xuetiao.png");
	m_pixBlood = QtHelper::GetRedPixmap(204,50);

	int nCopyWidth = m_pixBlood.width()*0.8;
	m_pixBloodNotUseLabel = m_pixBlood.copy(0,0,nCopyWidth,m_pixBlood.height());
	QLabel * pLabel1 = new QLabel(this);

	int w1 = m_pixBlood.width();
	int h2 = m_pixBlood.height();

	pLabel1->setGeometry(100,300,w1,h2);
	pLabel1->setPixmap(m_pixBlood);
	//pLabel1->hide();
	QLabel * pLabel2 = new QLabel(this);
	int w = m_pixBloodNotUseLabel.width();
	int h = m_pixBloodNotUseLabel.height();
	pLabel2->setGeometry(100,350,w,h);
	pLabel2->setPixmap(m_pixBloodNotUseLabel);
	//pLabel2->hide();

	QString strStyleSheet = QString(
		"QProgressBar {background: url(./xuetiao.png)0 0 50 0 no-repeat;}\
		 QProgressBar::chunk {background: url(./redline.png) no-repeat;}");
	
	/*

	QProgressBar *m_pProgressBar = new QProgressBar(this);
	m_pProgressBar->setStyleSheet(strStyleSheet);
	m_pProgressBar->setGeometry(0,0,204,50);
	m_pProgressBar->setMinimum(0);
	m_pProgressBar->setMaximum(100);


	QSlider * m_pSilder = new QSlider(this);
	m_pSilder->setGeometry(50,100,100,40);
	m_pSilder->setOrientation(Qt::Horizontal);
	m_pSilder->setRange(0,100);

	connect(m_pSilder,SIGNAL(valueChanged(int)),m_pProgressBar,SLOT(setValue(int)));
	connect(m_pProgressBar,SIGNAL(valueChanged(int)),m_pSilder,SLOT(setValue(int)));
	*/

	QLabel * label_skill = new QLabel(this);
	label_skill->setFixedWidth(233);
	label_skill->setWordWrap(true);
	QString strStyle = QString("background:rgba(34,33,36,0.95);border:1px solid rgba(28, 22, 21, 1);font-size:12px;font-family:Microsoft YaHei;font-weight:400;color:rgba(201,182,150,1);line-height:18px;padding:13px 17px;");
	label_skill->setStyleSheet(strStyle);
	label_skill->setText(QString::fromWCharArray(L"放出回旋镖，命中目标后提升自身移动速度，并降低敌方移动速度放出回旋镖"));
	
	label_skill->move(0,0);
	
}

Pixmap::~Pixmap()
{

}

void Pixmap::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.drawPixmap(100,200,m_pixBlood);

	painter.drawPixmap(100,250,m_pixBloodNotUseLabel);
	
}

void Pixmap::timerEvent(QTimerEvent *)
{

}