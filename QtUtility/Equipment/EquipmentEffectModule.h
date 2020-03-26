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
	//���ø�ѡ��ѡ��
	void resetCheckBoxState();
	void setRadioBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable);
	void setCheckBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable);
public slots:
	//װ�����Ը�ѡ���źŲ�
	void OnCheckBoxTypeClicked(int nCheckType);
	//װ�����Ե�ѡ���źŲ�
	void OnRadioTypeClicked(int nCheckType);
protected:
	virtual void paintEvent(QPaintEvent *);
signals:
	void equipmentEffectCheckedResult(const QVector<int> & vecType);
private:
	//��ѡ��
	QSignalMapper* m_pEquipEffectCheckMapper;
	//������
	QCheckBox* m_pCheckBox1;
	//���״�͸
	QCheckBox* m_pCheckBox4;
	//�����ٶ�
	QCheckBox* m_pCheckBox7;
	//������
	QCheckBox* m_pCheckBox10;
	//����͵ȡ
	QCheckBox* m_pCheckBox13;

	//����ǿ��
	QCheckBox* m_pCheckBox2;
	//������͸
	QCheckBox* m_pCheckBox5;
	//��ȴ����
	QCheckBox* m_pCheckBox8;
	//����ֵ
	QCheckBox* m_pCheckBox11;
	//�����ָ�
	QCheckBox* m_pCheckBox14;

	//����ֵ
	QCheckBox* m_pCheckBox3;
	//����
	QCheckBox* m_pCheckBox6;
	//��������
	QCheckBox* m_pCheckBox9;
	//�����ָ�
	QCheckBox* m_pCheckBox12;
	//�ƶ��ٶ�
	QCheckBox* m_pCheckBox15;

	//��ѡ��
	QSignalMapper * m_pEquipEffectRadioMapper;
	//������
	QxRadioLabel* m_pRadioLabel1;
	//���״�͸
	QxRadioLabel* m_pRadioLabel4;
	//�����ٶ�
	QxRadioLabel* m_pRadioLabel7;
	//������
	QxRadioLabel* m_pRadioLabel10;
	//����͵ȡ
	QxRadioLabel* m_pRadioLabel13;

	//����ǿ��
	QxRadioLabel* m_pRadioLabel2;
	//������͸
	QxRadioLabel* m_pRadioLabel5;
	//��ȴ����
	QxRadioLabel* m_pRadioLabel8;
	//����ֵ
	QxRadioLabel* m_pRadioLabel11;
	//�����ָ�
	QxRadioLabel* m_pRadioLabel14;

	//����ֵ
	QxRadioLabel* m_pRadioLabel3;
	//����
	QxRadioLabel* m_pRadioLabel6;
	//��������
	QxRadioLabel* m_pRadioLabel9;
	//�����ָ�
	QxRadioLabel* m_pRadioLabel12;
	//�ƶ��ٶ�
	QxRadioLabel* m_pRadioLabel15;

	//����ͼ
	QPixmap m_pixEffectBG;
};
#endif