#ifndef QXEQUIPMENTTABLEMODEL_H
#define QXEQUIPMENTTABLEMODEL_H
#include <QAbstractTableModel>
#include "BaseDataDef.h"
#include <QWidget>
class QxEquipmentTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit QxEquipmentTableModel(QWidget* parent = NULL);
	~QxEquipmentTableModel();
	int rowCount(const QModelIndex &parent  = QModelIndex() ) const;
	int columnCount(const QModelIndex &parent  = QModelIndex() ) const;
	QVariant data(const QModelIndex &index, int role  = Qt::DisplayRole ) const;
	bool updateAll(const QVector<QVariant>& vecVariant);
	bool removeAll();
	void setETable(ETable eTable);
private:
	QVector<QVariant> m_vecVariant;
	ETable m_eTable;
};
#endif