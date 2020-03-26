#ifndef PIXMAP_H
#define PIXMAP_H
#include<QWidget>
class Pixmap : public QWidget
{
	Q_OBJECT
public:
	explicit Pixmap(QWidget* parent=0);
	~Pixmap();
protected:
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent *);
private:
	QPixmap m_pixBg;
	double m_nRCircle;
	int m_nTimer;
	QPixmap m_pixRed;
	QPixmap m_pixBlood;

	QPixmap m_pixBloodNotUseLabel;
};
#endif