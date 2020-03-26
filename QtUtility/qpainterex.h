#ifndef QPAINTEREX_H
#define QPAINTEREX_H

#include <QPainter>

//QPainter::drawText实现反锯齿平滑模式（anti-alias smooth）
class QPainterEx : public QPainter
{
public:
	QPainterEx();
	explicit QPainterEx(QPaintDevice *);
	~QPainterEx();

	void drawText(const QRectF &r, int flags, const QString &text, QRectF *br=0);
	void drawText(const QRectF &r, const QString &text, const QTextOption &o = QTextOption());
	void drawText(const QPointF &p, const QString &str, int tf, int justificationPadding);
	void drawText(const QPointF &p, const QString &s);
	void drawText(const QRect &r, int flags, const QString &text, QRect *br=0);

	inline void drawText(const QPoint &p, const QString &s);
	inline void drawText(int x, int y, const QString &s);
	inline void drawText(int x, int y, int w, int h, int flags, const QString &text, QRect *br=0);

	//字体描边
	void setStrokePen(const QPen& pen);//这个pen是外部描边的pen
	void drawStrokeText(const QRectF &r, const QString &text, const QTextOption &o = QTextOption());

	//void drawText(const QRectF &r, int flags, const QString &text, QRectF *br=0);这种方式画的时候，QPainter::boundingRect()方法
	//存在问题，故需重新调整下boundingRect
	void ajustBoundingRect(const QRectF &rect, const QString &text, int flags, const QFontMetricsF& fm, QRectF &rectBounds);

private:
	Q_DISABLE_COPY(QPainterEx)
	QPen m_strokePen;
};

#endif // QPAINTEREX_H
