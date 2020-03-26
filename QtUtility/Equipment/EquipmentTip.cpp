#include "stdafx.h"
#include "EquipmentTip.h"
#include <QPainter>
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>

EquipmentTip::EquipmentTip(QWidget* parent /* = 0 */)
	: QWidget(parent)
	, m_pItemDesc(nullptr)
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::ToolTip);
	//setAttribute(Qt::WA_TranslucentBackground);
	bool bLoad = m_pixBG.load("./Images/Setting/QxEquipment/EquipmentTipBG.png");
	resize(m_pixBG.width(),m_pixBG.height());
	bool bLoad3 = m_pixCost.load("./Images/Setting/QxEquipment/Money.png");

	m_pItemDesc = new QTextEdit(this);
	m_pItemDesc->setGeometry(16, 81, 240, 30);
	m_pItemDesc->setReadOnly(true);
	m_pItemDesc->setContextMenuPolicy(Qt::NoContextMenu);
	m_pItemDesc->setWordWrapMode(QTextOption::WrapAnywhere);
	m_pItemDesc->setLineWrapMode(QTextEdit::FixedPixelWidth);
	m_pItemDesc->setLineWrapColumnOrWidth(240);
	m_pItemDesc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pItemDesc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pItemDesc->setStyleSheet("background:transparent;border: 0px;font-family: 'FZZhengHeiS-M-GB';color:#d0d0d0;");
}

EquipmentTip::~EquipmentTip()
{

}

void EquipmentTip::setEquipmentInfo(const STEquipment& stEquipment)
{
	if ( stEquipment.iEquipmentId <= 0 )
	{
		hide();
	}
	memset(&m_stEquipment,0,sizeof(m_stEquipment));
	m_stEquipment = stEquipment;
	//根据ItemId获取Item信息
#if 0
	m_stItem = CQxLogicalAPIHelper<>::GetItemById(m_stEquipment.iEquipmentId);

	bool bLoad2 = m_pixIcon.load(QString::fromStdWString(m_stItem.strItemIcon));
	QString strDesc = QString::fromStdWString(m_stItem.strItemDesc);
	strDesc = strDesc.trimmed();
	stringToHtml(strDesc);

	m_pItemDesc->setText(strDesc);

	int nLineDistanceHeight = 2;
	QTextDocument *pDoc = m_pItemDesc->document();
	for (QTextBlock block = pDoc->begin(); block.isValid(); block = block.next())
	{
		QTextCursor tc(block);
		QTextBlockFormat fmt = block.blockFormat();
		fmt.setLineHeight(nLineDistanceHeight, QTextBlockFormat::LineDistanceHeight);
		tc.setBlockFormat(fmt);
	}

	QRect boundingRect = m_pItemDesc->fontMetrics().boundingRect(QRect(16, 81, 240, 0), 
		Qt::TextWordWrap, strDesc);

	int nLineCount = 0;
	int nLineSpacing = m_pItemDesc->fontMetrics().lineSpacing();
	if (nLineSpacing > 0)
	{
		if (boundingRect.height() % nLineSpacing == 0)
		{
			nLineCount = boundingRect.height() / nLineSpacing;
		}
		else
		{
			nLineCount = (boundingRect.height()+nLineDistanceHeight) / nLineSpacing;
		}
	}

	m_pItemDesc->resize(240, boundingRect.height() + nLineCount * nLineDistanceHeight);
	update();
	resize(270, 107 + boundingRect.height());
#endif
}

void EquipmentTip::stringToHtml(QString &str)
{
	str.replace("\n","<br />");
}

void EquipmentTip::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(rect(), QBrush(QColor("#1b1514")));

	QPen pen(QColor("#8e846c"));
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawRect(rect());

	if ( strlen(m_stEquipment.strItemName) )
	{
		//加载图片
		if ( !m_pixIcon.isNull() )
		{
			painter.drawPixmap(17,14,m_pixIcon.scaled(QSize(44,44),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		}
		if ( !m_pixCost.isNull() )
		{
			painter.drawPixmap(70,36,m_pixCost.scaled(QSize(m_pixCost.width(),m_pixCost.height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		}
	}

	QFont font;
	font.setFamily(QStringLiteral("FZZhengHeiS-M-GB"));
	font.setPixelSize(16);
	painter.setFont(font);
	painter.setPen(QColor("#ffcc00"));

	painter.drawText(QRect(69,15,100,18), QString::fromLocal8Bit(m_stEquipment.strEquipmentName), 
		QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
#if 0
	font.setPixelSize(14);
	painter.setFont(font);
	painter.drawText(QRect(99,41,100,16), QString::number(m_stItem.uiPrice), 
		QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
#endif
	
}