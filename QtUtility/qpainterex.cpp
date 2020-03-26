#include "qpainterex.h"
#include <QDebug>

QPainterEx::QPainterEx(QPaintDevice *device)
	: QPainter(device)
{
}

QPainterEx::~QPainterEx()
{
}

void QPainterEx::setStrokePen(const QPen& pen)
{
	m_strokePen = pen;
}

void QPainterEx::drawStrokeText(const QRectF &r, const QString &text, const QTextOption &o)
{
	if (text.isEmpty() || pen().style() == Qt::NoPen)
		return;

	save();
	setClipRect(r);

	const QPen& oldpen = pen();
	setBrush(QBrush(oldpen.color()));
	setPen(Qt::NoPen);

	const QFont& fnt = font();
	QFontMetricsF fm(fnt);

	QTextOption::WrapMode mode = o.wrapMode();

	//需要换行显示
	if ((mode & ~QTextOption::NoWrap) &&
		(mode & ~QTextOption::ManualWrap))
	{
		QString temp2 = text;
		QStringList strReplaceList = temp2.split("\n");
		QString textCheck;//可以显示的所有字

		//逐行取文字
		QStringList lstTexts;
		QString singleLineText;
		int line = 0;

		int nMaxLine = r.height() / fm.height();
		if ((int)r.height() % (int)fm.height() > 0)
			nMaxLine++;
		for ( int i = 0 ; i < strReplaceList.size() ; ++i )
		{
			QString temp = strReplaceList[i];
			while (temp.length() > 0)
			{
				if (fm.width(temp) <= r.width())
				{
					singleLineText = temp;
					lstTexts.append(singleLineText);
					textCheck.append(singleLineText);
					line++;
					break;
				}
				else
				{
					for (int pos = 1; pos <= temp.length(); ++pos)
					{
						QString& str = temp.left(pos);
						if (fm.width(str) > r.width())
						{
							if (pos>1)
							{
								singleLineText = temp.left(pos-1);
								lstTexts.append(singleLineText);
								textCheck.append(singleLineText);
								line++;

								int right = temp.length()-pos+1;
								temp = temp.right(right);
							}
							break;
						}
					}
				}

				if (line >= nMaxLine)
					break;
			}
		}
		//qDebug() << lstTexts << textCheck;

		QRectF br = boundingRect(r, textCheck, o);
		br.setHeight(fm.height());
		//qDebug() << rt;

		foreach (const QString &str, lstTexts)
		{
			const QRectF& bounds = boundingRect(br, str, o);

			QPoint pnt;
			pnt.setX(bounds.left());
			pnt.setY(bounds.top() + fm.ascent());

			QPainterPath path;
			//path.setFillRule(Qt::WindingFill);
			path.addText(pnt, fnt, str);

			if (m_strokePen.style() == Qt::NoPen)
			{
				m_strokePen = oldpen;
			}
			strokePath(path, m_strokePen);
			//fillPath(path, brush());
			drawPath(path);

			br.moveTop(br.top() + fm.height());
		}
	}
	else //不换行
	{
		const QRectF& bounds = boundingRect(r, text, o);
		//qDebug() << r << bounds;

		QPoint pnt;
		pnt.setX(bounds.left());
		pnt.setY(bounds.top() + fm.ascent());

		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addText(pnt, fnt, text);

		if (m_strokePen.style() == Qt::NoPen)
		{
			m_strokePen = oldpen;
		}
		 
		//fillPath(path, brush());
		drawPath(path);
	}

	restore();
}

