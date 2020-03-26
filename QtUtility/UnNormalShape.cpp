#include "UnNormalShape.h"
#include <QPainter>
#include <QBitmap>
UnNormalShape::UnNormalShape(const QPixmap & pixmap,const QPixmap & cover ,QWidget* parent)
	: QWidget(parent)
	, m_pixmap(pixmap)
	, m_pixmapCover(cover)
{
	setMask(m_pixmap.mask());
}

UnNormalShape::~UnNormalShape()
{

}

void UnNormalShape::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.drawPixmap(0,0,m_pixmap.scaled(QSize(width(),height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	//painter.drawPixmap(1,1,m_pixmap.scaled(QSize(width()-2,height()-2),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	painter.drawPixmap(0,0,m_pixmapCover.scaled(QSize(width(),height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}