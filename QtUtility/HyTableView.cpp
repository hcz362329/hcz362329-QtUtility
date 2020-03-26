#include <QPainter>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>
#include <QDrag>
#include <QApplication>
#include <QMimeData>
#include "HyTableView.h"

#define HUNYU_MIME_FORMAT	"image/hunyu"

HyTableView::HyTableView(QWidget* parent)
	: QTableView(parent)
	, m_rtLastRect(QRect())
	, m_pModel(NULL)
	, m_pDelegate(NULL)
	, m_bCombineConfig(false)
	, m_bBatchCombine(false)
	, m_nLockTimer(0)
{
	setFrameShape(QFrame::NoFrame);
	setShowGrid(false);
	initDragSettings();
	setEditTriggers(QAbstractItemView::NoEditTriggers);	
	setSelectionBehavior(QAbstractItemView::SelectItems);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setFocusPolicy(Qt::NoFocus);
	setMouseTracking(true);
	initTableView();
	startLockHyTimer();
}

HyTableView::~HyTableView()
{
	stopLockTimer();
}

void HyTableView::initDragSettings()
{
	setDragEnabled(true);
	setAcceptDrops(true);	
	setDefaultDropAction(Qt::MoveAction);	
	setDragDropMode(QAbstractItemView::InternalMove);
	setDragDropOverwriteMode(false);
	setDropIndicatorShown(true);
}

void HyTableView::initTableView()
{
	setModelDelegate();
	setEditTriggers(QAbstractItemView::NoEditTriggers);			// 设置内容不可编辑etEditTriggers()
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);			// 禁用H方向滚动条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollMode(QAbstractItemView::ScrollPerItem);		// 设置V方向滚动按项
	setSelectionMode(QAbstractItemView::SingleSelection);
	setDragDropOverwriteMode(false);
	setDropIndicatorShown(true);

	/*m_pScrollBar = new CustomStyle;
	verticalScrollBar()->setStyle(m_pScrollBar);*/
	setFocusPolicy(Qt::NoFocus);
	verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	verticalScrollBar()->setFixedWidth(20);
}


void HyTableView::setModelDelegate()
{
	m_pModel = new HyTableModel(this);
	m_pDelegate = new HyTableDelegate(this);
	setModel(m_pModel);
	setItemDelegate(m_pDelegate);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	resetTableViewContents();
}

void HyTableView::updateAll(const QVector<QVariant>& arrItem)
{
	m_vecHunyu.clear();
	m_vecHunyu << arrItem;
	if ( m_pModel->updateAll(arrItem) )
	{
		resetTableViewContents();
		update();
		emit sigItemCount(m_vecHunyu.size());
	}
}

void HyTableView::updateAll(const QList<QVariant>& HyList,QString strJXImg)
{
	//m_ETable == ETableNormal
	QVector<QVariant> vecTmp;
	for( int nIndex = 0 ; nIndex < HyList.size() ; ++nIndex )
	{
		QVariant item;
		
		vecTmp.push_back(item);
	}
	if ( m_pModel != NULL )
	{
		m_pModel->updateAll(vecTmp);
		emit sigItemCount(vecTmp.size());
	}
	resetTableViewContents();
}

void HyTableView::setVerticalScrollBarValue(int nValue)
{
	verticalScrollBar()->setValue(nValue);
}

void HyTableView::updateItemLockState(QVariant item)
{
	if ( m_pModel != NULL )
	{
		m_pModel->updateItemLockState(item);
		updateLockHyVec(item,false);
		update();
	}
}

void HyTableView::updateLockHyVec(QVariant hyItem,bool bInsert)
{
	QMutexLocker mutex(&m_mutex);
	QVector<QVariant>::iterator iter = m_vecLockHy.begin();
	bool bFound = false;
	while ( iter != m_vecLockHy.end() )
	{
		++iter;
	}
	if ( bInsert && !bFound )
	{
		m_vecLockHy.push_back(hyItem);
	}
}

bool HyTableView::HyLocking(QVariant hyItem)
{
	bool bLocking = false;
	
	return bLocking;
}

