#ifndef EXAMBOOST_JxModel_H
#define EXAMBOOST_JxModel_H
#include <QAbstractListModel>
#include "HyTableDef.h"

class JxModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JxModel(QObject* parent = NULL);
	~JxModel();
protected:
	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
	void clearModel();
	void updateAll(const QVector<STJX>&);
	void updateAll(QVector<STSH>& vecSTSH);
private:
	QVector<STJX> m_vecSTJX;
	QVector<STSH> m_vecSTSH;
public:
	void setListViewShowType(EListViewShowType eListViewShowType);
	EListViewShowType getListViewShowType();
	EListViewShowType m_eShowType;
};
#endif