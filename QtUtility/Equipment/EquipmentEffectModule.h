#ifndef EQUIPMENTEFFECTMODULE_H
#define EQUIPMENTEFFECTMODULE_H
#include "BaseDataDef.h"
#include "EquipmentBase.h"
#include "QxRadioLabel.h"
#include <QSignalMapper>
#include <QCheckBox>

class EquipmentEffectModule : public EquipmentBase
{
	Q_OBJECT
public:
	explicit EquipmentEffectModule(QWidget* parent = NULL);
	~EquipmentEffectModule();
	void constructCheckBox();
	void constructRadioBox();
	//重置复选框选中
	void resetCheckBoxState();
	void setRadioBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable);
	void setCheckBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable);
public slots:
	//装备属性复选框信号槽
	void OnCheckBoxTypeClicked(int nCheckType);
	//装备属性单选框信号槽
	void OnRadioTypeClicked(int nCheckType);
protected:
	virtual void paintEvent(QPaintEvent *);
signals:
	void equipmentEffectCheckedResult(const QVector<int> & vecType);
private:
	//复选框
	QSignalMapper* m_pEquipEffectCheckMapper;
	//攻击力
	QCheckBox* m_pCheckBox1;
	//护甲穿透
	QCheckBox* m_pCheckBox4;
	//攻击速度
	QCheckBox* m_pCheckBox7;
	//物理暴击
	QCheckBox* m_pCheckBox10;
	//生命偷取
	QCheckBox* m_pCheckBox13;

	//法术强度
	QCheckBox* m_pCheckBox2;
	//法术穿透
	QCheckBox* m_pCheckBox5;
	//冷却缩减
	QCheckBox* m_pCheckBox8;
	//法力值
	QCheckBox* m_pCheckBox11;
	//法力恢复
	QCheckBox* m_pCheckBox14;

	//生命值
	QCheckBox* m_pCheckBox3;
	//护甲
	QCheckBox* m_pCheckBox6;
	//法术抗性
	QCheckBox* m_pCheckBox9;
	//生命恢复
	QCheckBox* m_pCheckBox12;
	//移动速度
	QCheckBox* m_pCheckBox15;

	//单选框
	QSignalMapper * m_pEquipEffectRadioMapper;
	//攻击力
	QxRadioLabel* m_pRadioLabel1;
	//护甲穿透
	QxRadioLabel* m_pRadioLabel4;
	//攻击速度
	QxRadioLabel* m_pRadioLabel7;
	//物理暴击
	QxRadioLabel* m_pRadioLabel10;
	//生命偷取
	QxRadioLabel* m_pRadioLabel13;

	//法术强度
	QxRadioLabel* m_pRadioLabel2;
	//法术穿透
	QxRadioLabel* m_pRadioLabel5;
	//冷却缩减
	QxRadioLabel* m_pRadioLabel8;
	//法力值
	QxRadioLabel* m_pRadioLabel11;
	//法力恢复
	QxRadioLabel* m_pRadioLabel14;

	//生命值
	QxRadioLabel* m_pRadioLabel3;
	//护甲
	QxRadioLabel* m_pRadioLabel6;
	//法术抗性
	QxRadioLabel* m_pRadioLabel9;
	//生命恢复
	QxRadioLabel* m_pRadioLabel12;
	//移动速度
	QxRadioLabel* m_pRadioLabel15;

	//背景图
	QPixmap m_pixEffectBG;
};
#endif