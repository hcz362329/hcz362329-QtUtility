#ifndef RECOMMANDSCHEMEITEM_H
#define RECOMMANDSCHEMEITEM_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "EquipmentTip.h"
#include <QPushButton>
class RecommandSchemeItem : public EquipmentBase
{
	Q_OBJECT
public:
	explicit RecommandSchemeItem(QWidget* parent = NULL);
	~RecommandSchemeItem();
	void setSchemeId(int nRank = 0);
	//��ʼ��װ����λ��Ϣ��λ��
	void initCtrls();
	void setEquipmentMapInfo(const QMap<UINT,STEquipmentSet> & mapInfo);
	void recommandEquipmentPressed(QMouseEvent *);
	//װ����ʾ��Ϣ����
	void LoadEquipmentInfoTip(QMouseEvent *event);
	//�����Ƽ���������
	void SetSchemeName(std::wstring strName);
signals:
	void recomandEquipment(const STEquipmentSet & stEquipmentSet);
	void recomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void hideEvent(QHideEvent *);
	public slots:
		//Ӧ���Ƽ����������
		void OnApplySchemeBtnClicked();
private:
	QPixmap m_pixBG;
	QPixmap m_pixRankBG;
	//Ӧ�ð�ť
	QPushButton* m_pApplySchemeBtn;
	////��ǰ�����ķ������� QMap<��λ,װ��>
	QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
	//װ���߿�
	QPixmap m_pixBorder;
	//װ����λ��ͼ
	QPixmap m_pixEquipmentSlotBG;
	//װ��
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	QPoint m_pointDrag;
	//�û���ק�����װ��
	STEquipmentSet m_stEquipmentSet;
	//ѡ�б�ʶ
	QPixmap m_pixSelect;
	//����
	int m_nRank;
	QString m_strSchemeName;
};
#endif