#include "HyTableModel.h"
#include <QDebug>
#define Hy_Enabled 1

HyTableModel::HyTableModel(QObject *parent)
	: QAbstractTableModel(parent)
	, m_ETable(ETableNormal)
{
	m_vecHy.clear();
}

HyTableModel::~HyTableModel()
{
	m_vecHy.clear();
}

int HyTableModel::rowCount(const QModelIndex &parent  /*= QModelIndex()*/ ) const
{
	Q_UNUSED(parent);
	switch (m_ETable)
	{
	case ETableNormal:
		{
			if ( m_vecHy.size() <= Hy_Table_Show_Count )
			{
				return  Hy_Row_Count;
			}
			else
			{
				return (m_vecHy.size()-1 )/Column_Count + 1;
			}
		}
		break;
	case ETableJX:
		{
			if ( m_vecJx.size() <= Jx_Table_Show_Count )
			{
				return JX_Row_Count;
			}
			else
			{
				return (m_vecJx.size()-1 )/Column_Count + 1;
			}
		}
		break;
	default:
		break;
	}
	return Hy_Row_Count;
}

int HyTableModel::columnCount(const QModelIndex &parent  /*= QModelIndex()*/ ) const
{
	Q_UNUSED(parent);
	return Column_Count;
}

QVariant HyTableModel::data(const QModelIndex &index, int role  /*= Qt::DisplayRole*/ ) const
{
	if ( !index.isValid() )
	{
		return QVariant();
	}

	if ( role == Qt::DisplayRole )
	{
		//明确取值时的条件,用于在QModelIndex index =indexAt(event->pos());
		// index.data(Qt::DisplayRole);
		QVariant v;
		int nRow    = index.row();
		int nColumn = index.column();
		int nIndex  = nRow * Column_Count + nColumn ;
		switch (m_ETable)
		{
		case ETableNormal:
			{
				if ( nIndex >= m_vecHy.size() )
				{
					return QVariant();
				}
				else
				{
					v.setValue(m_vecHy[nIndex]);
					return v;
				}
			}
			break;
		case ETableJX:
			{
				if ( nIndex >= m_vecJx.size() )
				{
					return QVariant();
				}
				else
				{
					v.setValue(m_vecJx[nIndex]);
					return v;
				}
			}
			break;
		default:
			break;
		}	
	}
	return QVariant();
}

bool HyTableModel::updateAll(const QVector<QVariant>& vecVariant)
{
	removeAll();
	m_vecHy = vecVariant;
	if ( m_vecHy.size() < Hy_Table_Show_Count )
	{
		for ( int nIndex = m_vecHy.size(); nIndex < Hy_Table_Show_Count ; ++nIndex )
		{
			QVariant variant;
			m_vecHy.push_back(variant);
		}
	}
	if ( m_vecHy.size()%columnCount() != 0 )
	{
		int nLength = Column_Count - m_vecHy.size()%Column_Count;
		for ( int i = 0;i < nLength;++i)
		{
			QVariant Variant;
			m_vecHy.push_back(Variant);
		}
	}
	
	beginInsertRows(QModelIndex(),0,(m_vecHy.size()-1 )/Column_Count );
	endInsertRows();
	return true;
}

bool HyTableModel::updateAll(const QVector<STJX>& vecTmp)
{
	removeAll();
	m_vecJx = vecTmp;
	if ( m_vecJx.size() < Jx_Table_Show_Count )
	{
		for ( int nIndex = m_vecJx.size(); nIndex < Jx_Table_Show_Count ; ++nIndex )
		{
			STJX stJX ;
			m_vecJx.push_back(stJX);
		}
	}
	if ( m_vecJx.size()%columnCount() != 0 )
	{
		int nLength = Column_Count - m_vecJx.size()%Column_Count;
		for ( int i = 0;i < nLength;++i)
		{
			STJX stJX;
			m_vecJx.push_back(stJX);
		}
	}

	beginInsertRows(QModelIndex(),0,(m_vecJx.size()-1 )/Column_Count );
	endInsertRows();
#if 0
	for ( int nReset= 0 ; nReset < m_vecJx.size(); nReset++)
	{
		qDebug()<<"nReset:"<<nReset<<" Num:"<<m_vecJx[nReset].nNum<<" name:"<<m_vecJx[nReset].strJXName<<" imgPath:"<<m_vecJx[nReset].strImgPath<<" nLock:"<<m_vecJx[nReset].nLock;
	}
#endif
	
	int nSize = m_vecJx.size();
	Q_UNUSED(nSize);
	return true;
}

void HyTableModel::updateItemLockState(QVariant item)
{
	
}

bool HyTableModel::updateAll()
{
	int nItemCount = 0;
	switch (m_ETable)
	{
	case ETableNormal:
		{
			if ( m_vecHy.size() <= 0 )
			{
				return false;
			}
			nItemCount = m_vecHy.size();
		}
		break;
	case ETableJX:
		break;
	default:
		break;
	}
	beginInsertRows(QModelIndex(),0,(nItemCount-1 )/Column_Count );
	endInsertRows();
	return true;
}

bool HyTableModel::removeAll()
{
	switch (m_ETable)
	{
	case ETableNormal:
		{

			m_vecHy.clear();
		}
		break;
	case ETableJX:
		{
			m_vecJx.clear();
		}
		break;
	default:
		break;
	}
	beginResetModel();
	endResetModel();
	return true;
}

void HyTableModel::setETable(ETable ETable)
{
	m_ETable = ETable;
}

ETable HyTableModel::getETable()
{
	return m_ETable;
}