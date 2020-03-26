#include "stdafx.h"
#include "QxEquipmentTableModel.h"

QxEquipmentTableModel::QxEquipmentTableModel(QWidget* parent /*= NULL*/)
	: QAbstractTableModel(parent)
	, m_eTable(eTableEquipment)
{
	m_vecVariant.clear();
}

QxEquipmentTableModel::~QxEquipmentTableModel()
{

}

int QxEquipmentTableModel::rowCount(const QModelIndex &parent  /*= QModelIndex()*/ ) const
{
	int nRow = 0;
	int nColumn=0;
	switch ( m_eTable )
	{
	case eTableEquipment:
		nRow = 6;
		nColumn = 2;
		break;
	case eTableLegend:
		nRow = 5;
		nColumn = 5;
		break;
	case eTableDevelopLegend:
		nRow = 3;
		nColumn = 5;
		break;
	case eTableProp:
		nRow = 2;
		nColumn = 5;
		break;
	case eTableGossip:
		nRow = 4;
		nColumn = 3;
		break;
	default:
		break;
	}

	nRow = m_vecVariant.size() / nColumn;
	if (m_vecVariant.size() % nColumn != 0)
	{
		nRow++;
	}
	return nRow;
	//return ((m_vecVariant.size() - 1) / nColumn + 1) < nRow ? nRow :(m_vecVariant.size() - 1) / nColumn + 1;
}

int QxEquipmentTableModel::columnCount(const QModelIndex &parent  /*= QModelIndex()*/ ) const
{
	int nColumn = 2;
	if ( m_eTable == eTableEquipment )
	{
		nColumn = 2;
	}
	if ( m_eTable == eTableLegend )
	{
		nColumn = 5;
	}
	if ( m_eTable == eTableDevelopLegend )
	{
		nColumn = 5;
	}
	if ( m_eTable == eTableProp )
	{
		nColumn = 5;
	}
	if ( m_eTable == eTableGossip )
	{
		nColumn = 3;
	}
	return nColumn;
}

QVariant QxEquipmentTableModel::data(const QModelIndex &index, int role  /*= Qt::DisplayRole*/ ) const
{
	QVariant var;
	int nTableColumn = columnCount();
	if ( index.isValid() && role == Qt::DisplayRole )
	{
		int nRow	= index.row();
		int nColumn = index.column();
		int nData = nRow * nTableColumn + nColumn;
		if (  nData >= m_vecVariant.size() )
		{
			return var;
		}
		else
		{
			var.setValue(m_vecVariant[nData]);
		}
	}
	return var;
}

bool QxEquipmentTableModel::updateAll(const QVector<QVariant>& vecVariant)
{
	removeAll();

	if (vecVariant.size() > 0)
	{
		int rowCount = vecVariant.size()/columnCount();
		if (0 != vecVariant.size()%columnCount())
		{
			rowCount++;
		}

		beginInsertRows(QModelIndex(),0,rowCount-1);
		m_vecVariant << vecVariant;
		endInsertRows();
	}
	return true;
}

bool QxEquipmentTableModel::removeAll()
{
	beginResetModel();
	m_vecVariant.clear();
	endResetModel();
	return true;
}

void QxEquipmentTableModel::setETable(ETable eTable)
{
	m_eTable = eTable;
}