#ifndef QXEQUIPMENTTABLEVIEW_H
#define QXEQUIPMENTTABLEVIEW_H
#include <QTableView>
#include "QxEquipmentTableModel.h"
#include "QxEquipmentTableDelegate.h"
#include "EquipmentTip.h"

class QxEquipmentTableView : public QTableView
{
	Q_OBJECT
public:
	explicit QxEquipmentTableView(QWidget* parent = NULL);
	~QxEquipmentTableView();
	void resizeTableContent();
	void setModelDelegate();
	void updateTable(QVector<QVariant>& vecVariant);
	void setETable(ETable eTable);
	void setPressedItem(const STEquipment & stEquipment);
	//��ק����
	void initDragSettings();
	//װ����ʾ��Ϣ����
	void LoadEquipmentInfoTip(QMouseEvent *event);
	//��ʼ������
	void initRect();
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void leaveEvent(QEvent *event);
signals:
	void equipmentTableClicled(const STEquipment & stEquipment);
private:
	QxEquipmentTableModel* m_pModel;
	QxEquipmentTableDelegate* m_pDelegate;
	ETable m_eTable;

	QPoint m_pointDrag;
	STEquipment m_stEquipment;
	QVector<QRect> m_vecRect;
};
#endif