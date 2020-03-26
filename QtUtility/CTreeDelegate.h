#ifndef TREEDELEGATE_H
#define TREEDELEGATE_H
#include <QStyledItemDelegate>


class CTreeDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit CTreeDelegate(QWidget* parent = nullptr);
	~CTreeDelegate();
protected:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
private:
	QPixmap m_pixBG;
	QPixmap m_pixSelect;
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	//µã»÷¶ÔÏó
	
};
#endif
