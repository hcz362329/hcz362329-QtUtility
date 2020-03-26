#ifndef EQUIPMENTSETMODULE_H
#define EQUIPMENTSETMODULE_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "EquipmentSchemeModule.h"

class EquipmentSetModule : public EquipmentBase
{
	Q_OBJECT
public:
	explicit EquipmentSetModule(QWidget* parent = NULL);
	~EquipmentSetModule();
signals:
	void selectLegend(const STEquipmentLegend & stEquipmentLegend);
	void equipmentTableClicled(const STEquipment & stEquipment);
	void recomandEquipment(const STEquipmentSet & stEquipmentSet);
	void recomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
protected:
	virtual void paintEvent(QPaintEvent *event);
public slots:
	//�л���Ӣ������ģ��
	void OnChangeHeroBtnClicked();
	//�л���װ������ģ��
	void OnNotChangeHeroBtnClicked();
	//��ȡӢ��ѡ����
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
public:
	//����Ӣ��
	void SetLegend(DWORD dwLegendId);
	void LoadLegendPixmap(DWORD dwLegendId);
private:
	QPixmap m_pixLegend;
	STEquipmentLegend m_stEquipmentLegend;
	//Ӣ��ѡ��ģ��
	
	//װ������ģ��
	EquipmentSchemeModule* m_pEquipmentSchemeModule;
	//����Ӣ��,��������Ӣ�۰�ť
	QPushButton* m_pChangeHero;
	QPushButton* m_pNotChangeHero;
	//�û�ѡ���Ӣ��Icon�ռ�
	QMap<int,QPixmap> m_mapLegendIcon;
};
#endif