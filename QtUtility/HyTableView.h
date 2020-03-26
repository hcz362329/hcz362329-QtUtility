#ifndef PACKAGETABLEVIEW_H
#define PACKAGETABLEVIEW_H
#include <QVector>
#include <QLabel>
#include <QTableView>
#include <QMouseEvent>
#include <QDropEvent>
#include <QMutexLocker>
#include <QSequentialAnimationGroup>
#include "HyTableDef.h"
#include "HyTableDelegate.h"
#include "HyTableModel.h"

class HyTableView : public QTableView
{
	Q_OBJECT
public:
	explicit HyTableView(QWidget* parent = NULL);
	~HyTableView();
protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void dropEvent(QDropEvent *e);	
	virtual bool event(QEvent* e);
	QString getTip(const QPoint& pos);
public:
	void initDragSettings();
	void setNeedDragItem(QVariant item);
	void startDrag(bool bRightButtonClicked = false);
	void setCombineConfig(bool isCombineConfigVisible = false);
	void setBatchCombine(bool isBatchCombine = false);
public:
	void initTableView();
	void setModelDelegate();
	void updateAll(const QVector<QVariant>& arrItem);
	void resetTableViewContents();
	void setVerticalScrollBarValue(int);
	//��������
	void updateItemLockState(QVariant item);

	//����
	void updateAll(const QVector<STJX>&);
	//���� 5�����ǻ����л�ȡ��list<QVariant> ���µ�m_pHyTable
	void updateAll(const QList<QVariant>&,QString strJXImg);
	//���»���������������,bInsert:true ����,false ɾ��
	void updateLockHyVec(QVariant hyItem,bool bInsert);
	bool HyLocking(QVariant hyItem);
signals:
	void sigStartDraging(const QVariant& data);
	void sigStopDraging();
	void sigAnimationStoped(__int64);
	void sigDropItem2OperSlot(const QVariant&);
	void sigResetBagItemUsedStatus(const QVariant&);
	void OnHyHoverSignal(const QVariant& item);
	void OnJXSelectSignal(const STJX& stJX);
	void sigItemCount(const int & count);
protected:
	virtual void timerEvent(QTimerEvent *event);
private:
	QRect m_rtLastRect;
	//����������ʾ��������
	//����������,��������
	QVector<QRect> m_vecTipRect;
	QVector<QRect> m_vecLockRect;
	QVector<QVariant> m_vecHunyu;

	HyTableModel* m_pModel;
	HyTableDelegate* m_pDelegate ;

	QPoint m_ptStartPos;
	QVariant m_needDragHunyuItem;
	QLabel *m_pAnimationLabel;
	QSequentialAnimationGroup *m_pAnimationGroup;
	bool m_bCombineConfig;
	bool m_bBatchCombine;
	QVector<QVariant> m_vecVariant;
	//����
	QVector<STJX> m_vecJX;
public:
	void setETable(ETable ETable);
	void setHyShowType(EHyShowType eHyShowType);
	ETable getETable();
	ETable m_ETable;
	QVector<QVariant> m_vecLockHy;
	int m_nLockTimer;
	void startLockHyTimer();
	void stopLockTimer();
	QMutex m_mutex;
};

#endif