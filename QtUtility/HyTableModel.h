#ifndef PACKAGETABLEMODEL_H
#define PACKAGETABLEMODEL_H
#include <QVariant>
#include <QAbstractTableModel>
#include "HyTableDef.h"

class HyTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit HyTableModel(QObject *parent = NULL);
	~HyTableModel();
	int rowCount(const QModelIndex &parent  = QModelIndex() ) const;
	int columnCount(const QModelIndex &parent  = QModelIndex() ) const;
	QVariant data(const QModelIndex &index, int role  = Qt::DisplayRole ) const;
	//����
	bool updateAll(const QVector<STJX>&);
	//ͨ��
	bool updateAll(const QVector<QVariant>&);
	bool updateAll();
	bool removeAll();
	//��������
	void updateItemLockState(QVariant item);
private:
	//����
	QVector<QVariant> m_vecHy;
	//����
	QVector<STJX>  m_vecJx;
	QVector<QVariant> m_vecVariant;
public:
	void setETable(ETable ETable);
	ETable getETable();
	ETable m_ETable;
};

#endif