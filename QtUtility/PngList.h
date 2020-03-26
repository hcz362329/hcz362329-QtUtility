#ifndef PngList_h
#define PngList_h
#include <QWidget>
#include <QPixmap>
#include <QMap>
class PngList : public QWidget
{
	Q_OBJECT
public:
	explicit PngList(QWidget* parent,const float & interval);
	~PngList();
	QPixmap & GetPixmapByIndex(int index);
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
private:
	int m_iTimerId;
	int m_iIndex;
	QPixmap m_pixPngList;
	QMap<int ,QPixmap> m_mapIndex2Pixmap;
};
#endif