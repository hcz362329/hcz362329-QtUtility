#include "rounded_widget.h"
#include <QBitmap>
#include <QPainter>
RoundedWidget::RoundedWidget(QWidget* parent)
	:QWidget(parent)
	, nRadius(0)
{
	
}

void RoundedWidget::SetPixmap(const QString & strPixmap)
{
	bool bLoad = pixmap.load(strPixmap);
	QSize size = pixmap.size();
	resize(pixmap.size());
	if (bLoad)
	{
		setMask(pixmap.mask());
	}
}

void RoundedWidget::paintEvent(QPaintEvent* event)
{
	if (!pixmap.isNull())
	{
		QPainter painter(this);
		painter.drawPixmap(0,0,pixmap);
		if (nRadius>0)
		{
			QSize size = this->size();
			QBitmap bmp(this->size());
			bmp.fill();
			QPainter p(&bmp);
			p.setPen(Qt::NoPen);
			p.setBrush(Qt::black);
			p.drawRoundedRect(bmp.rect(), nRadius, nRadius);
			setMask(bmp);
		}
	}
	QWidget::paintEvent(event);
}

void RoundedWidget::SetRoundedColor(int w,int h,int border_radius,int r,int g,int b, int a)
{
	pixmap = QPixmap(w, h);
	pixmap.fill(Qt::transparent);
	QPainter painter;
	painter.begin(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(r,g,b));
	painter.drawRect(0,0,w,h);
	painter.end();
	nRadius = border_radius;
}