#include <QPainter>
#include <QTimerEvent>
#include <QFont>
#include "BannerWidget.h"
#include "qpainterex.h"
BannerWidget::BannerWidget(QWidget *parent)
	: QWidget(parent),
	m_nStep(0),
	m_strText(QString::fromLocal8Bit("文本颜色HSV"))
{
	setAutoFillBackground(true);

	// 设置文字大小
	QFont newFont = font();
	newFont.setPointSize(newFont.pointSize() + 20);
	setFont(newFont);

	m_timer.start(100, this);
}

BannerWidget::~BannerWidget()
{
	m_timer.stop();
}

void BannerWidget::setText(const QString &text)
{
	m_strText = text;
}

void BannerWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
#if 1
	QPainterEx painter(this);
#endif
	//QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	// 计算文本绘制的起始坐标
	QFontMetrics metrics(font());
	int x = (width() - metrics.width(m_strText)) / 2;
	int y = (height() + metrics.ascent() - metrics.descent()) / 2;
#if 0
	QColor color;
	for (int i = 0; i < m_strText.size(); ++i)
	{
		// 设置色调（H）、饱和度（S）、亮度（V）
		int nIndex = (m_nStep + i) % 16;
		color.setHsv((15 - nIndex) * 16, 255, 191);
		painter.setPen(color);

		// 单个字符绘制
		//painter.drawText(rcText,Qt::AlignLeft, QString::fromWCharArray(L"击破对方基地，即可获得胜利"));

		painter.drawText(x, y, QString(m_strText[i]));

		// 计算下一个字符的x坐标起始点
		x += metrics.width(m_strText[i]);
	}
#else
	QRect rcText(100, 174, 300, 50);
	QString strName1 = QString::fromWCharArray(L"汉仪小隶书简");
	QFont font(strName1);
	
	font.setPixelSize(20);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor("#AC9369"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));

	painter.drawStrokeText(rcText,QString::fromWCharArray(L"关羽"), QTextOption(Qt::AlignRight | Qt::AlignTop));
#endif
	
	
#if 0
	QRect rcText(100, 174, 300, 50);
	QFont font;
	font.setPixelSize(20);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor("#AC9369"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));

	painter.drawStrokeText(rcText,QString::fromWCharArray(L"关羽"), QTextOption(Qt::AlignRight | Qt::AlignTop));
#endif
	
	
	//painter.drawText(x, y-50, QString::fromLocal8Bit("文本颜色HSV"));
}

void BannerWidget::timerEvent(QTimerEvent *event)
{
	Q_UNUSED(event);

	if (event->timerId() == m_timer.timerId())
	{
		++m_nStep;
		update();
	}
	else
	{
		QWidget::timerEvent(event);
	}
}