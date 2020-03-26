#include "JxDelegate.h"
#include <QPainter>
JxDelegate::JxDelegate(QObject* parent /*= NULL*/)
	: QStyledItemDelegate(parent)
	, m_eShowType(eListViewShowJX)
{
	m_pixLock.load("./Images/JiangXing/lockJX.png");
	m_pixItemBg.load("./Images/HunYuConfig_ItemBkgnd.png");
	m_pixHyItemCountBG.load("./Images/HyItemCountBG.png");
	m_pixMengBan.load("./Images/JiangXing/jxLMB.png");
	m_mapSHEngName.insert(QString::fromWCharArray(L"青龙"),QString("QingLong_64.png"));
	m_mapSHEngName.insert(QString::fromWCharArray(L"白虎"),QString("BaiHu_64.png"));
	m_mapSHEngName.insert(QString::fromWCharArray(L"朱雀"),QString("ZhuQue_64.png"));
	m_mapSHEngName.insert(QString::fromWCharArray(L"玄武"),QString("XuanWu_64.png"));
}

JxDelegate::~JxDelegate()
{

}

QSize JxDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);
	return QSize(274,91);
}

void JxDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	//将绘画压入绘画队列,压入之后解绑即恢复初始状态为下次压入做准备
	painter->save();
	/*
	if ( index.isValid() )
	{
		QFont font;
		font.setFamily("SimSun");
		font.setPixelSize(12);
		QPen pen(QColor(181,161,117));
		
		switch ( m_eShowType  )
		{
		case eListViewShowJX:
			{
				STJX stJX = qvariant_cast<STJX>(index.data(Qt::DisplayRole));
				QRect rect						= option.rect;
				QRect rectBG					= QRect(rect.left(),rect.top() + 3 ,rect.width(),rect.height() - 6);
				QRect rectJx					= QRect(rectBG.left()+23,rectBG.top() + 10 ,40,40);
				QRect rectJxName				= QRect(rectBG.left()+5,rectBG.top() + 60 ,80,15);
				QRect rectJxNum					= QRect(rectBG.left()+230,rectBG.top() + 5 ,19,19);
				QRect rectInfo1					= QRect(rectBG.left()+90,rectBG.top() + 3 ,135,24);
				QRect rectInfo2					= QRect(rectBG.left()+90,rectBG.top() + 28 ,165,24);
				QRect rectInfo3					= QRect(rectBG.left()+90,rectBG.top() + 53 ,165,24);
				//背景
				if ( !m_pixItemBg.isNull() )
				{
					painter->drawPixmap(rectBG.left(),rectBG.top(),m_pixItemBg.scaled(QSize(rectBG.width(),rectBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				//将星
				if ( !stJX.strImgPath.isNull() )
				{
					QString strJXPath64 = QString("./Images/JiangXing_64/%1.jpg").arg(stJX.strJXEng);
					painter->drawPixmap(rectJx.left(),rectJx.top(),QPixmap(strJXPath64).scaled(QSize(rectJx.width(),rectJx.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				//将星名称
				if ( !stJX.strJXName.isNull() )
				{
					painter->setPen(pen);
					painter->setFont(font);
					painter->drawText(rectJxName,Qt::AlignCenter,stJX.strJXName);
				}
				//将星属性
				QPen pentext(QColor(125, 102, 61));
				painter->setPen(pentext);
				for ( int nIndex = 0 ; nIndex < stJX.vecEff.size(); ++nIndex )
				{
					font.setPixelSize(11);
					painter->setFont(font);
					QString strInfo;
					if (stJX.vecEff[nIndex].usEffValue > 0)
					{
						strInfo = QString("%1-%2+%3").arg(nIndex+1).arg(QString::fromLocal8Bit(stJX.vecEff[nIndex].szEffName)).arg(stJX.vecEff[nIndex].usEffValue);
					}
					else
					{
						strInfo = QString("%1-%2%3").arg(nIndex+1).arg(QString::fromLocal8Bit(stJX.vecEff[nIndex].szEffName)).arg(stJX.vecEff[nIndex].usEffValue);
					}
					if (stJX.vecEff[nIndex].usEffValueType == 2)
					{
						strInfo.append("%");
					}
					
					switch (nIndex)
					{
					case 0:
						painter->drawText(rectInfo1,Qt::AlignTop | Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					case 1:
						painter->drawText(rectInfo2,Qt::AlignTop | Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					case 2:
						painter->drawText(rectInfo3,Qt::AlignTop | Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					default:
						break;
					}
				}
				if ( stJX.nNum > 0 )
				{
					painter->drawPixmap(rectJxNum.left(),rectJxNum.top(),m_pixHyItemCountBG.scaled(QSize(rectJxNum.width(),rectJxNum.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					painter->setPen(pen);
					font.setPixelSize(12);
					painter->setFont(font);
					painter->setPen(QColor(232,204,106));
					
					painter->drawText(rectJxNum.left(),rectJxNum.top()-2,rectJxNum.width(),rectJxNum.height(),Qt::AlignCenter,QString::number(stJX.nNum));
				}
				else
				{
					//加蒙板
					painter->drawPixmap(rectBG.left(),rectBG.top(),m_pixMengBan.scaled(QSize(rectBG.width(),rectBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				if ( stJX.nLock )
				{
					//将星未开放，加锁
					painter->drawPixmap(rectBG.left(),rectBG.top(),m_pixMengBan.scaled(QSize(rectBG.width(),rectBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					painter->drawPixmap(rectJx.left(),rectJx.top(),m_pixLock.scaled(QSize(rectJx.width(),rectJx.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
			}
			break;
		case eListViewShowSH:
			{
				STSH stSH = qvariant_cast<STSH>(index.data(Qt::DisplayRole));
				QRect rect						= option.rect;
				QRect rectBG					= QRect(rect.left(),rect.top() + 3 ,rect.width(),rect.height() - 6);
				QRect rectSH					= QRect(rectBG.left()+24,rectBG.top() + 10 ,40,40);
				QRect rectSHName				= QRect(rectBG.left()+5,rectBG.top() + 60 ,80,15);
				QRect rectSHNum					= QRect(rectBG.left()+230,rectBG.top() + 5 ,19,19);
				QRect rectInfo1					= QRect(rectBG.left()+90,rectBG.top() + 15 ,165,15);
				QRect rectInfo2					= QRect(rectBG.left()+90,rectBG.top() + 31 ,165,15);
				QRect rectInfo3					= QRect(rectBG.left()+90,rectBG.top() + 47 ,165,15);
				//背景
				if ( !m_pixItemBg.isNull() )
				{
					painter->drawPixmap(rectBG.left(),rectBG.top(),m_pixItemBg.scaled(QSize(rectBG.width(),rectBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				//兽魂
				if ( !stSH.strSHName.isNull() )
				{
					QString strPath = QString("./Images/ShouHun/%1").arg(m_mapSHEngName[stSH.strSHName]);
					painter->drawPixmap(rectSH.left(),rectSH.top(),QPixmap(strPath).scaled(QSize(rectSH.width(),rectSH.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				//兽魂名称
				if ( !stSH.strSHName.isNull() )
				{
					painter->setPen(pen);
					painter->setFont(font);
					painter->drawText(rectSHName,Qt::AlignCenter,stSH.strSHName);
				}
				//兽魂属性
				QPen pentext(QColor(125, 102, 61));
				painter->setPen(pentext);
				for ( int nIndex = 0 ; nIndex < stSH.vecSHEff.size(); ++nIndex )
				{
					font.setPixelSize(11);
					painter->setFont(font);
					QString strInfo;
					if (stSH.vecSHEff[nIndex].usEffValue > 0)
					{
						strInfo = QString("%1-%2+%3").arg(nIndex+1).arg(QString::fromLocal8Bit(stSH.vecSHEff[nIndex].szEffName)).arg(stSH.vecSHEff[nIndex].usEffValue);
					}
					else
					{
						strInfo = QString("%1-%2%3").arg(nIndex+1).arg(QString::fromLocal8Bit(stSH.vecSHEff[nIndex].szEffName)).arg(stSH.vecSHEff[nIndex].usEffValue);
					}
					if (stSH.vecSHEff[nIndex].usEffValueType == 2)
					{
						strInfo.append("%");
					}
					switch (nIndex)
					{
					case 0:
						painter->drawText(rectInfo1,Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					case 1:
						painter->drawText(rectInfo2,Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					case 2:
						painter->drawText(rectInfo3,Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,strInfo);
						break;
					default:
						break;
					}
				}
				if ( stSH.nNum > 0 )
				{
					painter->drawPixmap(rectSHNum.left(),rectSHNum.top(),m_pixHyItemCountBG.scaled(QSize(rectSHNum.width(),rectSHNum.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					painter->setPen(QColor(232,204,106));
					font.setPixelSize(12);
					painter->setFont(font);
					painter->drawText(rectSHNum.left(),rectSHNum.top()-2,rectSHNum.width(),rectSHNum.height(),Qt::AlignCenter,QString::number(stSH.nNum));
				}
				
			}
			break;
		}
	}
	*/
	painter->restore();
}

void JxDelegate::setSelectJX(STJX stJX)
{
	m_stJXSelect = stJX;
}

void JxDelegate::setListViewShowType(EListViewShowType eListViewShowType)
{
	m_eShowType = eListViewShowType;
}

EListViewShowType JxDelegate::getListViewShowType()
{
	return m_eShowType;
}