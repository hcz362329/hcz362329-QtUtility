#include "stdafx.h"
#include "QxRadioLabel.h"

#include <QPainter>
#include <QMouseEvent>

QxRadioLabel::QxRadioLabel(QWidget *parent /* = NULL */)
	:QLabel(parent)
	, m_pMovie(NULL)
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint );
	//setAttribute(Qt::WA_TranslucentBackground);
}

QxRadioLabel::~QxRadioLabel()
{
	if ( m_pMovie != NULL )
	{
		delete m_pMovie;
		m_pMovie = NULL;
	}
}

void QxRadioLabel::setPixmapBG(QString strBG)
{
	m_pixBG.load(strBG);
	setPixmap(m_pixBG);
}

void QxRadioLabel::setGifMovie(QString strMovie)
{
	if ( m_pMovie == NULL )
	{
		m_pMovie = new QMovie(strMovie);
	}
	else
	{
		delete m_pMovie;
		m_pMovie = NULL;
		m_pMovie = new QMovie(strMovie);
	}
	setMovie(m_pMovie);
	m_pMovie->start();
}

void QxRadioLabel::mousePressEvent(QMouseEvent *ev)
{
	if ( ev->button() == Qt::LeftButton )
	{
		emit clicked();
	}
}

void QxRadioLabel::enterEvent(QEvent *)
{
	emit enterRadioLabel();
}

void QxRadioLabel::leaveEvent(QEvent *)
{
	emit leaveRadioLabel();
}

void QxRadioLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	if ( event->button() == Qt::LeftButton )
	{
		emit dbClicked();
	}
}