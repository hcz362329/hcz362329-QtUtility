#include "JxModel.h"

JxModel::JxModel(QObject* parent /*= NULL*/)
	: QAbstractListModel(parent)
{

}

JxModel::~JxModel()
{
	m_vecSTJX.clear();
	m_vecSTSH.clear();
}

int JxModel::rowCount(const QModelIndex & parent /*= QModelIndex()*/) const
{
	Q_UNUSED(parent);
	int nRowCount = 0;
	switch ( m_eShowType )
	{
	case eListViewShowJX:
		{
			nRowCount = m_vecSTJX.size();
		}
		break;
	case eListViewShowSH:
		{
			nRowCount = m_vecSTSH.size();
		}
		break;
	default:
		break;
	}
	return nRowCount;
}

QVariant JxModel::data(const QModelIndex & index, int role /* = Qt::DisplayRole */) const
{
	if ( !index.isValid() )
	{
		return QVariant();
	}
	if ( role == Qt::DisplayRole )
	{
		QVariant v;
		int nIndex = index.row();
		switch ( m_eShowType )
		{
		case eListViewShowJX:
			{
				if ( nIndex < m_vecSTJX.size() )
				{
					v.setValue(m_vecSTJX[nIndex]);
				}
			}
			break;
		case eListViewShowSH:
			{
				if ( nIndex < m_vecSTSH.size() )
				{
					v.setValue(m_vecSTSH[nIndex]);
				}
			}
			break;
		default:
			break;
		}
		return v;
	}
	return QVariant();
}

void JxModel::clearModel()
{
	switch ( m_eShowType )
	{
	case eListViewShowJX:
		{
			if ( m_vecSTJX.size() == 0 )
			{
				beginRemoveRows(QModelIndex(),0,m_vecSTJX.size());
			}
			else
			{
				beginRemoveRows(QModelIndex(),0,m_vecSTJX.size()-1);
			}
			m_vecSTJX.clear();
			endRemoveRows();
		}
		break;
	case eListViewShowSH:
		{
			if ( m_vecSTSH.size() == 0 )
			{
				beginRemoveRows(QModelIndex(),0,m_vecSTSH.size());
			}
			else
			{
				beginRemoveRows(QModelIndex(),0,m_vecSTSH.size()-1);
			}
			m_vecSTSH.clear();
			endRemoveRows();
		}
		break;
	default:
		break;
	}
}

void JxModel::updateAll(const QVector<STJX>& vec)
{
	clearModel();
	m_vecSTJX << vec;
	if ( m_vecSTJX.size() > 0 )
	{
		beginInsertRows(QModelIndex(),0,m_vecSTJX.size() - 1);
		endInsertRows();
	}
}

void JxModel::updateAll(QVector<STSH>& vecSTSH)
{
	clearModel();
	m_vecSTSH << vecSTSH;
	if ( m_vecSTSH.size() > 0 )
	{
		beginInsertRows(QModelIndex(),0,m_vecSTSH.size() - 1);
		endInsertRows();
	}
}

void JxModel::setListViewShowType(EListViewShowType eListViewShowType)
{
	m_eShowType = eListViewShowType;
}

EListViewShowType JxModel::getListViewShowType()
{
	return m_eShowType;
}