void HyTableView::updateAll(const QVector<STJX>& vec)
{
	if ( m_pModel != NULL )
	{
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
		emit sigItemCount(/*ownJX.size()*/nTotalHyNum);
		m_pModel->updateAll(vecJX);
		resetTableViewContents();
		
		for(int nIndex = 0 ; nIndex < ownJX.size() ; ++nIndex )
		{
			qDebug()<<"HyTableView name:"<<ownJX[nIndex].strJXName;
		}
	}
}

void HyTableView::resetTableViewContents()
{
	resizeRowsToContents();
	resizeColumnsToContents();
}

void HyTableView::mousePressEvent(QMouseEvent *e)
{
	if ( m_ETable == ETableNormal )
	{
		
		
	}
	if( m_ETable == ETableJX )
	{
		
	}
	QTableView::mousePressEvent(e);
}

void HyTableView::mouseDoubleClickEvent(QMouseEvent *e)
{
	if ( m_ETable == ETableNormal )
	{
	}
	if ( m_ETable == ETableJX )
	{
		return;
	}
	
	QTableView::mouseDoubleClickEvent(e);
}

void HyTableView::mouseMoveEvent(QMouseEvent *e)
{
	if ( m_ETable == ETableNormal )
	{
		
	}
	if ( m_ETable == ETableJX )
	{
		QModelIndex index = indexAt(e->pos());
		STJX stJX = qvariant_cast<STJX>(index.data(Qt::DisplayRole));
		return;
	}
	
	QTableView::mouseMoveEvent(e);
}

void HyTableView::dropEvent(QDropEvent *e)
{
	if ( m_ETable == ETableNormal )
	{
		bool bAccept = false;
		if( e->mimeData()->hasFormat(HUNYU_MIME_FORMAT) )
		{
			
		}
		if( !bAccept )
		{
			e->ignore();
		}
	}
	
}

bool HyTableView::event(QEvent* e)
{
	if ( m_ETable == ETableNormal )
	{
		if ( e->type() == QEvent::ToolTip ) {  
			QHelpEvent *helpEvent = static_cast<QHelpEvent *>(e);  
			QString strTip = getTip(helpEvent->pos());
			

			return true;  
		}  
	}
	
	return QTableView::event(e); 
}

QString HyTableView::getTip(const QPoint& pos)
{
	QString strRtn;
	if ( m_ETable == ETableNormal )
	{
		QModelIndex index = indexAt(pos);
		if ( index.isValid() )
		{
			/*QVariant curHunyuItem = qvariant_cast<QVariant>(index.data(Qt::UserRole));
			if ( curHunyuItem.nHunyuID > 0 )
			{
				strRtn = QString("<strong><font color=#e79f34 weight=bold>&nbsp;%1</font></strong><br>").arg(curHunyuItem.strHunYuName);
				QVector<HunYuEffect> arrEffects;
				CHunYuCollection::getInstance()->getHunyuAttrEffect(curHunyuItem.nHunyuID, arrEffects);
				QString strPropertyEffectName;
				for ( int n = 0; n < arrEffects.size(); ++n )
				{
					if ( arrEffects[n].fPropertyEffectValue > 0 )
					{
						strPropertyEffectName = arrEffects[n].strPropertyEffectName + QString("+") +
							QString("").setNum(arrEffects[n].fPropertyEffectValue, 'g', 3);
					}
					else
					{
						strPropertyEffectName = arrEffects[n].strPropertyEffectName + QString("") +
							QString("").setNum(arrEffects[n].fPropertyEffectValue, 'g', 3);
					}
					if ( arrEffects[n].usEffValueType == 2 )
						strPropertyEffectName += "%";
					strRtn += QString("<br><font color=#e79f34>%1</font>").arg(strPropertyEffectName);
				}
				strRtn += QString("<br><br><font color=#e79f34>%1%2</font>").arg(tr("hunyu_value")).arg(curHunyuItem.usHyValue);
			}*/
		}
	}
	
	

	return strRtn;
}

