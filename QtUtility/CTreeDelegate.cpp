#include "CTreeDelegate.h"
#include <QPainter>

#define DELEGATE_PRESSED_ENABLED 1
#include <QDebug>
#include "Data.h"
#include "Helper/QtHelper.hpp"
CTreeDelegate::CTreeDelegate(QWidget* parent /* = nullptr */)
	: QStyledItemDelegate(parent)
{
	m_pixBG.load("./Images/Equipment/equipmentBG.png");
	m_pixSelect.load("./Images/Equipment/QxEquipmentSelect.png");
}

CTreeDelegate::~CTreeDelegate()
{

}

void CTreeDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	painter->save();
	QRect rect			= option.rect;
	
	QRect rectIcon		= QRect(rect.left(),rect.top(),64,64);
	QRect rectName		= QRect(rect.left()+70,rect.top(),100,rect.height());
	QRect rectGroup		= QRect(rect.left()+10,rect.top()+3,150,rect.height());
	
	if (index.isValid() )
	{
		STNode stNode = qvariant_cast<STNode>(index.data(Qt::DisplayRole));
		QPen pen;
		if (option.state & QStyle::State_MouseOver )
		{
			if ( stNode.IsGroup ){pen.setColor(Qt::green);}
			else{pen.setColor(Qt::red);}
		}
		else
		{
			if (stNode.IsGroup)
				pen.setColor(Qt::darkBlue);
			else
				pen.setColor(Qt::blue);
		}
		painter->setPen(pen);
		if (stNode.IsGroup)
		{
			QString strNum = QString("(%1/%2)").arg(stNode.online).arg(stNode.total);
			QString strText = QString::fromWCharArray(stNode.strGroupName.c_str()) + QString(",group_id:")+QString::number(stNode.group_id)+QString(" ")+strNum;
			
			painter->drawText(rectGroup,Qt::AlignLeft|Qt::TextWordWrap, strText);
		}
		else
		{
			if ( stNode.state == 0 )
			{
				QImage image = QtHelper::GetGrayPixmap(QString::fromWCharArray(stNode.strPath.c_str()));
				painter->drawImage(rectIcon.left(),rectIcon.top(),image.scaled(rectIcon.width(),rectIcon.height()));
			}
			else
			{
				QPixmap pixmap;
				pixmap.load(QString::fromWCharArray(stNode.strPath.c_str()));
				painter->drawPixmap(rectIcon.left(),rectIcon.top(),rectIcon.width(),rectIcon.height(),pixmap);
			}
			QString strText = QString::fromWCharArray(stNode.strName.c_str()) + QString(",node_id:")+QString::number(stNode.node_id)+QString(" ") + QString(",group_id:")+QString::number(stNode.group_id)+QString(" ");
			painter->drawText(rectName,Qt::AlignLeft|Qt::TextWordWrap, strText);
		}
	}
	
	painter->restore();
}QSize CTreeDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const{	QSize size;	STNode stNode = qvariant_cast<STNode>(index.data(Qt::DisplayRole));	if (stNode.IsGroup)
	{
		size = QSize(200,20);
	}	else
	{
		size = QSize(200,66);
	}	return size;}