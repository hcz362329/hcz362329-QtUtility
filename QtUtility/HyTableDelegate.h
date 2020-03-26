#ifndef PACKAGETABLEDELEGATE_H
#define PACKAGETABLEDELEGATE_H
#include "HyTableDef.h"

#include <QAbstractItemDelegate>
class HyTableDelegate : public QAbstractItemDelegate
{
	Q_OBJECT
public:
	explicit HyTableDelegate(QWidget* parent = NULL);
	~HyTableDelegate();
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
public:
	void setSelectedItem(QVariant item);
	bool isEquiped(__int64 nHunyuId) const;
	void setHyShowType(EHyShowType eHyShowType);
	EHyShowType getHyShowType() const;
private:
	QPixmap m_pixSelect;
	QPixmap m_pixItemBG;
	QPixmap m_pixEquiped;
	QPixmap m_pixLock;
	QPixmap m_pixJXLock;
	QPixmap m_pixUnLock;
	QPixmap m_pixMengBan;
	QPixmap m_pixHyItemCountBG;
	QPixmap	m_arItemIcon[5];
	QPixmap	m_arLv5Icon[5];
	QPixmap	m_arLv5AttrIcon[5];
public:
	void setETable(ETable ETable);
	ETable getETable();
	ETable m_ETable;
	QVariant m_selectItem;
	QMap<__int64,bool> m_mapEquiped;
	QMap<QString,QPixmap> m_mapImg;
	EHyShowType		m_eHyShowType;
};

#endif