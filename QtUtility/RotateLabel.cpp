#include "RotateLabel.h"

#include <QDebug>
#include <QTimerEvent>
#include <QPainter>
#include <QTime>
#define ROTATE_ANGLE 60
RotateLabel::RotateLabel(QWidget* parent,const QString & strPath,const float & interval,const bool & clockwise)
	: QLabel(parent)
	, m_strPath(strPath)
	, m_fInterval(interval)
	, m_bClockWise(clockwise)
	, m_nTimer(0)
	, m_fRotate(0)
	, m_fRotateInterval(0)
{
	bool bLoad = m_pixRotate.load(strPath);
	if ( !bLoad )
	{
		qDebug()<<strPath<<" not exist";
	}
	else
	{
		resize(m_pixRotate.width(),m_pixRotate.height());
		this->setPixmap(m_pixRotate);
		StartTimer();
	}
}

RotateLabel::~RotateLabel()
{

}

void RotateLabel::paintEvent(QPaintEvent *e)
{
	QLabel::paintEvent(e);
}

void RotateLabel::timerEvent(QTimerEvent *event)
{
	if ( event->timerId() == m_nTimer )
	{
		if (m_bClockWise)
		{
			m_fRotate+=1;
		}
		else
		{
			m_fRotate-=1;
		}

		QPixmap & pixmap = GetPixmapByIndex(m_fRotate);
		this->setPixmap(pixmap);
		
		if (m_fRotate ==360 || m_fRotate==-360)
		{
			m_fRotate = 0;
		}
		update();
	}
}

void RotateLabel::StartTimer()
{
	m_fRotateInterval = (((float)m_fInterval)/360)*1000;
	m_nTimer = startTimer(m_fRotateInterval);
}

QPixmap & RotateLabel::GetPixmapByIndex(float angle)
{
	QMap<float ,QPixmap>::Iterator iter =  m_mapAngle2Pixmap.find(angle);
	if ( iter == m_mapAngle2Pixmap.end() )
	{
		int imageWidth = m_pixRotate.width();
		int imageHeight = m_pixRotate .height();

		QPixmap temp(m_pixRotate.size());
		temp.fill(Qt::transparent);
		QPainter  painter(&temp); 
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
		painter.translate(imageWidth / 2, imageHeight / 2); //让图片的中心作为旋转的中心
		painter.rotate(m_fRotate); //顺时针旋转90度
		painter.translate(-(imageWidth / 2), -(imageHeight / 2)); //使原点复原
		painter.drawPixmap(0, 0,   m_pixRotate);
		painter.end();
		m_mapAngle2Pixmap[angle]=temp;
	}
	return m_mapAngle2Pixmap[angle];
}