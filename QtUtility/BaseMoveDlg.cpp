#include "BaseMoveDlg.h"
#include <QMouseEvent>
#include <QDialog>
#include <QDebug>
BaseMoveDlg::BaseMoveDlg(QWidget *parent /* = NULL */)
	: QWidget(parent)
	, m_bLeftBtnPress(false)
	, m_bResize(false)
	, m_nMinWidth(600)
	, m_nMinHeight(600)
	, m_nMaxWidth(800)
	, m_nMaxHeight(800)
	, m_eScaleType(eScaleTypeNone)
{
	resize(m_nMinWidth, m_nMinHeight);
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	setMouseTracking(true);
}

BaseMoveDlg::~BaseMoveDlg()
{

}

void BaseMoveDlg::mousePressEvent(QMouseEvent *e)
{
	if ( e->button() == Qt::LeftButton)
	{
		QRect rectMainTop(0,0,rect().width(),10);
		QRect rectMainRight(rect().width() - 10, 0, 10, rect().width());
		QPoint point = e->pos();
		if (rectMainTop.contains(point))
		{
			m_bResize = true;
			m_bLeftBtnPress = true;
			m_eScaleType = eScaleTypeTop;
		}
		else if (rectMainRight.contains(point))
		{
			m_bResize = true;
			m_bLeftBtnPress = true;
			m_eScaleType = eScaleTypeRight;
		}
		else
		{
			m_bLeftBtnPress = true;
			m_bResize = false;
			m_eScaleType = eScaleTypeNone;
		}
		m_relativeInit = e->globalPos() - pos();
		qDebug() <<"InitPoint:"<< m_relativeInit <<"mapToGlobal:" << mapToGlobal(m_relativeInit);
		
	}
}

void BaseMoveDlg::mouseReleaseEvent(QMouseEvent *)
{
	m_bLeftBtnPress = false;
}

void BaseMoveDlg::mouseMoveEvent(QMouseEvent *e)
{
	//mouse state
	QRect rectMainTop(0, 0, rect().width(), 10);
	QRect rectMainRight(rect().width()-10, 0, 10, rect().width());
	if (rectMainTop.contains(e->pos()))
	{
		setCursor(Qt::SizeVerCursor);
	}
	else if (rectMainRight.contains(e->pos()))
	{
		setCursor(Qt::SizeHorCursor);
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
	//press or resize
	if (m_bLeftBtnPress)
	{
		if (m_bResize)
		{
			QPoint pos_cursor = QCursor::pos();
			QPoint pos2 = mapFromGlobal(pos_cursor);
			QPoint point = e->globalPos();
			qDebug() << "global:" << point << ",local:" << m_relativeInit;
			qDebug()<<"mapToGlobal:"<<mapToGlobal(m_relativeInit);
			QPoint initMapToGlobal = mapToGlobal(m_relativeInit);
			int w = initMapToGlobal.rx() - point.rx();
			int h = initMapToGlobal.ry() - point.ry();
			
			AdjustSize(m_eScaleType,w,h);
			QCursor::setPos(mapToGlobal(QPoint(e->globalPos()-pos())));
			//Move(m_eScaleType, w, h, e);
		}
		else
		{
			QPoint move_pos = e->globalPos();
			QPoint move_to = move_pos - m_relativeInit;
			move(move_to);
			qDebug() << "global:" << move_pos << ",local:" << m_relativeInit;
			qDebug() << "move_to:" << move_to.rx() << "," << move_to.ry();
		}
	}
	if (m_bLeftBtnPress&&!m_bResize)
	{
		
	}
	QWidget::mouseMoveEvent(e);
}

void BaseMoveDlg::resizeEvent(QResizeEvent *event)
{
	/*QSize size = event->size();
	if (size.width()>m_nMaxWidth && size.width()<m_nMinWidth)
	{
		resize(event->oldSize().width(),height());
	}
	if (size.height() > m_nMaxHeight && size.height() < m_nMinHeight)
	{
		resize(width(), event->oldSize().height());
	}*/
	QWidget::resizeEvent(event);
}

void BaseMoveDlg::AdjustSize(EScaleType eScaleType,int scale_w, int scale_h)
{
	int adjuseWidth = this->width();
	int adjustHeight = this->height();
	bool bAdjust = false;
	int w = width(), h = height();
	switch (m_eScaleType)
	{
	case eScaleTypeNone:
		return;
		break;
	case eScaleTypeLeft:
		break;
	case eScaleTypeTop:
		h += scale_h;
		break;
	case eScaleTypeRight:
		w -= scale_w;
		break;
	case eScaleTypeBottom:
		break;
	default:
		return;
		break;
	}

	if (w > m_nMinWidth && w < m_nMaxWidth  )
	{
		adjuseWidth = w;
		bAdjust = true;
	}
	if (h > m_nMinHeight && h < m_nMaxHeight )
	{
		adjustHeight = h;

		bAdjust = true;
	}
	if (bAdjust)
	{
		setFixedWidth(adjuseWidth);
		setFixedHeight(adjustHeight);
		//resize(adjuseWidth, adjustHeight);
	}
}

void BaseMoveDlg::Move(EScaleType eScaleType, int scale_w, int scale_h, QMouseEvent *e)
{
	QPoint point = e->globalPos();
	QPoint move_to = point - m_relativeInit;
	QPoint initMapToGlobal = mapToGlobal(m_relativeInit);
	switch (m_eScaleType)
	{
	case eScaleTypeNone:
		break;
	case eScaleTypeLeft:
		break;
	case eScaleTypeTop:
		move_to.setX(move_to.rx()+ scale_w);
		break;
	case eScaleTypeRight:

		break;
	case eScaleTypeBottom:
		break;
	default:
		break;
	}
	//move(move_to);
}