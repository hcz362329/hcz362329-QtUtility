#ifndef UnNormalShape_h
#define UnNormalShape_h
#include "Helper/QtHelper.hpp"
#include <QWidget>
#include <QPixmap>
class UnNormalShape : public QWidget
{
	Q_OBJECT
public:
	explicit UnNormalShape(const QPixmap & pixmap,const QPixmap & cover ,QWidget* parent=0);
	~UnNormalShape();

protected:
	virtual void paintEvent(QPaintEvent *);
private:
	QPixmap m_pixmap;
	QPixmap m_pixmapCover;
};
#endif