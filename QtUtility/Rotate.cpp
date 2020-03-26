#include "Rotate.h"
#include "RotateLabel.h"
#include "PngList.h"
#include "OpacityWidget.h"
#include "helper/QtHelper.hpp"
#include <QPainter>
Rotate::Rotate(QWidget* parent)
	:QWidget(parent)
{
	resize(1000,1000);
	//setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowOpacity(0.6);
	RotateLabel * label = new RotateLabel(this,"./Images/RuneBkg.png",0.5,true);
	label->move(50,50);

	RotateLabel * label_ = new RotateLabel(this,"./Images/RuneBkg.png",0.5,false);
	label_->move(190,50);

	RotateLabel * label1 = new RotateLabel(this,"./Animation/bg_light.png",3.72,true);
	label1->move(335,192);

	RotateLabel * label2 = new RotateLabel(this,"./Animation/light2.png",3.2,false);
	label2->move(335,192);

	RotateLabel * label3 = new RotateLabel(this,"./Animation/light1.png",3.2,true);
	label3->move(335,192);


	QPixmap pixmap;
	bool bLoad = pixmap.load("./Animation/light3.png");
	OpacityWidget* flash1 = new OpacityWidget(this,"./Animation/light3.png",0.16,0.2);
	flash1->setGeometry(265,299,pixmap.width(),pixmap.height());

	OpacityWidget* flash2 = new OpacityWidget(this,"./Animation/light3.png",0.16,1);
	QPixmap pixmap2 = pixmap.scaled(QSize(pixmap.width()*0.8,pixmap.height()*0.8),Qt::KeepAspectRatio,Qt::SmoothTransformation);
	flash2->setGeometry(467,317,pixmap2.width(),pixmap2.height());

	PngList * pnglist = new PngList(this,1.24);
	pnglist->setGeometry(0,0,967,679);

	m_pixmap.load("./common_layer.png");
}

Rotate::~Rotate()
{

}

void Rotate::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (!m_pixmap.isNull())
	{
		painter.drawPixmap(0,0,m_pixmap.scaled(QSize(967,679),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}