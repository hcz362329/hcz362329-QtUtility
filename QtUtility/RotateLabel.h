#ifndef RotateLabel_h
#define RotateLabel_h

#include<QLabel>
#include <QPixmap>
#include <QMatrix>
#include <QMap>
class RotateLabel : public QLabel
{
	Q_OBJECT
public:
	explicit RotateLabel(QWidget* parent,const QString & strPath,const float & interval,const bool & clockwise=true);
	~RotateLabel();
	void StartTimer();
	QPixmap & GetPixmapByIndex(float angle);
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void timerEvent(QTimerEvent *);
private:
	QPixmap m_pixRotate;
	QString m_strPath;
	float m_fInterval;
	bool m_bClockWise;
	int m_nTimer;
	float m_fRotate;
	float m_fRotateInterval;
	QMap<float ,QPixmap> m_mapAngle2Pixmap;
};

#endif