void HyTableView::setNeedDragItem(QVariant item)
{
	if ( m_ETable == ETableNormal )
	{
		m_needDragHunyuItem = item;
	}
	
}

void HyTableView::startDrag(bool bRightButtonClicked /*= false*/)
{
	/*
	if ( !m_needDragHunyuItem.isDisabled )
	{
		QVariant mineData;
		mineData.dataHunyu.nHunyuLevel = m_needDragHunyuItem.nPropertyLevel;
		mineData.dataHunyu.nHunyuID = m_needDragHunyuItem.nHunyuID;
		mineData.dataHunyu.nAttrType = m_needDragHunyuItem.nPropertyType;
		mineData.dataHunyu.usHyValue = m_needDragHunyuItem.usHyValue;
		mineData.dataHunyu.usHyLock = m_needDragHunyuItem.usHyLock;
		mineData.nHunyuPosIndex = -1;
		strcpy_s(mineData.dataHunyu.szHunyuName, m_needDragHunyuItem.strHunYuName.toLocal8Bit().data());
		strcpy_s(mineData.dataHunyu.strJXName, m_needDragHunyuItem.strJX.toLocal8Bit().data());
		strcpy_s(mineData.dataHunyu.strSHName, m_needDragHunyuItem.strSH.toLocal8Bit().data());
		strcpy_s(mineData.dataHunyu.strJXImg, m_needDragHunyuItem.strJXImg.toLocal8Bit().data());
		strcpy_s(mineData.dataHunyu.strSHImg, m_needDragHunyuItem.strSHImg.toLocal8Bit().data());
		if ( bRightButtonClicked )
		{
			if ( !m_bCombineConfig )
			{
				emit sigDropItem2OperSlot(mineData);
			}
		}
		else
		{
			qDebug()<<"bRightButtonClicked:"<<bRightButtonClicked;
			qDebug()<<"send sigStartDraging signals before";
			emit sigStartDraging(mineData);
			qDebug()<<"send sigStartDraging signals after";
			QMimeData *mimeData = new QMimeData;
			QByteArray itemData;
			mineData.toByteArray(itemData);
			mimeData->setData(HUNYU_MIME_FORMAT, itemData);

			QPixmap pixmap = CResourceHelper::getInstance()->getFImage(mineData.dataHunyu.nHunyuLevel, mineData.dataHunyu.nAttrType);

			QPoint ptSpot = QPoint(pixmap.width() / 2, pixmap.height() / 2);
			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setHotSpot( ptSpot);
			drag->setPixmap(pixmap);
			drag->exec(Qt::MoveAction);

			//通知接受QWidget刷新界面
			emit sigStopDraging();
		}
	}
	*/
}

void HyTableView::setCombineConfig(bool isCombineConfigVisible /*= false*/)
{
	m_bCombineConfig = isCombineConfigVisible;
}

void HyTableView::setBatchCombine(bool isBatchCombine /*= false*/)
{
	m_bBatchCombine = isBatchCombine;
}

void HyTableView::setETable(ETable ETable)
{
	m_ETable = ETable;
	if ( m_pModel != NULL && m_pDelegate != NULL )
	{
		m_pModel->setETable(ETable);
		m_pDelegate->setETable(ETable);
	}
}
ETable HyTableView::getETable()
{
	return m_ETable;
}

void HyTableView::setHyShowType(EHyShowType eHyShowType)
{
	if ( m_pDelegate != NULL )
	{
		m_pDelegate->setHyShowType(eHyShowType);
	}
}

void HyTableView::startLockHyTimer()
{
	if ( m_nLockTimer != 0 )
	{
		stopLockTimer();
	}
	m_nLockTimer = startTimer(10000);
}

void HyTableView::stopLockTimer()
{
	if ( m_nLockTimer != 0 )
	{
		killTimer(m_nLockTimer);
		m_nLockTimer = 0;
	}
}

void HyTableView::timerEvent(QTimerEvent *event)
{
	if ( m_nLockTimer == event->timerId() && m_vecLockHy.size() > 0)
	{
		QMutexLocker mutex(&m_mutex);
		m_vecLockHy.clear();
	}
}