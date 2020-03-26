#ifndef OpacityWidget_h
#define OpacityWidget_h
#include <QWidget>
#include <QMap>
class OpacityWidget : public QWidget
{
	Q_OBJECT
public:
	explicit OpacityWidget(QWidget* parent ,const QString & strPath,const float & interval,const float & opacity);
	~OpacityWidget();
	QPixmap & GetPixmapByOpacity(const float& opacity);
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
private:
	QPixmap m_pixmap;
	float m_nInterval;
	int m_nTimerId;
	float m_fOpacity;
	QMap<float,QPixmap> m_mapOpacity2Pixmap;
};

#endif