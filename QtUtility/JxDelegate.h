#ifndef EXAMBOOST_JxDelegate_H
#define EXAMBOOST_JxDelegate_H
#include <QStyledItemDelegate>
#include "HyTableDef.h"
class JxDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit JxDelegate(QObject* parent = NULL);
	~JxDelegate();
public:
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	void setSelectJX(STJX stJX);
public:
	void setListViewShowType(EListViewShowType eListViewShowType);
	EListViewShowType getListViewShowType();
	EListViewShowType m_eShowType;
private:
	STJX m_stJXSelect;
	QPixmap m_pixLock;
	QPixmap m_pixItemBg;
	QPixmap m_pixHyItemCountBG;
	QPixmap m_pixMengBan;
	QMap<QString,QString> m_mapSHEngName;
};

#endif