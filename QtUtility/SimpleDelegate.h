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
};

#endif