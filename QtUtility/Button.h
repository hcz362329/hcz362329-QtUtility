#ifndef Button_h
#define Button_h
#include <QPushButton>
#include <QImage>
class Button : public QPushButton
{
	Q_OBJECT
public:
	explicit Button(const QString & name,QWidget* parent=0);
	~Button();

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
private:
	QImage m_image;
	QImage m_imageNormal;
	QImage m_imageHorver;
	QImage m_imagePress;
	QImage m_imageDisable;

	QList<QImage> m_list;
};

#endif
#include <QPushButton>