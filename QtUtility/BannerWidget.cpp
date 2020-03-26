#include <QPainter>
#include <QTimerEvent>
#include <QFont>
#include "BannerWidget.h"
#include "qpainterex.h"
BannerWidget::BannerWidget(QWidget *parent)
	: QWidget(parent),
	m_nStep(0),
	m_strText(QString::fromLocal8Bit("�ı���ɫHSV"))
{
	setAutoFillBackground(true);

	// �������ִ�С
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
	// �����ı����Ƶ���ʼ����
	QFontMetrics metrics(font());
	int x = (width() - metrics.width(m_strText)) / 2;
	int y = (height() + metrics.ascent() - metrics.descent()) / 2;
#if 0
	QColor color;
	for (int i = 0; i < m_strText.size(); ++i)
	{
		// ����ɫ����H�������Ͷȣ�S�������ȣ�V��
		int nIndex = (m_nStep + i) % 16;
		color.setHsv((15 - nIndex) * 16, 255, 191);
		painter.setPen(color);

		// �����ַ�����
		//painter.drawText(rcText,Qt::AlignLeft, QString::fromWCharArray(L"���ƶԷ����أ����ɻ��ʤ��"));

		painter.drawText(x, y, QString(m_strText[i]));

		// ������һ���ַ���x������ʼ��
		x += metrics.width(m_strText[i]);
	}
#else
	QRect rcText(100, 174, 300, 50);
	QString strName1 = QString::fromWCharArray(L"����С�����");
	QFont font(strName1);
	
	font.setPixelSize(20);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor("#AC9369"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));

	painter.drawStrokeText(rcText,QString::fromWCharArray(L"����"), QTextOption(Qt::AlignRight | Qt::AlignTop));
#endif
	
	
#if 0
	QRect rcText(100, 174, 300, 50);
	QFont font;
	font.setPixelSize(20);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor("#AC9369"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));

	painter.drawStrokeText(rcText,QString::fromWCharArray(L"����"), QTextOption(Qt::AlignRight | Qt::AlignTop));
#endif
	
	
	//painter.drawText(x, y-50, QString::fromLocal8Bit("�ı���ɫHSV"));
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