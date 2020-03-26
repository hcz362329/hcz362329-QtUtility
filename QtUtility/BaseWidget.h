//edit by cz
#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include <QPixmap>
#include <QWidget>

class BaseWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BaseWidget(QWidget * parent);
	~BaseWidget();
public:
	QPixmap m_pixBg;
};

#endif