#include "stdafx.h"
#include "RecommandSchemeItem.h"
//#include "Log4cplusWrapper.h"
//#include "QxLobbyAPIHelper.hpp"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDir>
#include "QxEquipment.h"

#define RecommandSchemeItem_Select_Flag_Enabled 0

RecommandSchemeItem::RecommandSchemeItem(QWidget* parent /*= NULL*/)
	: EquipmentBase(parent)
	, m_pApplySchemeBtn(nullptr)
{
	setMouseTracking(true);
	initCtrls();
	m_strSchemeName = QString::fromWCharArray(L"推荐方案");
}

RecommandSchemeItem::~RecommandSchemeItem()
{

}

void RecommandSchemeItem::setSchemeId(int nRank)
{
	m_nRank = nRank;
	bool bLoad = m_pixRankBG.load(QString("./Images/Setting/QxEquipment/RecommandRank_%1.png").arg(nRank));
	//qDebug()<<"bLoad="<<bLoad;
}

void RecommandSchemeItem::initCtrls()
{
	m_pixBG.load("./Images/Setting/QxEquipment/RecommandModuleBG.png");
	m_pixBorder.load("./Images/Setting/QxEquipment/QxEquipmentBorder.png");
	m_pixSelect.load("./Images/Setting/QxEquipment/QxEquipmentSelect.png");
	m_pixEquipmentSlotBG.load("./Images/Setting/QxEquipment/1_9.png");

	m_pApplySchemeBtn = new QPushButton(this);
	//m_pApplySchemeBtn->setClickSound(QDir::currentPath()+"/Sound/btn_mus_normalclick.wav");
	m_pApplySchemeBtn->setGeometry(502,7,60,22);
	m_pApplySchemeBtn->setObjectName("EquipmentApplySchemeBtn");
	connect(m_pApplySchemeBtn,SIGNAL(clicked()),this,SLOT(OnApplySchemeBtnClicked()));

	for ( int nIndex = 1 ; nIndex < 10 ; ++nIndex )
	{
		STEquipmentSet stEquipmentSet;
		stEquipmentSet.iPos = nIndex;
		stEquipmentSet.rectEquipment = QRect(18 +(nIndex-1)*60,43,50,50);
		m_mapSTEquipmentSet[stEquipmentSet.iPos] = stEquipmentSet;
	}
}

void RecommandSchemeItem::setEquipmentMapInfo(const QMap<UINT,STEquipmentSet> & mapInfo)
{
	//LOG_FUN("");
	QMap<UINT,STEquipmentSet>::const_iterator iter = mapInfo.begin();
	while ( iter != mapInfo.end() )
	{
		QMap<UINT,STEquipmentSet>::iterator iterSet = m_mapSTEquipmentSet.find(iter->iPos);
		if ( iterSet != m_mapSTEquipmentSet.end() )
		{
			iterSet->iEquipmentId = iter->iEquipmentId;
			iterSet->iEquipmentEffectCost = iter->iEquipmentEffectCost;
			strcpy(iterSet->strEquipmentName,iter->strEquipmentName);
			strcpy(iterSet->strEquipmentIcon,iter->strEquipmentIcon);
			strcpy(iterSet->strEquipmentEffect,iter->strEquipmentEffect);
			strcpy(iterSet->strItemName,iter->strItemName);
		}
		++iter;
	}
}

void RecommandSchemeItem::OnApplySchemeBtnClicked()
{
	emit recomandEquipmentApply(m_mapSTEquipmentSet);
}

