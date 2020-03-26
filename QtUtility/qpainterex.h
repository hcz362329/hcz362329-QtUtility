#ifndef QPAINTEREX_H
#define QPAINTEREX_H

#include <QPainter>

//QPainter::drawTextʵ�ַ����ƽ��ģʽ��anti-alias smooth��
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

	//�������
	void setStrokePen(const QPen& pen);//���pen���ⲿ��ߵ�pen
	void drawStrokeText(const QRectF &r, const QString &text, const QTextOption &o = QTextOption());

	//void drawText(const QRectF &r, int flags, const QString &text, QRectF *br=0);���ַ�ʽ����ʱ��QPainter::boundingRect()����
	//�������⣬�������µ�����boundingRect
	void ajustBoundingRect(const QRectF &rect, const QString &text, int flags, const QFontMetricsF& fm, QRectF &rectBounds);

private:
	Q_DISABLE_COPY(QPainterEx)
	QPen m_strokePen;
};

#endif // QPAINTEREX_H
