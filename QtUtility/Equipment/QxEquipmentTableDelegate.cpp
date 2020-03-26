#include "stdafx.h"
#include "QxEquipmentTableDelegate.h"
//#include "GossipSection.h"
//#include "Log4cplusWrapper.h"
#include <QPainter>
#include <QDebug>


QxEquipmentTableDelegate::QxEquipmentTableDelegate(QWidget* parent /*= NULL*/)
	: QAbstractItemDelegate(parent)
	, m_eTable(eTableEquipment)
{
	m_pixBuyNor.load("./Images/Setting/QxDevelop/buy_normal.png");
	m_pixBuyHorver.load("./Images/Setting/QxDevelop/buy_horver.png");
	m_pixBuyPressed.load("./Images/Setting/QxDevelop/buy_pressed.png");
	m_pixOwned.load("./Images/Setting/QxDevelop/owend.png");
	m_pixExample.load("./Images/Setting/QxDevelop/Icon/icon3.png");
	m_pixBanShunHuai.load("./Images/Setting/QxDevelop/bansunhuai.png");
	m_pixSunhuai.load("./Images/Setting/QxDevelop/sunhuai.png");
	m_pixMoneyIconEQ.load("./Images/Setting/QxEquipment/Money.png");
	m_pixTVLevelBG.load("./Images/Lobby/TVLevelBG.png");
	m_pixOwn.load("./Images/Setting/QxEquipment/Own.png");
	m_pixNotOwn.load("./Images/Setting/QxEquipment/NotOwn.png");
	m_pixMesh.load("./Images/Setting/mesh.png");
	m_pixLhsp.load("./Images/Setting/QxEquipment/linghunsp.png");
	m_pixSoulFragment.load("./Images/Common/SoulFragment.png");
	bool bLoad1 = m_pixZXIcon.load("./Images/Setting/QxDevelop/ZXIcon.png");
	bool bLoad2 = m_pixJLIcon.load("./Images/Setting/QxDevelop/JLIcon.png");
	bool bLoad3 = m_pixPTIcon.load("./Images/Setting/QxDevelop/PTIcon.png");
	//八卦中的16个资源识别Icon
	QPixmap pixmap;
	pixmap.load("./Images/Setting/QxDevelop/qian1.png");
	m_mapType2Item[eCSSSlot1Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/kun1.png");
	m_mapType2Item[eCSSSlot2Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/zhen1.png");
	m_mapType2Item[eCSSSlot3Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/xuan1.png");
	m_mapType2Item[eCSSSlot4Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/kan1.png");
	m_mapType2Item[eCSSSlot5Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/li1.png");
	m_mapType2Item[eCSSSlot6Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/gen1.png");
	m_mapType2Item[eCSSSlot7Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/dui1.png");
	m_mapType2Item[eCSSSlot8Open] = pixmap;

	pixmap.load("./Images/Setting/QxDevelop/tian1.png");
	m_mapType2Item[eCSSSlot9Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/tu1.png");
	m_mapType2Item[eCSSSlot10Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/mu1.png");
	m_mapType2Item[eCSSSlot11Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/feng1.png");
	m_mapType2Item[eCSSSlot12Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/shui1.png");
	m_mapType2Item[eCSSSlot13Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/huo1.png");
	m_mapType2Item[eCSSSlot14Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/shan1.png");
	m_mapType2Item[eCSSSlot15Open] = pixmap;
	pixmap.load("./Images/Setting/QxDevelop/ze1.png");
	m_mapType2Item[eCSSSlot16Open] = pixmap;
}

QxEquipmentTableDelegate::~QxEquipmentTableDelegate()
{

}

void QxEquipmentTableDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	painter->save();

	QVariant var = index.data(Qt::DisplayRole);
	if (var.isValid())
	{
		QPainter p(painter->device());
		p.setRenderHint(QPainter::Antialiasing);

		QFont font(QStringLiteral("FZZhengHeiS-M-GB"));
		font.setPixelSize(12);
		p.setPen(QColor("#c9b696"));
		p.setFont(font);

		switch (m_eTable)
		{
		case eTableEquipment:
			{
				QRect rect			= option.rect;//178,68
				QRect rectBG		= QRect(rect.left()+5,rect.top()+5,180,60);
				QRect rectIcon		= QRect(rectBG.left()+5,rectBG.top()+5,50,50);
				QRect rectName		= QRect(rectIcon.right()+10,rectBG.top()+6,85,18);
				QRect rectCost		= QRect(rectIcon.right()+30,rectBG.top()+35,70,18);
				QRect rectIconSelect= QRect(rect.left()+10,rect.top()+10,52,52);
				QRect rectMoney		= QRect(rectIcon.right()+9,rectBG.top()+38,18,14);

				const STEquipment& stEquipment = qvariant_cast<STEquipment>(var);
				if ( stEquipment.iEquipmentId > 0 )
				{
					if ( !m_pixBG.isNull() )
					{
						//painter->drawPixmap(rectBG.left(),rectBG.top(),m_pixBG.scaled(QSize(rectBG.width(),rectBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					QBrush brush("#211811");
					p.setBrush(brush);
					p.drawRect(rectBG);
					p.drawPixmap(rectMoney,m_pixMoneyIconEQ);
					QMap<QString,QPixmap>::const_iterator iter = m_mapEquipmentIcon.find(QString::fromLocal8Bit(stEquipment.strEquipmentIcon));
					if ( iter != m_mapEquipmentIcon.end() )
					{
						p.drawPixmap(rectIcon.left(),rectIcon.top(),iter->scaled(QSize(rectIcon.width(),rectIcon.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					else
					{
						QPixmap pix;
						QString strIcon = QString("./ItemIcon/")+QString::fromLocal8Bit(stEquipment.strEquipmentIcon);
						bool bLoad = pix.load(strIcon);
						if ( bLoad )
						{
							const_cast<QMap<QString,QPixmap>&>(m_mapEquipmentIcon)[QString::fromLocal8Bit(stEquipment.strEquipmentIcon)] = pix;
							p.drawPixmap(rectIcon.left(),rectIcon.top(),pix.scaled(QSize(rectIcon.width(),rectIcon.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						else
						{
							qDebug()<<"load pixmap in m_mapEquipmentIcon:failed!";
						}
					}
#if DELEGATE_PRESSED_ENABLED
					if ( m_stEquipment.iEquipmentId == stEquipment.iEquipmentId )
#else
					if ( option.state & QStyle::State_Selected )
#endif
					{
						p.drawPixmap(rectIconSelect.left(),rectIconSelect.top(),m_pixSelect.scaled(QSize(rectIconSelect.width(),rectIconSelect.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					font.setPixelSize(12);
					p.setFont(font);
					p.setPen(QColor(201,197,181));
					p.drawText(rectName,QString::fromLocal8Bit(stEquipment.strEquipmentName),QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
					font.setPixelSize(14);
					p.setFont(font);
					p.setPen(QColor(179,147,81));
					p.drawText(rectCost,QString::number(stEquipment.iEquipmentEffectCost),QTextOption(Qt::AlignLeft));
				}
			}
			break;
#if 0
		case eTableLegend:
		case eTableDevelopLegend:
			{
				QRect rect	= option.rect;

				const STEquipmentLegend& stEquipmentLegend = qvariant_cast<STEquipmentLegend>(var);
				if ( stEquipmentLegend.iLegendId > 0 )
				{
					QRect rectImg		= QRect(rect.left()+12,rect.top()+9,136,182);
					QRect rectNameImg	= QRect(rectImg.left()+3,rectImg.top()+158,77,20);
					QRect rectTVLevel   = QRect(rectImg.left()+70,rectImg.top()+152,63,35);
					QRect rectOwnOrNotOwn = QRect(rect.left()+20, rect.top()+4, 24, 70);
					QMap<DWORD,QPixmap>::const_iterator iter = m_pLegemdBigIconMap.find(stEquipmentLegend.iLegendId);
					if ( iter != m_pLegemdBigIconMap.end() )
					{
						p.drawPixmap(rectImg.left(),rectImg.top(),iter->scaled(QSize(rectImg.width(),rectImg.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					else
					{
						QPixmap pix;
						QString strNameIcon = QString::number(stEquipmentLegend.iLegendId)+QString(".jpg");
						QString str = QString("./Images/HeroSkin/HeroHead/%1").arg(strNameIcon);
						//QString str = m_mapId2Str[stEquipmentLegend.iLegendId];
						bool bLoad = pix.load(str);
						if ( bLoad )
						{
							const_cast<QMap<DWORD,QPixmap>&>(m_pLegemdBigIconMap)[stEquipmentLegend.iLegendId] = pix;
							p.drawPixmap(rectImg.left(),rectImg.top(),pix.scaled(QSize(rectImg.width(),rectImg.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						else
						{
							p.drawRect(rect);
							p.drawText(rectImg,Qt::AlignCenter ,QString::fromWCharArray(L"缺少资源:").append(QString::fromLocal8Bit(stEquipmentLegend.strLegendName)));
						}
					}

					QMap<DWORD,QPixmap>::const_iterator iter2 = m_pLegemdNameIconMap.find(stEquipmentLegend.iLegendId);
					if ( iter2 != m_pLegemdNameIconMap.end() )
					{
						p.drawPixmap(rectNameImg.left(),rectNameImg.top(),iter2->scaled(QSize(rectNameImg.width(),rectNameImg.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					else
					{
						QPixmap pix;
						QString strNameIcon = QString::number(stEquipmentLegend.iLegendId)+QString("_0.png");
						QString str = QString("./Images/HeroSkin/HeroHead/%1").arg(strNameIcon);
						bool bLoad = pix.load(str);
						if ( bLoad )
						{
							const_cast<QMap<DWORD,QPixmap>&>(m_pLegemdNameIconMap)[stEquipmentLegend.iLegendId] = pix;
							p.drawPixmap(rectNameImg.left(),rectNameImg.top(),pix.scaled(QSize(rectNameImg.width(),rectNameImg.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
					}

					p.drawPixmap(rectTVLevel.left(),rectTVLevel.top(),m_pixTVLevelBG.scaled(QSize(rectTVLevel.width(),rectTVLevel.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					QString strLv = QString("Lv.")+ QString::number(stEquipmentLegend.iLevel);
					p.setPen(QColor("#dac6a3"));
					QFont font(QStringLiteral("FZZhengHeiS-M-GB"));
					font.setPixelSize(14);
					p.setFont(font);
					p.drawText(QRect(rectTVLevel),strLv,QTextOption(Qt::AlignCenter));

					if (stEquipmentLegend.eHeroStatusFlag == eHeroStatusOwn)
					{//已拥有
						//p.drawPixmap(rectOwnOrNotOwn.left(), rectOwnOrNotOwn.top(), m_pixOwn.width(), m_pixOwn.height(), m_pixOwn);
					}
					if (stEquipmentLegend.eHeroStatusFlag == eHeroStatusNotOwn)
					{//未拥有
						/*	p.drawPixmap(rectOwnOrNotOwn.left(), rectOwnOrNotOwn.top(), m_pixNotOwn.width(), m_pixNotOwn.height(), m_pixNotOwn);*/
						p.drawPixmap(rectImg.left()+3, rectImg.top()+3, m_pixMesh.width(), m_pixMesh.height(), m_pixMesh);
					}

					

				}
			}
			break;
		case  eTableProp:
			{
				QRect rect			= option.rect;
				QRect rectFill		= QRect(rect.left()+11,rect.top()+10,138,243);
				QRect rectIconBorder= QRect(rectFill.left()+29,rectFill.top()+31,80,80);
				QRect rectEquip		= QRect(rectIconBorder.left() + 36,rectIconBorder.top(),47,48);
				QRect rectName		= QRect(rectFill.left() ,rectFill.top() +131,rectFill.width(),20);
				QRect rectOwn		= QRect(rectFill.left() +14 ,rectFill.top() +205,108,30);
				QRect rectUnOwn		= QRect(rectFill.left() + 8 ,rectFill.top() -3,23,70);
				QRect rectTime		= QRect(rectFill.left() + 5 ,rectFill.top() +187,rectFill.width()-10,14);
				QRect rectPrice		= QRect(rectFill.left() + 5 ,rectFill.top() +205,rectFill.width()-10,14);
				const STUserHeroCultivateItem& stCultivateItemTableRecord = qvariant_cast<STUserHeroCultivateItem>(var);
				if ( stCultivateItemTableRecord.uiItemId > 0 )
				{
					//const_cast<QMap<DWORD,QRect>&>(m_vecRectOwned_Buy)[nIndex]=rectOwn;
					//背景
					p.drawPixmap(rectFill.left(),rectFill.top(),m_pixPropListNormal.scaled(QSize(rectFill.width(),rectFill.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					if ( option.state & QStyle::State_MouseOver /*|| option.state & QStyle::State_Selected*/ )
					{
						p.drawPixmap(rectFill.left(),rectFill.top(),m_pixPropListSelect.scaled(QSize(rectFill.width(),rectFill.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					//图片
					QString strIcon = QString::fromStdWString(stCultivateItemTableRecord.strItemIcon);
					QMap<QString,QPixmap>::const_iterator iter = m_mapEquipmentIcon.find(strIcon);
					if ( iter != m_mapEquipmentIcon.end() )
					{
						p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),iter->scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
					else
					{
						QPixmap pix;
						QString strIcon2 = QString("./Images/Setting/QxDevelop/Icon/rect/")+strIcon;
						bool bLoad = pix.load(strIcon2);
						if ( bLoad )
						{
							const_cast<QMap<QString,QPixmap>&>(m_mapEquipmentIcon)[strIcon] = pix;
							p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),pix.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						else
						{
							QString strIcon2 = QString("./Images/Setting/QxDevelop/Icon/rect/Gossip.png");
							bool bLoad = pix.load(strIcon2);
							p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),pix.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
					}
					//分类
					QPixmap pmType = m_mapType2Item.value((ECultivateSlotStatus)stCultivateItemTableRecord.uiSlotMask);
					p.drawPixmap(rectIconBorder.left()+2,rectIconBorder.top()+61,pmType);
					//边框
					p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixPropListBorder.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					switch ( stCultivateItemTableRecord.uiItemLevel )
					{
					case 1://没有枚举类型,注释：普通品质
						if ( !m_pixPTIcon.isNull() )
						{
							p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixPTIcon.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						break;
					case 2://没有枚举类型,注释：精良品质
						if ( !m_pixJLIcon.isNull() )
						{
							p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixJLIcon.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						break;
					case 3://没有枚举类型,注释：珍稀品质
						if ( !m_pixZXIcon.isNull() )
						{
							p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixZXIcon.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						break;
					default:
						break;
					}

					//名称
					font.setPixelSize(16);
					p.setFont(font);

					p.drawText(rectName,QString::fromStdWString(stCultivateItemTableRecord.strName),QTextOption(Qt::AlignCenter));
					if ( stCultivateItemTableRecord.bIsOwned )
					{
						//检查是否已加载该道具
						if ( GossipSection::GetInstance()->IsEquiped(stCultivateItemTableRecord.uiItemId) )
						{
							p.drawPixmap(rectEquip.left(),rectEquip.top(),m_pixGossipTVEquip.scaled(QSize(rectEquip.width(),rectEquip.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						//损坏和半损坏
						if ( stCultivateItemTableRecord.uiDurability != stCultivateItemTableRecord.uiMaxDurability )
						{
							if ( stCultivateItemTableRecord.uiDurability <= 20 )
							{
								//八卦道具耐久度只扣了1点,就会显示破损状态，应该是低于20才会显示黄色残破，变0显示红色残破
								if ( stCultivateItemTableRecord.uiDurability == 0 )
								{
									//损坏
									p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixSunhuai.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
								}
								else
								{
									//半损坏
									p.drawPixmap(rectIconBorder.left(),rectIconBorder.top(),m_pixBanShunHuai.scaled(QSize(rectIconBorder.width(),rectIconBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
								}
							}
						}
						QString strPrice = QString::fromWCharArray(L"已拥有");
						QRect rcOwn;
						rcOwn.setRect(rectFill.left(), rectFill.top()+205, rectFill.width(), 20);
						p.drawText(rcOwn,strPrice,QTextOption(Qt::AlignCenter));
					}
					else
					{
						{
							//期限
							//QString strTime = QString::fromWCharArray(L"期限:永久");
							//p.drawText(rectTime,strTime,QTextOption(Qt::AlignLeft));
							QRect rcBuy;
							rcBuy.setRect(rectFill.left(), rectFill.top()+205, rectFill.width(), 20);
							if ( stCultivateItemTableRecord.uiItemLevel == 3)
							{//珍稀品质
								//p.setPen(QColor("#f5a238"));
								font.setPixelSize(12);
								p.setFont(font);
								QString strText = QString::fromStdWString(L"来源：战利品");
								p.drawText(QRect(rcBuy.left(), rcBuy.top(), rcBuy.width(), rcBuy.height())	, strText,QTextOption(Qt::AlignCenter));
							}
							else
							{
								if (!m_pixLhsp.isNull())
								{
									p.drawPixmap(rcBuy.left()+35, rcBuy.top(), m_pixLhsp.width(), m_pixLhsp.height(), m_pixLhsp);
								}
								//价格
								QString strPrice =/* QString::fromWCharArray(L"价格:") +*/ QString::number(stCultivateItemTableRecord.uiPrice);
								p.drawText(rcBuy,strPrice,QTextOption(Qt::AlignCenter));
							}
						}
					}
				}
			}
			break;

			case eTableGossip:
				{
					QRect rect			= option.rect;
					QRect rectImgBorder = QRect(rect.left()+13,rect.top()+9,53,53);
					QRect rectEquip		= QRect(rectImgBorder.left()+9,rectImgBorder.top()+1,47,48);
					QRect rectType		= QRect(rectImgBorder.left()+5,rectImgBorder.top()+35,16,15);
					QRect rectName		= QRect(rect.left(),rect.top()+64,80,21);
					//painter->drawRect(rect);
					//painter->drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixGossipMengBan.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					const STUserHeroCultivateItem& stCultivateItemTableRecord = qvariant_cast<STUserHeroCultivateItem>(var);
					if ( stCultivateItemTableRecord.uiItemId > 0 )
					{
						QString strIcon = QString::fromStdWString(stCultivateItemTableRecord.strItemIcon);
						QMap<QString,QPixmap>::const_iterator iter = m_mapEquipmentIcon.find(strIcon);
						if ( iter != m_mapEquipmentIcon.end() )
						{
							p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),iter->scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						else
						{
							QPixmap pix;
							QString strIcon2 = QString("./Images/Setting/QxDevelop/Icon/rect/")+strIcon;
							bool bLoad = pix.load(strIcon2);
							if ( bLoad )
							{
								const_cast<QMap<QString,QPixmap>&>(m_mapEquipmentIcon)[strIcon] = pix;
								p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),pix.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
							}
							else
							{
								QString strIcon2 = QString("./Images/Setting/QxDevelop/Icon/rect/Gossip.png");
								bool bLoad = pix.load(strIcon2);
								p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),pix.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
								////LOG_INFO("缺少资源:rect->"<<stCultivateItemTableRecord.strItemIcon);
							}
						}

						p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixGossipBorder.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));

						//painter->drawText(rect,Qt::AlignCenter,QString::number(stCultivateItemTableRecord.uiItemId));
						if ( !stCultivateItemTableRecord.bIsOwned )
						{
							//未拥有
							p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixGossipMengBan.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						else
						{
							//已拥有
							//检查是否已加载该道具

							if ( stCultivateItemTableRecord.uiDurability != stCultivateItemTableRecord.uiMaxDurability )
							{
								if ( stCultivateItemTableRecord.uiDurability <= 20 )
								{
									//八卦道具耐久度只扣了1点,就会显示破损状态，应该是低于20才会显示黄色残破，变0显示红色残破
									if ( stCultivateItemTableRecord.uiDurability == 0 )
									{
										//损坏
										p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixSunhuai.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
									}
									else
									{
										//半损坏
										p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixBanShunHuai.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
									}
								}
							}
							else
							{
								//检查是否处于修复状态
								if ( GossipSection::GetInstance()->GetRepairState()  )
								{
									p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixGossipMengBan.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
								}
							}
							if ( GossipSection::GetInstance()->IsEquiped(stCultivateItemTableRecord.uiItemId) )
							{
								p.drawPixmap(rectEquip.left(),rectEquip.top(),m_pixGossipTVEquip.scaled(QSize(rectEquip.width(),rectEquip.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
							}
						}
						p.drawPixmap(rectType,m_mapType2Item[(ECultivateSlotStatus)stCultivateItemTableRecord.uiSlotMask].scaled(QSize(rectType.width(),rectType.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						switch ( stCultivateItemTableRecord.uiItemLevel   )
						{
						case 1://没有枚举类型,注释：普通品质
							if ( !m_pixPTIcon.isNull() )
							{
								p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixPTIcon.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
							}
							break;
						case 2://没有枚举类型,注释：精良品质
							if ( !m_pixJLIcon.isNull() )
							{
								p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixJLIcon.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
							}
							break;
						case 3://没有枚举类型,注释：珍稀品质
							if ( !m_pixZXIcon.isNull() )
							{
								p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixZXIcon.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
							}
							break;
						default:
							break;
						}
						QFont font(QStringLiteral("FZZhengHeiS-M-GB"));
						font.setPixelSize(12);
						p.setFont(font);
						p.setPen(QColor("#c9b696"));
						p.drawText(rectName,QString::fromStdWString(stCultivateItemTableRecord.strName),QTextOption(Qt::AlignCenter));

						if ( option.state & QStyle::State_Selected )
						{
							p.drawPixmap(rectImgBorder.left(),rectImgBorder.top(),m_pixGossipTVSelect.scaled(QSize(rectImgBorder.width(),rectImgBorder.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
						}
						//painter->drawText(rect,Qt::AlignCenter,QString::number(stCultivateItemTableRecord.uiItemId));
					}
				}
				break;
#endif
		
		}
	}
	painter->restore();
}

QSize QxEquipmentTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize sizeItem;
	switch (m_eTable)
	{
	case eTableEquipment:
		sizeItem = QSize(190,70);//spacing 10,10
		break;
	case eTableLegend:
		/*sizeItem =  QSize(60,60);
		break;*/
	case eTableDevelopLegend:
		sizeItem =  QSize(160,200);
		break;
	case eTableProp:
		sizeItem =  QSize(160,263);
		break;
	case eTableGossip:
		sizeItem =  QSize(80,88);
		break;
	}
	return sizeItem;
}

void QxEquipmentTableDelegate::setETable(ETable eTable)
{
	m_eTable = eTable;
	switch (m_eTable)
	{
	case eTableEquipment:
		{
			m_pixBG.load("./Images/Setting/QxEquipment/equipmentBG.png");
			m_pixSelect.load("./Images/Setting/QxEquipment/QxEquipmentSelect.png");
		}
		break;
	case eTableLegend:
		{
			m_pixBG.load("./Images/Setting/QxEquipment/QxEquipmentLegendBG.png");
			m_pixSelect.load("./Images/Setting/QxEquipment/QxEquipmentLegendSelect.png");

		}
		break;
	case eTableProp:
		m_pixPropListNormal.load("./Images/Setting/QxDevelop/proplist.png");
		m_pixPropListSelect.load("./Images/Setting/QxDevelop/proplist_hover.png");

		m_pixPropListBorder.load("./Images/Setting/QxDevelop/GossipTV1.png");
		m_pixPropListExample.load("./Images/Setting/QxDevelop/Icon/rect/Gossip.png");
		m_pixMoneyIcon.load("./Images/Setting/QxDevelop/moneyIcon.png");

		m_pixGossipTVEquip.load("./Images/Setting/QxDevelop/GossipTVEquip.png");
		m_pixUnOwned.load("./Images/Setting/QxDevelop/UnOwned.png");
		break;
	case eTableGossip:
		m_pixBG.load("./Images/Setting/QxDevelop/touxiang.png");
		m_pixGossipBorder.load("./Images/Setting/QxDevelop/GossipTV1.png");
		m_pixGossipMengBan.load("./Images/Setting/QxDevelop/mengban.png");
		m_pixGossipTVSelect.load("./Images/Setting/QxDevelop/GossipTVSelect.png");
		m_pixGossipTVEquip.load("./Images/Setting/QxDevelop/GossipTVEquip.png");
		break;
	}
}

void QxEquipmentTableDelegate::setPressedItem(const STEquipment & stEquipment)
{
	m_stEquipment = stEquipment;
}

void QxEquipmentTableDelegate::setPressedItem(const STEquipmentLegend & stEquipmentLegend)
{
	m_stEquipmentLegend = stEquipmentLegend;
}

void QxEquipmentTableDelegate::setMapId2StrInfo(QMap<DWORD,QString> mapId2Str)
{
	if ( m_eTable == eTableDevelopLegend || m_eTable == eTableLegend)
	{
		m_mapId2Str = mapId2Str;
	}
}