void RecommandSchemeItem::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	if ( !m_pixBG.isNull() )
	{
		painter.drawPixmap(0,0,m_pixBG);
	}
	if ( !m_pixRankBG.isNull() )
	{
		//painter.drawPixmap(20,20,m_pixRankBG.scaled(QSize(m_pixRankBG.width(),m_pixRankBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
	QFont font;
	font.setFamily(QStringLiteral("FZZhengHeiS-M-GB"));
	font.setPixelSize(14);
	painter.setFont(font);
	painter.setPen(QColor("#f5a238"));
	painter.drawText(15,22,m_strSchemeName);
	//装备背景底图显示
	painter.drawPixmap(18,43,m_pixEquipmentSlotBG.scaled(QSize(m_pixEquipmentSlotBG.width(),m_pixEquipmentSlotBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		
		//装备显示
		if ( iter->iEquipmentId > 0 )
		{
			QMap<QString,QPixmap>::iterator iterIcon = m_mapEquipmentIcon.find(QString::fromLocal8Bit(iter->strEquipmentIcon));
			if ( iterIcon != m_mapEquipmentIcon.end()  )
			{
				painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),iterIcon->scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			}
			else
			{
				QPixmap pix;
				QString strIcon = QString::fromLocal8Bit(iter->strEquipmentIcon);
				bool bLoad = pix.load(strIcon);
				if ( bLoad )
				{
					m_mapEquipmentIcon[QString::fromLocal8Bit(iter->strEquipmentIcon)] = pix;
					painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),pix.scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				else
				{
					qDebug()<<"load pixmap in m_mapEquipmentIcon:failed!";
				}
			}
			painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),m_pixBorder.scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		}
		
		iter++;
	}
	//选中装备标识
	if ( m_stEquipmentSet.iPos > 0 )
	{
#if RecommandSchemeItem_Select_Flag_Enabled
		painter.drawPixmap(m_stEquipmentSet.rectEquipment.left(),m_stEquipmentSet.rectEquipment.top(),m_pixSelect.scaled(QSize(m_stEquipmentSet.rectEquipment.width(),m_stEquipmentSet.rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
#endif
	}
}

void RecommandSchemeItem::mousePressEvent(QMouseEvent *event)
{
	//推荐装备上的点击处理
	recommandEquipmentPressed(event);
	EquipmentBase::mousePressEvent(event);
}

void RecommandSchemeItem::leaveEvent(QEvent *event)
{
	QxEquipment::getInstance()->hideEquipmentTip();
	EquipmentBase::leaveEvent(event);
}

void RecommandSchemeItem::mouseMoveEvent(QMouseEvent *event)
{
	if ( event->buttons() & Qt::LeftButton && m_stEquipmentSet.iEquipmentId > 0 )
	{
		//推荐装备的拖拽 数据 传输方式 载体 QMimeData
		int distance = (event->pos() - m_pointDrag).manhattanLength();
		//判定移动距离 Qt移动默认值:10 pixels
		if (distance >= QApplication::startDragDistance())
		{
			//内存数据获取
			STEquipment stEquipment = (STEquipment&)m_stEquipmentSet;
			QMimeData* mimeData = new QMimeData;
			QByteArray equipData;
			//追加方式保存数据进入QByteArray
			equipData.append((char*)&stEquipment,sizeof(stEquipment));
			
			mimeData->setData(QxEquipment_Drag_Data_Type,equipData);

			QString strPixmap = QString::fromLocal8Bit(stEquipment.strEquipmentIcon);
			QPixmap pixmap;
			pixmap.load(strPixmap);
			QPixmap pixResize = pixmap.scaled(QSize(44,44),Qt::KeepAspectRatio,Qt::SmoothTransformation);
			QPoint ptSpot = QPoint(pixResize.width() / 2, pixResize.height() / 2);
			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setHotSpot( ptSpot);
			drag->setPixmap(pixResize);
			drag->exec(Qt::MoveAction);
		}
	}
	LoadEquipmentInfoTip(event);
}

void RecommandSchemeItem::LoadEquipmentInfoTip(QMouseEvent *event)
{
	STEquipmentSet stEquipmentSet;
	bool bShowTip = false;
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	QPoint pos1 = event->pos();
	QPoint pointShow;
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains(event->pos()) )
		{
			stEquipmentSet = iter.value();
			bShowTip = true;
			break;
		}
		++iter;
	}
	
	int nEquipmentPos = stEquipmentSet.iPos;
	QxEquipment::getInstance()->showEquipmentTip(QPoint(95+(nEquipmentPos-1)*65,200),(STEquipment&)stEquipmentSet,bShowTip);
}

void RecommandSchemeItem::SetSchemeName(std::wstring strName)
{
	m_strSchemeName = QString::fromStdWString(strName);
	update();
}

void RecommandSchemeItem::recommandEquipmentPressed(QMouseEvent *event)
{
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->iPos > 0 && iter->rectEquipment.contains(event->pos()) )
		{
			//发送推荐装备至方案配置模块
			//RecommandSchemeItem(信号)->RecommandModule(信号)->EquipmentSetModule(信号)->EquipmentSchemeModule(响应)
			if ( event->buttons() & Qt::RightButton )
			{
				emit recomandEquipment(iter.value());
			}
			if ( event->button() * Qt::LeftButton )
			{
				m_pointDrag = event->pos();
			}
			m_stEquipmentSet = iter.value();
		}
		++iter;
	}
	update();
}

void RecommandSchemeItem::hideEvent(QHideEvent *)
{
	QxEquipment::getInstance()->hideEquipmentTip();
}