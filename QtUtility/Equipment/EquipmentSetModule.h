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
	//切换到英雄设置模块
	void OnChangeHeroBtnClicked();
	//切换到装备设置模块
	void OnNotChangeHeroBtnClicked();
	//获取英雄选择结果
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
public:
	//设置英雄
	void SetLegend(DWORD dwLegendId);
	void LoadLegendPixmap(DWORD dwLegendId);
private:
	QPixmap m_pixLegend;
	STEquipmentLegend m_stEquipmentLegend;
	//英雄选择模块
	
	//装备方案模块
	EquipmentSchemeModule* m_pEquipmentSchemeModule;
	//更改英雄,放弃更改英雄按钮
	QPushButton* m_pChangeHero;
	QPushButton* m_pNotChangeHero;
	//用户选择后英雄Icon收集
	QMap<int,QPixmap> m_mapLegendIcon;
};
#endif