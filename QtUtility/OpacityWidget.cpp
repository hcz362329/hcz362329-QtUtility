#include "OpacityWidget.h"
#include <QTimerEvent>
#include <QPainter>
#include <QLabel>
OpacityWidget::OpacityWidget(QWidget* parent ,const QString & strPath,const float & interval,const float & opacity)
	: QWidget(parent)
	, m_nInterval(interval)
	, m_nTimerId(0)
	, m_fOpacity(opacity)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowOpacity(m_fOpacity);
	bool bLoad = m_pixmap.load(strPath);
	m_nTimerId = startTimer(m_nInterval);
	/*QLabel * pLabel = new QLabel(this);
	pLabel->setPixmap(m_pixmap);*/
}

QPixmap & OpacityWidget::GetPixmapByOpacity(const float& opacity)
{
	QMap<float,QPixmap>::Iterator iter = m_mapOpacity2Pixmap.find(opacity);
	if (iter == m_mapOpacity2Pixmap.end() )
	{
		QPixmap temp(m_pixmap.size());
		temp.fill(Qt::transparent); 
		QPainter  imagePain(&temp);
		imagePain.setCompositionMode(QPainter::CompositionMode_Source);
		imagePain.drawPixmap(0, 0, m_pixmap);
		imagePain.setCompositionMode(QPainter::CompositionMode_DestinationIn);
		imagePain.fillRect(temp.rect(), QColor(0, 0, 0, opacity));
		imagePain.end();
	}
	return m_mapOpacity2Pixmap[opacity];
}

OpacityWidget::~OpacityWidget()
{

}

void OpacityWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
#if 0
	QPixmap  pixmap = GetPixmapByOpacity(m_fOpacity);
	if ( !pixmap.isNull() )
	{
		painter.drawPixmap(0,0,pixmap);
	}
#else
	QPixmap temp(m_pixmap.size());
	temp.fill(Qt::transparent); 
	QPainter  imagePain;
	imagePain.begin(&temp);
	// ·´×ßÑù
	imagePain.setRenderHint(QPainter::Antialiasing, true);
	imagePain.drawPixmap(0, 0, m_pixmap);
	imagePain.fillRect(temp.rect(), QColor(0, 0, 0, 0.2));
	imagePain.end();
	painter.drawPixmap(0,0,temp);
#endif
	
	QWidget::paintEvent(event);
}

void OpacityWidget::timerEvent(QTimerEvent *event)
{
	if ( m_nTimerId == event->timerId())
	{
		//m_fOpacity = (m_fOpacity==1)?0.2:1;
		//setWindowOpacity(m_fOpacity);
	}
	update();
}