void QPainterEx::drawText(const QRectF &r, const QString &text, const QTextOption &o)
{
	if (text.isEmpty() || pen().style() == Qt::NoPen)
		return;

	save();
	setClipRect(r);

	const QPen& oldpen = pen();
	setBrush(QBrush(oldpen.color()));
	setPen(Qt::NoPen);

	const QFont& fnt = font();
	QFontMetricsF fm(fnt);

	QTextOption::WrapMode mode = o.wrapMode();

	//需要换行显示
	if ((mode & ~QTextOption::NoWrap) &&
		(mode & ~QTextOption::ManualWrap))
	{
		QString temp2 = text;
		QStringList strReplaceList = temp2.split("\n");
		QString textCheck;//可以显示的所有字

		//逐行取文字
		QStringList lstTexts;
		QString singleLineText;
		int line = 0;

		int nMaxLine = r.height() / fm.height();
		if ((int)r.height() % (int)fm.height() > 0)
			nMaxLine++;
		for ( int i = 0 ; i < strReplaceList.size() ; ++i )
		{
			QString temp = strReplaceList[i];
			while (temp.length() > 0)
			{
				if (fm.width(temp) <= r.width())
				{
					singleLineText = temp;
					lstTexts.append(singleLineText);
					textCheck.append(singleLineText);
					line++;
					break;
				}
				else
				{
					for (int pos = 1; pos <= temp.length(); ++pos)
					{
						QString& str = temp.left(pos);
						if (fm.width(str) > r.width())
						{
							if (pos>1)
							{
								singleLineText = temp.left(pos-1);
								lstTexts.append(singleLineText);
								textCheck.append(singleLineText);
								line++;

								int right = temp.length()-pos+1;
								temp = temp.right(right);
							}
							break;
						}
					}
				}

				if (line >= nMaxLine)
					break;
			}
		}
		//qDebug() << lstTexts << textCheck;

		QRectF br = boundingRect(r, textCheck, o);
		br.setHeight(fm.height());
		//qDebug() << rt;

		foreach (const QString &str, lstTexts)
		{
			const QRectF& bounds = boundingRect(br, str, o);

			QPoint pnt;
			pnt.setX(bounds.left());
			pnt.setY(bounds.top() + fm.ascent());

			QPainterPath path;
			path.setFillRule(Qt::WindingFill);
			path.addText(pnt, fnt, str);
			drawPath(path);

			br.moveTop(br.top() + fm.height());
		}
	}
	else //不换行
	{
		const QRectF& bounds = boundingRect(r, text, o);
		//qDebug() << r << bounds;

		QPoint pnt;
		pnt.setX(bounds.left());
		pnt.setY(bounds.top() + fm.ascent());

		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addText(pnt, fnt, text);
		drawPath(path);
	}

	restore();
}

void QPainterEx::drawText(const QRectF &r, int flags, const QString &text, QRectF *br)
{
	if (text.isEmpty() || pen().style() == Qt::NoPen)
		return;

	save();
	setClipRect(r);

	const QPen& oldpen = pen();
	setBrush(QBrush(oldpen.color()));
	setPen(Qt::NoPen);

	const QFont& fnt = font();
	QFontMetricsF fm(fnt);

	//需要换行显示
	if (flags & Qt::TextWordWrap ||
		flags & Qt::TextWrapAnywhere )
	{
		QString temp2 = text;
		QStringList strReplaceList = temp2.split("\n");

		QString textCheck;//可以显示的所有字

		//逐行取文字
		QStringList lstTexts;
		QString singleLineText;
		int line = 0;

		int nMaxLine = r.height() / fm.height();
		if ((int)r.height() % (int)fm.height() > 0)
			nMaxLine++;

		for ( int i = 0 ; i < strReplaceList.size() ; ++i )
		{
			QString temp = strReplaceList[i];
			while (temp.length() > 0)
			{
				if (fm.width(temp) <= r.width())
				{
					singleLineText = temp;
					lstTexts.append(singleLineText);
					textCheck.append(singleLineText);
					line++;
					break;
				}
				else
				{
					for (int pos = 1; pos <= temp.length(); ++pos)
					{
						QString& str = temp.left(pos);
						if (fm.width(str) > r.width())
						{
							if (pos>1)
							{
								singleLineText = temp.left(pos-1);
								lstTexts.append(singleLineText);
								textCheck.append(singleLineText);
								line++;

								int right = temp.length()-pos+1;
								temp = temp.right(right);
							}
							break;
						}
					}
				}

				if (line >= nMaxLine)
					break;
			}
		}
		int fontHeight = this->fontMetrics().height();
		int lineHeight = this->fontMetrics().lineSpacing();
		QRect rect(r.left(),r.top(),r.width(),r.height());
		int offsetY = 0 ;
		for ( int i = 0 ; i < lstTexts.size();++i )
		{
			if (flags&Qt::AlignTop)
			{
				offsetY=i*lineHeight+fontMetrics().ascent();
			}
			else 
			{
				offsetY=i*lineHeight+fontMetrics().ascent()+(r.height()-lstTexts.size()*lineHeight)/2;
			}
			
			QString strText = lstTexts[i];
			QRect boud_rect= fontMetrics().boundingRect(QRect(rect.left() , rect.top()+offsetY, rect.width(), lineHeight), flags, strText);
			QPainterPath path;
			path.setFillRule(Qt::WindingFill);
			path.addText(QPoint(boud_rect.left(),boud_rect.top()), font(), lstTexts[i]);
			drawPath(path);
		}
	}
	else //不换行
	{
		QRectF bounds = boundingRect(r, flags, text);
		if (!bounds.isValid())
		{
			ajustBoundingRect(r, text, flags, fm, bounds);
		}

		//qDebug() << r << bounds;

		QPoint pnt;
		pnt.setX(bounds.left());
		pnt.setY(bounds.top() + fm.ascent());

		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addText(pnt, fnt, text);
		drawPath(path);

		if (br != 0)
		{
			*br = bounds.toAlignedRect();
		}
	}

	restore();
}

