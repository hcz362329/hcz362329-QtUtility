#ifndef Rotate_h
#define Rotate_h
#include <QWidget>
class Rotate : public QWidget
{
	Q_OBJECT
public:
	explicit Rotate(QWidget* parent=0);
	~Rotate();

protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	QPixmap m_pixmap;
};

#endif