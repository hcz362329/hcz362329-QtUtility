#ifndef HQRADIOLABEL_H
#define HQRADIOLABEL_H
#include <QLabel>
#include <QMovie>

class QxRadioLabel : public QLabel
{
	Q_OBJECT
public:
	explicit QxRadioLabel(QWidget *parent = NULL);
	~QxRadioLabel();
public:
	void setPixmapBG(QString);
	void setGifMovie(QString);
protected:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *ev);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
private:
	QPixmap  m_pixBG;
	QMovie*  m_pMovie;
signals:
	void clicked();
	void dbClicked();
	void enterRadioLabel();
	void leaveRadioLabel();
};

#endif