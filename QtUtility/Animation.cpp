#include "Animation.h"

#include <QPainter>
#include <QTimerEvent>
#include <QDebug>
#define CIRCLE_ENABLED 1

#define FRAME_NUM 160

CAnimation::CAnimation(QWidget *parent)
	: QWidget(parent)
	, m_bRunOver(false)
{
	/*setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);*/
	resize(400,400);
	setMouseTracking(true);
	m_imgIcon = new QImage(QSize(8960, 56), QImage::Format_ARGB32_Premultiplied);
#if 0
	bool bLoad = m_imgIcon->load("./loading.png");
#else
	bool bLoad = m_imgIcon->load("./loading3.png");
#endif
	

	m_iTimerId = 0;
	m_iIndex = -1;
}

CAnimation::~CAnimation()
{
	delete m_imgIcon;
}

void CAnimation::timerEvent(QTimerEvent *event)
{
	// 不停的更新 iIndex 的值，刷新界面，实现动画效果
	if (event->timerId() == m_iTimerId)
	{
		m_iIndex ++;

		if (m_iIndex > FRAME_NUM - 1)
		{
#ifdef CIRCLE_ENABLED
			m_iIndex = 0;
			
#else
			killTimer(m_iTimerId);
			m_iTimerId = 0;
			m_iIndex = -1;
			emit stopAnimation(m_stHero);
			hide();
			m_bRunOver = true;
#endif
		}
		update();
	}
}

void CAnimation::mouseMoveEvent(QMouseEvent *event)
{
	emit heroInfoSignal(m_stHero);
	QWidget::mouseMoveEvent(event);
}

void CAnimation::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	{
		QPainterPath path;
		path.addEllipse(100,100,56,56);
		painter.setBrush(Qt::red);
		painter.drawPath(path);
	}

	if (m_iIndex >= 0)
	{
		//painter.setCompositionMode(QPainter::CompositionMode_Screen);
		painter.drawImage(100, 100, *m_imgIcon, m_iIndex*56,0, 56,56);
		painter.drawText(QRect(100,200,50,20),QString::number(m_iIndex));
	}
}

void CAnimation::startAnimation(int nMsec)
{
	m_iTimerId = startTimer(nMsec);
	show();
}

void CAnimation::SetSeconds(int nsecs)
{
	int fSpeed = ((float)nsecs / FRAME_NUM )*1000;
	startAnimation(fSpeed);
}

void CAnimation::SetHero(const STHero & stHero)
{
	m_stHero = stHero;
	SetSeconds(m_stHero.ulBeginSecond);
}

STHero CAnimation::GetHero()
{
	return m_stHero;
}

bool CAnimation::IsRunOver()
{
	return m_bRunOver;
}

void CAnimation::StartQuickAnimation()
{
	int last_count = FRAME_NUM - m_iIndex;
	if ( last_count > 0 )
	{
		int internal_ = (0.2 / last_count)*1000;
		//internal_ = internal_>=50 ? internal_: 50;
		if ( m_iTimerId > 0 )
		{
			killTimer(m_iTimerId);
			m_iTimerId = startTimer(internal_);
		}
	}
}