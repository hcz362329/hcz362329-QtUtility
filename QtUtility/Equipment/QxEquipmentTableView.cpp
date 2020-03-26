#include "stdafx.h"
#include "QxEquipmentTableView.h"
//#include "QxLobbyAPIHelper.hpp"
//#include "Log4cplusWrapper.h"
#include <QHeaderView>
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QSound>
#include <QDir>
#include "QxEquipment.h"

QxEquipmentTableView::QxEquipmentTableView(QWidget* parent /*= NULL*/)
	: QTableView(parent)
	, m_eTable(eTableEquipment)
{
	setMouseTracking(true);
	//setShowGrid(false);
	//ѡ������,����ѡ��
	setSelectionMode(QAbstractItemView::SingleSelection);
	//�������������ƶ��¼�ȡ��
	setFocusPolicy(Qt::NoFocus);
	//����ƶ��¼���
	setMouseTracking(true);
	//��������ģ�ͺ���ʾ
	setModelDelegate();
	//�ر�ˮƽ������
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QString strVertical = QString("QScrollBar:vertical{width: 9px;min-height: 60px;background:#2C3236;		border-radius:5px;}\
	QScrollBar::handle:vertical	{width: 4px;min-height: 20px;background:rgba(233,187,85,1);border-radius:3px;}");
	verticalScrollBar()->setStyleSheet(strVertical);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//�����к���ͷ��
	verticalHeader()->hide();
	horizontalHeader()->hide();
	//��ק����
	initDragSettings();
	//����������
	setShowGrid(false);
	//��ʼ������λ��,����Tips
	initRect();
}

QxEquipmentTableView::~QxEquipmentTableView()
{

}

void QxEquipmentTableView::resizeTableContent()
{
	resizeRowsToContents();
	resizeColumnsToContents();
}

void QxEquipmentTableView::initDragSettings()
{
	setDragEnabled(true);
	//setAcceptDrops(true);	
	//setDefaultDropAction(Qt::MoveAction);	
	//setDragDropMode(QAbstractItemView::InternalMove);
	//setDragDropOverwriteMode(false);
	//setDropIndicatorShown(true);
}

void QxEquipmentTableView::setModelDelegate()
{
	m_pModel	= new QxEquipmentTableModel(this);
	m_pDelegate = new QxEquipmentTableDelegate(this);
	setModel(m_pModel);
	setItemDelegate(m_pDelegate);
}

void QxEquipmentTableView::updateTable(QVector<QVariant>& vecVariant)
{
	//LOG_FUN("");
	m_pModel->updateAll(vecVariant);
	resizeTableContent();
	////LOG_INFO("size:"<<vecVariant.size());
}

void QxEquipmentTableView::setETable(ETable eTable)
{
	m_eTable = eTable;
	m_pModel->setETable(m_eTable);
	m_pDelegate->setETable(m_eTable);
	if ( m_eTable == eTableProp )
	{
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	}
}

void QxEquipmentTableView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		QModelIndex index = indexAt(event->pos());
		if ( index.isValid() )
		{
			STEquipment stEquipment;
			stEquipment = qvariant_cast<STEquipment>(index.data(Qt::DisplayRole));
			if ( stEquipment.iEquipmentId > 0 )
			{
#if DELEGATE_PRESSED_ENABLED
				//�������¼���������װ����Ϣ
				if ( event->button() == Qt::LeftButton )
				{
					m_stEquipment = stEquipment;
					QSound::play(QDir::currentPath()+"/Sound/mus_equipclick.wav");
				}
				//�Ҽ�����¼����ͼ��ص�װ��������װ����Ϣ
				if ( event->button() == Qt::RightButton )
				{
					emit equipmentTableClicled(stEquipment);
				}
				setPressedItem(stEquipment);
				update();
#endif
			}
			m_pointDrag = event->pos();
		}
	}
	QTableView::mousePressEvent(event);
}

void QxEquipmentTableView::setPressedItem(const STEquipment & stEquipment)
{
	if ( m_pDelegate != nullptr )
	{
		m_pDelegate->setPressedItem(stEquipment);
	}
}

void QxEquipmentTableView::mouseMoveEvent(QMouseEvent *event)
{
	if ( event->buttons() & Qt::LeftButton )
	{
		int distance = (event->pos() - m_pointDrag).manhattanLength();
		if (distance >= QApplication::startDragDistance())
		{
			QMimeData* mimeData = new QMimeData;
			QByteArray equipData;
			equipData.append((char*)&m_stEquipment,sizeof(m_stEquipment));
			//memcpy(&equipData,&m_stEquipment,sizeof(m_stEquipment));
			mimeData->setData(QxEquipment_Drag_Data_Type,equipData);

			QString strPixmap =QString("./ItemIcon/")+ QString::fromLocal8Bit(m_stEquipment.strEquipmentIcon);
			QPixmap pixmap;
			pixmap.load(strPixmap);
			QPixmap pixResize = pixmap.scaled(QSize(44,44),Qt::KeepAspectRatio,Qt::SmoothTransformation);
			QPoint ptSpot = QPoint(pixResize.width() / 2, pixResize.height() / 2);
			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setHotSpot( ptSpot);
			drag->setPixmap(pixResize);
			drag->exec(Qt::MoveAction);
			delete drag;
			drag = nullptr;
		}
	}
	LoadEquipmentInfoTip(event);
}

void QxEquipmentTableView::leaveEvent(QEvent *event)
{
	QxEquipment::getInstance()->hideEquipmentTip();
	QTableView::leaveEvent(event);
}

void QxEquipmentTableView::LoadEquipmentInfoTip(QMouseEvent *event)
{
	bool bShowTip = false;
	QPoint pos1 = event->pos();
	QModelIndex index = indexAt(event->pos());
	if ( index.isValid() )
	{
		STEquipment stEquipment;
		stEquipment = qvariant_cast<STEquipment>(index.data(Qt::DisplayRole));

		//����װ��λ��������ʾλ��(0,2,4,6,8)(1,3,5,7,9)����һ��,����
		int nEquipmentPos = 0;
		for ( int nIndex = 0 ; nIndex < m_vecRect.size();++nIndex )
		{
			if ( m_vecRect[nIndex].contains(event->pos()) )
			{
				bShowTip = true;
				nEquipmentPos = nIndex;
				break;
			}
		}
		if ( nEquipmentPos % 2 == 0  )//���߱�����һ��
		{
			QxEquipment::getInstance()->showEquipmentTip(QPoint(760,235),stEquipment,bShowTip);
		}
		else if ( nEquipmentPos % 2 == 1 )//���߱���ұ�һ��
		{
			QxEquipment::getInstance()->showEquipmentTip(QPoint(940,235),stEquipment,bShowTip);
		}
	}
	else
	{
		QxEquipment::getInstance()->hideEquipmentTip();
	}
}

void QxEquipmentTableView::initRect()
{
	for ( int nIndex = 0 ;nIndex < 12 ; ++nIndex  )
	{
		QRect rect;
		rect = QRect(nIndex%2*190,nIndex/2*70,190,70);
		m_vecRect.push_back(rect);
	}
}