#include "PngList.h"
#include <QTimerEvent>
#include <QPainter>
PngList::PngList(QWidget* parent,const float & interval)
	: QWidget(parent)
	, m_iTimerId(0)
	, m_iIndex(0)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowOpacity(0.1);
	float fSpeed = ((float)interval / 31 )*1000;
	m_pixPngList.load(".Animation/pnglist/wx0001.png");
	
	m_iTimerId = startTimer(fSpeed);
}

PngList::~PngList()
{

}

void PngList::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (m_iIndex >= 0 && !m_pixPngList.isNull() )
	{
		painter.drawPixmap(0, 0, m_pixPngList);
	}
	
}

void PngList::timerEvent(QTimerEvent *event)
{
	if ( m_iTimerId == event->timerId() )
	{
		m_iIndex++;
		m_pixPngList = GetPixmapByIndex(m_iIndex);
		/*QString strPath = QString("./Animation/pnglist/wx%1.png").arg(m_iIndex);
		bool bLoad = m_pixPngList.load(strPath);*/
		if ( m_iIndex==31)
		{
			killTimer(m_iTimerId);
			//m_iIndex=0;
		}
		update();
	}
}

QPixmap & PngList::GetPixmapByIndex(int index)
{
	QMap<int ,QPixmap>::Iterator iter =  m_mapIndex2Pixmap.find(index);
	if ( iter == m_mapIndex2Pixmap.end() )
	{
		QString strPath = QString("./Animation/pnglist/wx%1.png").arg(m_iIndex);
		QPixmap pixmap ;
		bool bLoad = pixmap.load(strPath);
		m_mapIndex2Pixmap[index] = pixmap;
	}
	return m_mapIndex2Pixmap[index];
}