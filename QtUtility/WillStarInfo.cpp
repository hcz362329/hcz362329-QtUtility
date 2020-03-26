#include "WillStarInfo.h"
#include <QPainter>
#include <QDebug>

#define RC_DIR QStringLiteral("./resources/skin/1/myhero/Awaken/")

WillStarInfo::WillStarInfo(QWidget* parent )
	: QWidget(parent)
	, m_pTitle(nullptr)
{
	QString strBg = RC_DIR+"bg_jiangxing.png";
	bool bLoad=m_pixBg.load(RC_DIR+"bg_jiangxing.png");
	if (!bLoad)
	{
		qDebug()<<"pixmap not exist:bg_jiangxing.png\n";
	}
	else
	{
		resize(m_pixBg.width(),m_pixBg.height());
	}
	m_pixJx1Bg.load(RC_DIR+"bg_jiangxing1.png");
	m_pixJx2Bg.load(RC_DIR+"bg_jiangxing2.png");
	m_pTitle = new QLabelPainter(this);
	m_pTitle->setGeometry(21,10,60,20);
	QString strFamily = QString::fromWCharArray(L"ººÒÇÐ¡Á¥Êé¼ò");
	STRenderText stRenderText;
	stRenderText.strFamilyName = strFamily;
	stRenderText.font_size = 18;
	stRenderText.bold = true;
	stRenderText.text_color = QColor(242,221,186);
	stRenderText.strRenderText = QString::fromWCharArray(L"½« ÐÇ");
	stRenderText.is_TextFlag = true;
	stRenderText.flag = Qt::AlignLeft;
	m_pTitle->SetRenderText(stRenderText);
	
}


WillStarInfo::~WillStarInfo()
{

}

void WillStarInfo::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if ( !m_pixBg.isNull() )
	{
		painter.drawPixmap(0,0,m_pixBg);
	}
	if ( !m_pixJx1Bg.isNull() )
	{
		painter.drawPixmap(12,56,m_pixJx1Bg);
	}
	if ( !m_pixJx2Bg.isNull() )
	{
		painter.drawPixmap(16,312,m_pixJx2Bg);
	}
}