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
	//魂玉锁定
	void updateItemLockState(QVariant item);

	//将星
	void updateAll(const QVector<STJX>&);
	//将星 5级将星魂玉中获取的list<QVariant> 更新到m_pHyTable
	void updateAll(const QList<QVariant>&,QString strJXImg);
	//更新魂玉锁定操作数据,bInsert:true 放入,false 删除
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
	//魂玉悬浮提示区域设置
	//魂玉点击加锁,解锁区域
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
	//将星
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