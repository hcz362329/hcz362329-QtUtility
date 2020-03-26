#include "stdafx.h"
#include "EquipSchemeBtn.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

EquipSchemeBtn::EquipSchemeBtn(int nSchemeNo,QWidget* parent /* = 0 */)
	: QPushButton(parent)
	, m_eSide(eSideNone)
	, m_LESchemeName(nullptr)
	, m_pEditBtn(nullptr)
{
	m_strSchemeUINo = QString::number(nSchemeNo);

	m_pEditBtn = new QPushButton(this);
	m_pEditBtn->setGeometry(3,13,20,20);
	m_pEditBtn->setObjectName("EquipmentSchemeNameEditBtn");
	connect(m_pEditBtn,SIGNAL(clicked()),this,SLOT(OnEditBtnClicked()));

	QFont font;
	font.setFamily("FZZhengHeiS-M-GB");
	font.setPixelSize(14);
	m_LESchemeName = new QLineEdit(this);
	m_LESchemeName->setStyleSheet("background-color:rgba(255,255,255,0);color:rgb(255,255,255);border: 0px solid rgba(255,255,255,0);");
	m_LESchemeName->setGeometry(23,13,100,20);
	m_LESchemeName->setAlignment(Qt::AlignLeft);
	m_LESchemeName->setContextMenuPolicy(Qt::NoContextMenu);
	m_LESchemeName->installEventFilter(this);
	m_LESchemeName->setReadOnly(true);
	//方案名称变化信号槽
	connect(m_LESchemeName,SIGNAL(textChanged(const QString &)),this,SLOT(OnTextChanged(const QString &)));
	//m_LESchemeName->hide();
}

EquipSchemeBtn::~EquipSchemeBtn()
{

}

void EquipSchemeBtn::OnEditBtnClicked()
{
	if ( m_LESchemeName != nullptr )
	{
		m_LESchemeName->show();
		m_LESchemeName->setReadOnly(false);
		m_LESchemeName->setFocus();
		m_LESchemeName->selectAll();
	}
}

void EquipSchemeBtn::OnTextChanged(const QString & text)
{
	qDebug()<<"text:"<<text;
	QString strText;
	if ( text.toLocal8Bit().length() > 15 )
	{
		QByteArray byteLocal8Bit = text.toLocal8Bit().left(15);
		strText = QString::fromLocal8Bit(byteLocal8Bit);
	}
	else
	{
		strText = text;
	}
	m_LESchemeName->setText(strText);
	m_strSchemeName = strText;
}

void EquipSchemeBtn::setSide(ESide eSide)
{
	m_eSide = eSide;
	switch (eSide)
	{
	case eSideLeft:
		{
			m_rectUINo = QRect(12,15,20,18);
		}
		break;
	case eSideRight:
		{
			m_rectUINo = QRect(rect().width()-32,17,20,18);
		}
		break;
	default:
		break;
	}
	if ( m_LESchemeName != nullptr && m_pEditBtn != nullptr )
	{
		m_pEditBtn->setVisible(m_eSide == eSideNone);
		m_LESchemeName->setVisible(eSide==eSideNone);
	}
	m_LESchemeName->setReadOnly(true);
	update();
}

void EquipSchemeBtn::setText(const QString &text)
{
	if ( m_LESchemeName != nullptr )
	{
		if (!text.isEmpty() )
		{
			m_strSchemeName = text;
			m_LESchemeName->setText(text);
		}
	}
}

bool EquipSchemeBtn::eventFilter(QObject *obj, QEvent *e)
{
	if ( obj == m_LESchemeName )
	{
		if (e->type() == QEvent::KeyPress )
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
			if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter )
			{
				if ( NULL != m_LESchemeName->text() )
				{
					OnTextChanged(m_LESchemeName->text());
					m_LESchemeName->editingFinished();
					m_LESchemeName->setReadOnly(true);
					return true;
				}
			}
		}
	}
	return QPushButton::eventFilter(obj,e);
}

void EquipSchemeBtn::paintEvent(QPaintEvent *e)
{
	QPushButton::paintEvent(e);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QFont font;
	font.setFamily("FZZhengHeiS-M-GB");
	font.setPixelSize(14);
	painter.setFont(font);
	if ( m_eSide == eSideLeft )
	{
		painter.setPen(QColor(255,255,254));
		painter.drawText(m_rectUINo,Qt::AlignLeft,m_strSchemeUINo);
	}
	else if ( m_eSide == eSideRight )
	{
		painter.setPen(QColor(255,255,254));
		painter.drawText(m_rectUINo,Qt::AlignRight,m_strSchemeUINo);
	}
	else
	{
		painter.setPen(QColor(255,255,255));
		//painter.drawText(23,13,100,20,Qt::AlignCenter,m_strSchemeName);
	}
}

QString EquipSchemeBtn::getSchemeName()
{
	return m_strSchemeName;
}