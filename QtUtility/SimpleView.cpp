#include "JxListView.h"
#include <QScrollBar>
#include <QMouseEvent>
#include <qDebug>
JxListView::JxListView(QWidget* parent/* = NULL*/ )
	: QListView(parent)
	, m_pModel(NULL)
	, m_pDelegate(NULL)
{
	initView();
}

JxListView::~JxListView()
{
	
}

void JxListView::initView()
{
	initModelDelagate();
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);			// 禁用H方向滚动条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	setFocusPolicy(Qt::NoFocus);
	verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	verticalScrollBar()->setFixedWidth(20);
}

void JxListView::initModelDelagate()
{
	if ( m_pModel == NULL )
	{
		m_pModel = new JxModel(this);
		setModel(m_pModel);
	}
	if ( m_pDelegate == NULL)
	{
		m_pDelegate = new JxDelegate(this);
		setItemDelegate(m_pDelegate);
	}
}


void JxListView::updateAll(QVector<STJX>& vec)
{
	if ( m_pModel != NULL )
	{
		//获取将星属性
		QVector<STJX> vecJX;
		QVector<STJX> ownJX;
		QVector<STJX> unOwnJX;

		QVector<STJX> lockJX;
		QVector<STJX> unLockJX;

		//锁定，未锁定排序：锁定在后
		std::for_each(vec.begin(),vec.end(),[&](const STJX & stJX)
		{
			if ( stJX.nLock == 1  )
			{
				lockJX << stJX;
			}
			else
			{
				unLockJX << stJX;
			}
		});
		vecJX << unLockJX << lockJX;
		//int nCount = 0;
		int nTotalHyNum = 0;
		std::for_each(vecJX.begin(),vecJX.end(),[&](const STJX & stJX)
		{
			if ( stJX.nNum > 0  )
			{
				ownJX << stJX;
				nTotalHyNum += stJX.nNum;
			}
			else
			{
				unOwnJX << stJX;
			}
		});
		vecJX.clear();
		vecJX << ownJX;
		vecJX << unOwnJX;
		emit sigItemCount(nTotalHyNum/*ownJX.size()*/);
		m_pModel->updateAll(vecJX);
	}
}

void JxListView::updateAll(QVector<STSH>& vecSTSH)
{
	int nTotalHyNum = 0;
	for ( int nIndex = 0 ; nIndex < vecSTSH.size();++nIndex )
	{
		nTotalHyNum+= vecSTSH[nIndex].nNum;
	}
	emit sigItemCount(nTotalHyNum/*vecSTSH.size()*/);
	m_pModel->updateAll(vecSTSH);
}

void JxListView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton )
	{
		QModelIndex index = indexAt(event->pos());
		if ( index.isValid() )
		{
			switch ( m_eShowType )
			{
			case eListViewShowJX:
				{
					STJX stJX = qvariant_cast<STJX>(index.data(Qt::DisplayRole));
					if ( stJX.nLock == 0 && stJX.nNum > 0 )
					{
						emit OnJXSelectSignal(stJX);
					}
				}
				break;
			case eListViewShowSH:
				{
					STSH stSH = qvariant_cast<STSH>(index.data(Qt::DisplayRole));
					if ( stSH.nNum > 0 )
					{
						emit OnSHSelectSignal(stSH);
					}
				}
				break;
			default:break;
			}
		}
	}
	return QListView::mousePressEvent(event);
}

void JxListView::setListViewShowType(EListViewShowType eListViewShowType)
{
	m_eShowType = eListViewShowType;
	m_pModel->setListViewShowType(eListViewShowType);
	m_pDelegate->setListViewShowType(eListViewShowType);
}

EListViewShowType JxListView::getListViewShowType()
{
	return m_eShowType;
}