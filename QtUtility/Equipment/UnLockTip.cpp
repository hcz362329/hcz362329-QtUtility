#include "stdafx.h"
#include "UnLockTip.h"
//#include "Log4cplusWrapper.h"
#include <QPainter>

UnLockTip * UnLockTip::g_instance=NULL;

UnLockTip::UnLockTip(QWidget* parent)
	: QWidget(parent)
	, m_uiSlotId(0)
{
	g_instance = this;
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::ToolTip);
	//setAttribute(Qt::WA_TranslucentBackground);
	resize(170,100);
}

UnLockTip::~UnLockTip()
{
	g_instance = nullptr;
}

UnLockTip * UnLockTip::GetInstance()
{
	if ( g_instance == NULL )
	{
		new UnLockTip();
	}
	return g_instance;
}

void UnLockTip::DeleteInstance()
{
	delete g_instance;
	g_instance = nullptr;
}

void UnLockTip::UpdateInfo(QString strTitle,QString strContent,QString strLockState)
{
	////LOG_FUN("");

	m_strTitle			=strTitle;
	m_strContent		=strContent;
	m_strLockState		=strLockState;
	////LOG_INFO("m_strTitle:"<<m_strTitle.toStdWString()<<",m_strContent:"<<m_strContent.toStdWString()<<",m_strLockState:"<<m_strLockState.toStdWString());
	update();
}

void UnLockTip::SetLockState(QString strLockState)
{
	m_strLockState =strLockState;
	update();
}

void UnLockTip::SetSlotId(int uiSlotId)
{
	m_uiSlotId = uiSlotId;
}
int UnLockTip::GetSlotId()
{
	return m_uiSlotId;
}

void UnLockTip::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(rect(), QBrush(QColor("#1b1514")));
	QPen pen(QColor("#8e846c"));
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawRect(rect());

	QFont font("FZZhengHeiS-M-GB");
	font.setPixelSize(16);
	painter.setFont(font);
	painter.setPen(QColor("#f5a238"));
	QRect boundingRect = painter.fontMetrics().boundingRect(QRect(10, 10, 0, 0), Qt::TextSingleLine, m_strTitle);
	painter.drawText(boundingRect,Qt::AlignLeft,m_strTitle);

	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen(QColor("#c9b696"));
	QRect boundingRect2 = painter.fontMetrics().boundingRect(QRect(11, 36, 0, 0), Qt::TextSingleLine, m_strContent);
	painter.drawText(boundingRect2,Qt::AlignLeft,m_strContent);

	QRect boundingRect3 = painter.fontMetrics().boundingRect(QRect(11, 73, 0, 0), Qt::TextSingleLine, QStringLiteral("×´Ì¬£º"));
	painter.drawText(boundingRect3,Qt::AlignLeft,QStringLiteral("×´Ì¬£º"));
	painter.setPen(QColor("#2cad46"));
	QRect boundingRect4 = painter.fontMetrics().boundingRect(QRect(boundingRect3.right()+5, 73, 0, 0), Qt::TextSingleLine, m_strLockState);
	painter.drawText(boundingRect4,Qt::AlignLeft,m_strLockState);
}