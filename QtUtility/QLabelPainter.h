#pragma once
#include <QLabel>
#include <QWidget>
#include "qpainterex.h"
#include "ImageHandle.h"

class QLabelPainter : public QLabel
{
	Q_OBJECT
public:
	QLabelPainter(QWidget* parent=0);
	~QLabelPainter();

	void SetRenderText(const STRenderText & text);
protected:
	void paintEvent(QPaintEvent *);
private:
	STRenderText m_stRenderText;
};

