#pragma once

#include <QWidget>
class HdCharge : public QWidget
{
	Q_OBJECT
public:
	HdCharge(QWidget* parent=0);
	~HdCharge();
	QPixmap GetPixmapByColor(QColor color,int w,int h);
protected:
	void paintEvent(QPaintEvent *);
private:
	QPixmap m_pixBg;
	QPixmap m_pixTop;
	QPixmap m_pixTitle;
};