void QPainterEx::ajustBoundingRect(const QRectF &rect, const QString &text, int flags, const QFontMetricsF& fm, QRectF &rectBounds)
{
	if (!rectBounds.isValid())
	{
		rectBounds.setWidth(fm.width(text));
		
		int nLineCount = 1;
		if (fm.width(text) > rect.width())
		{
			nLineCount = fm.width(text) / rect.width();
			if ((int)fm.width(text) % (int)rect.width() != 0)
			{
				nLineCount++;
			}
		}
		rectBounds.setHeight(fm.height()*nLineCount + fm.leading()*(nLineCount-1));

		if (flags & Qt::AlignHCenter)
		{
			int nXoffset = (rect.width() - fm.width(text))/2;
			rectBounds.moveLeft(rect.left() + nXoffset);
		}
		else
		{
			if (flags & Qt::AlignRight)
			{
				rectBounds.moveRight(rect.right());
			}
			else
			{
				rectBounds.moveLeft(rect.left());
			}
		}

		if (flags & Qt::AlignVCenter)
		{
			int nYoffset = (rect.height() - fm.height())/2;
			rectBounds.moveTop(rect.top() + nYoffset);
		}
		else
		{
			if (flags & Qt::AlignBottom)
			{
				rectBounds.moveBottom(rect.bottom());
			}
			else
			{
				rectBounds.moveTop(rect.top());
			}
		}
	}
}

void QPainterEx::drawText(const QPointF &p, const QString &str, int tf, int justificationPadding)
{
	Q_UNUSED(tf);
	if (p.isNull() || str.isEmpty())
		return;

	save();

	const QPen& oldpen = pen();
	setBrush(QBrush(oldpen.color()));
	setPen(Qt::NoPen);

	QFont fnt = font();
	QFontMetricsF fm(fnt);

	int width = fm.width(str);
	if (justificationPadding > 0)
	{
		qreal factor = (qreal)justificationPadding/(qreal)width + 1;
		fnt.setLetterSpacing(QFont::AbsoluteSpacing, factor);
	}
	const QRectF& bounds = QRectF(p.x(), p.y(), width, fm.height());

	QPoint pnt;
	pnt.setX(bounds.left());
	pnt.setY(bounds.top());

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addText(pnt, fnt, str);
	drawPath(path);

	restore();
}

void QPainterEx::drawText(const QPointF &p, const QString &s)
{
	drawText(p, s, 0, 0);
}

void QPainterEx::drawText(const QRect &r, int flags, const QString &text, QRect *br)
{
	drawText(QRectF(r), flags, text, (QRectF *)br);
}

inline void QPainterEx::drawText(const QPoint &p, const QString &s)
{
	drawText(QPointF(p), s);
}

inline void QPainterEx::drawText(int x, int y, const QString &s)
{
	drawText(QPointF(x, y), s);
}

inline void QPainterEx::drawText(int x, int y, int w, int h, int flags, const QString &text, QRect *br)
{
	drawText(QRect(x, y, w, h), flags, text, br);
}
