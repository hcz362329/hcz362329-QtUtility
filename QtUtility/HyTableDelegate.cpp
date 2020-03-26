#include "HyTableDelegate.h"
#include <QDebug>
#include <QPainter>
HyTableDelegate::HyTableDelegate(QWidget* parent)
	: QAbstractItemDelegate(parent)
	, m_ETable(ETableNormal)
	, m_eHyShowType(eHyShowNormal)
{
	m_pixItemBG.load("./Images/hunyu/hyTableBg.png");
	m_pixSelect.load("./Images/hunyu/select.png");
	m_pixEquiped.load("./Images/hunyu/equiped.png");
	m_pixLock.load("./Images/hunyu/lock.png");
	m_pixJXLock.load("./Images/JiangXing/lockJX.png");
	m_pixUnLock.load("./Images/hunyu/unlock.png");
	m_pixMengBan.load("./Images/JiangXing/jxTMB.png");
	m_pixHyItemCountBG.load("./Images/HyItemCountBG.png");
	for ( int n = 0; n < _countof(m_arItemIcon); ++n )
	{
		m_arItemIcon[n].load(QString("./Images/hunyu/icon_%1.png").arg(n+1));
	}
	for ( int n = 0; n < _countof(m_arLv5Icon); ++n )
	{
		m_arLv5Icon[n].load(QString("./Images/ShouHun/icon_%1.png").arg(n+1));
	}
	for ( int n = 0; n < _countof(m_arLv5AttrIcon); ++n )
	{
		m_arLv5AttrIcon[n].load(QString("./Images/hunyu/forelv5_%1.png").arg(n+1));
	}

}

HyTableDelegate::~HyTableDelegate()
{
	
}

void HyTableDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	painter->save();
	switch ( m_ETable )
	{
	case ETableNormal:
		{
			
		}
		break;
	case ETableJX:
		{
			STJX stJX = qvariant_cast<STJX>(index.data(Qt::DisplayRole));
			QRect rectSTJX						= option.rect;
			QRect rectJXBG                  = QRect(option.rect.left() + 3 ,option.rect.top() + 3 ,63,63);
			QRect rectJX                    = QRect(option.rect.left() + 11 ,option.rect.top() + 11 ,47,47);
			QRect rectNum					= QRect(option.rect.left() +45 ,option.rect.top() + 6 ,19,19);
			if ( !m_pixItemBG.isNull() )
			{
				painter->drawPixmap(rectJXBG.left(),rectJXBG.top(),m_pixItemBG.scaled(QSize(rectJXBG.width(),rectJXBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			}
			if ( !stJX.strImgPath.isEmpty() )
			{
				QMap<QString,QPixmap>::const_iterator iter = m_mapImg.find(stJX.strImgPath);
				if ( iter != m_mapImg.end() )
				{
					painter->drawPixmap(rectJX.left(),rectJX.top(),iter.value().scaled(QSize(rectJX.width(),rectJX.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				else
				{
					QString strJXPath64 = QString("./Images/JiangXing_64/%1.jpg").arg(stJX.strJXEng);
					QPixmap pix(strJXPath64);
					const_cast<QMap<QString,QPixmap>&>(m_mapImg)[stJX.strImgPath] = pix;
					painter->drawPixmap(rectJX.left(),rectJX.top(),pix.scaled(QSize(rectJX.width(),rectJX.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
			}
			else
			{
				if ( !stJX.strJXName.isEmpty() )
				{
					qDebug()<<"name:"<<stJX.strJXName<<"img is null";
				}
			}
			QPen pen ;
			pen.setColor(QColor(232, 204, 106));
			if ( stJX.nNum > 0 )
			{
				painter->setPen(pen);
				QFont font;
				font.setFamily("SimSun");
				font.setPixelSize(12);
				painter->setFont(font);
				painter->setPen(QColor(232,204,106));
				painter->drawPixmap(rectNum.left(),rectNum.top(),m_pixHyItemCountBG.scaled(QSize(rectNum.width(),rectNum.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				painter->drawText(rectNum.left(),rectNum.top()-2,rectNum.width(),rectNum.height(),Qt::AlignCenter,QString::number(stJX.nNum));
				
			}
			else
			{
				if ( stJX.nNum == 0 || stJX.nLock )
				{
					//加锁和加蒙版的顺序
					if ( stJX.nLock )
					{
						painter->drawPixmap(rectJXBG.left(),rectJXBG.top(),m_pixJXLock.scaled(QSize(rectJXBG.width(),rectJXBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					} 
					else
					{
						painter->drawPixmap(rectJXBG.left(),rectJXBG.top(),m_pixMengBan.scaled(QSize(rectJXBG.width(),rectJXBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
					}
				}
			}
		}
		break;
	default:
		break;
	}
	
	painter->restore();
}

QSize HyTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);
	return QSize(HyWidth,HyWidth);
}

void HyTableDelegate::setETable(ETable ETable)
{
	m_ETable = ETable;
}

ETable HyTableDelegate::getETable()
{
	return m_ETable;
}

void HyTableDelegate::setSelectedItem(QVariant item)
{
	m_selectItem = item;
}

bool HyTableDelegate::isEquiped(__int64 nHunyuId) const
{
	return false;
}

void HyTableDelegate::setHyShowType(EHyShowType eHyShowType)
{
	m_eHyShowType = eHyShowType;
}

EHyShowType HyTableDelegate::getHyShowType() const
{
	return m_eHyShowType;
}