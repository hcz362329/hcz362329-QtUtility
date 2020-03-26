#include "QLabelPainter.h"


QLabelPainter::QLabelPainter(QWidget* parent)
	:QLabel(parent)
{

}


QLabelPainter::~QLabelPainter()
{

}

void QLabelPainter::SetRenderText(const STRenderText & text)
{
	m_stRenderText = text;
}

void QLabelPainter::paintEvent(QPaintEvent *e)
{
	QLabel::paintEvent(e);
	QPainterEx painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	if ( !m_stRenderText.strRenderText.isEmpty())
	{
		painter.save();

		QFont font(m_stRenderText.strFamilyName);

		font.setPixelSize(m_stRenderText.font_size);
		font.setBold(m_stRenderText.bold);
		painter.setFont(font);
		painter.setPen(m_stRenderText.text_color);
		if (m_stRenderText.is_TextFlag )
		{
			painter.drawText(rect(),m_stRenderText.flag,m_stRenderText.strRenderText);
		}
		else
		{
			painter.drawText(rect(),Qt::AlignCenter,m_stRenderText.strRenderText);
		}

		painter.restore();
	}
}