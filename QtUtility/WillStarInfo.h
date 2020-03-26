#ifndef WillStarInfo_h
#define WillStarInfo_h
#include <QWidget>
#include "QLabelPainter.h"

class WillStarInfo : public QWidget
{
	Q_OBJECT
public:
	explicit WillStarInfo(QWidget* parent = 0);
	~WillStarInfo();
protected:
	void paintEvent(QPaintEvent *);
private:
	QPixmap m_pixBg;
	QPixmap m_pixJx1Bg;
	QPixmap m_pixJx2Bg;
	QLabelPainter * m_pTitle;
};
#endif