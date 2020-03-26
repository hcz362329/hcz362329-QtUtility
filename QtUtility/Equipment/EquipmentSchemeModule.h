#ifndef EQUIPMENTSCHEMEMODULE_H
#define EQUIPMENTSCHEMEMODULE_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "EquipSchemeBtn.h"

#include <QButtonGroup>
#include <QPushButton>
#include "EquipmentTip.h"
class EquipmentSchemeModule : public EquipmentBase
{
	Q_OBJECT
public:
	explicit EquipmentSchemeModule(QWidget* parent = NULL);
	~EquipmentSchemeModule();
	void setLegendScheme(int iLegendId);
	//��ʼ��װ����λ��Ϣ��λ��
	void initBaseData();
	//������װ��
	bool isEquiped(const STEquipment & stEquipment);
	//���õ�һ��δװ���������Ϣ
	bool setFirstEmptyEquipmentInfo(const STEquipment & stEquipment);
	//ѡ������λ���ƶ�
	void moveSelectEquipment();
	//����װ��������ť
	void loadSchemeBtn();
	//���߼�ģ���ź�
	void connectLogicalSignals();
	//����װ��������
	void setSchemeName(int nSchemeBtnPos,QString strName);
	//����װ������
	void ChangeEquipmentScheme();
	//�жϷ�����Ϣ�Ƿ����仯
	bool isEquipmentSchemeInfoChanged();
	//װ����ʾ��Ϣ����
	void LoadEquipmentInfoTip(QMouseEvent *event);
	//װ������Map��Ϣ��UnSaveMap�滻
	void ChangeEquipmentSchemeMapToUnSaveMap();
	//�����Ƿ��ɸ�ģ�鷢����ȡӢ��װ������������
	void SetSendGetHeroSchemeReq(bool bSend);
	//��ȡ�Ƿ��ɸ�ģ�鷢�͵Ļ�ȡӢ��װ����Ϣ����
	bool GetSendGetHeroSchemeReq();
	//�жϻ�ȡӢ�۷����Ĳ����Ƿ���ȷ
	bool GetHeroSchemeRspValid(int uiHeroId);

	//�����϶�����
	void SetDragReq(bool bDrag);
	bool GetDragReq();
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void hideEvent(QHideEvent *);
	virtual bool eventFilter(QObject *, QEvent *);
	//���õ�ǰ������ڲ�λ��װ��
	void setPressedSTEquipmentSet(QMouseEvent *event);
	///ж��װ��
	void UnLoadSTEquipmentSet(QMouseEvent *event);
	//��ק
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	//���شӵ��߱����Ƽ�װ���е���קװ��
	void LoadDragEquipment(QDropEvent *event);
	//���ص�ǰ�������ڲ���ק������
	void LoadInnerDratEquipment(STEquipmentSet stEquipmentSet,QDropEvent *event);
	//��ȡ����Id,ͨ����ť���λ��:m_nSchemeBtnPos
	int getSchemIdBySchemeBtnPos(int nBtnPos);
	//��ȡװ����Ϣ,ͨ������id
	QMap<UINT,STEquipmentSet> getEquipmentSetBySchemeId(int uiSchemeId);
	//��ȡ��һ�θ÷����е����λ״̬����Ϣ,ͨ��������ťλ�û�ȡ
	STEquipmentSet getSchemePressedEquipmentSetInfoBySchemePos(int nSchemePos);
	//��ȡ��������,����Id��1,2,3����������ͨ������UIId��ȡ����ID
	QString getSchemeNameBySchemeId(int nScheme);
	//��ӡ��ǰװ������װ����Ϣ
	void OutputSchemeInfo();
	void updateEquipmentMapSet(QMap<UINT,STEquipmentSet> mapSTEquipmentSet);
	//����װ���������Ʊ༭text
	void SetEditSchemeNameText();
public slots:
	void OnSchemeBtnClicked(int);
	void OnSaveSetBtnClicked();
	void OnRestClicked();
	//�Ҽ����װ�������Ӧ
	void OnEquipmentTableClicled(const STEquipment & stEquipment);
	//��Ӧ�Ƽ�װ��ģ�����ź�
	void OnRecomandEquipment(const STEquipmentSet & stEquipmentSet);
	//��Ӧ�Ƽ�װ��Ӧ�õ���ź�
	void OnRecomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
	//��ȡӢ��ѡ����
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
	//��ȡӢ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ
	void OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&);
	//�����û�Ӣ��������Ϣ��Ӧ�ź�
	void OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp&);

	void OnTextChanged(const QString &);
	void OnEditingFinished();
	//����,��ȡUI���淢���仯
	void SetUIChanged(bool bChange);
	bool GetUIChanged();
private:
	QPixmap m_pixSchemeBG;
	//װ��������ť,����1,����2,����3,���������̶�,�����ƿɸ�,��1,2,3��ʶ
	QButtonGroup* m_pSchemeGroup;
	
	QPushButton* m_pSchemeBtn1;
	QPushButton* m_pSchemeBtn2;
	QPushButton* m_pSchemeBtn3;
	QMap<int,QPushButton*> m_mapSchemeBtn;

	/*EquipSchemeBtn* m_pSchemeBtn1;
	EquipSchemeBtn* m_pSchemeBtn2;
	EquipSchemeBtn* m_pSchemeBtn3;*/

	QPushButton* m_pSaveSetBtn;
	QPushButton* m_pRestBtn;
	//��ǰ������ť��Ӧ�ķ���Id
	QMap<INT,int> m_mapBtnToScheme;
	//����δ�������Ϣ
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapUnSaveSTEquipmentScheme;
	//��ǰӢ�۵ķ���QMap<����Id,װ������>
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapSTEquipmentScheme;
	//��ǰ�����ķ������� QMap<��λ,װ��>
	QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
	//��ǰ������ڲ�λ��װ��
	STEquipmentSet m_stEquipmentSet;
	//��ǰ���������б�����һ�ε�����ڲ�λ��װ����Ϣ
	QMap<INT,STEquipmentSet> m_mapPressedEquipmentSet;
	//��ק������װ�����ݱ���
	STEquipment m_stDragEquipment;
	//��ǰ���������ť�ֶα�ʶ ��1��ʼ��ʶ,�ɴ˱�ʶ��ȡ ����Id,�ɷ���id ��ȡ����װ����Ϣ
	int m_nSchemeBtnPos;
	//װ��
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	//װ���߿�
	QPixmap m_pixBorder;
	//ѡ�б�ʶ
	QPixmap m_pixSelect;
	//��ǰ�����Ƿ����仯
	bool m_bChangeSchemeInfo;//UI�仯��Ϣ 
	bool m_bSaveInfoChanged;//δ������������ı仯��Ϣ
	int m_uiLegendId;
	//��קλ�õ���ʼ��
	QPoint m_pDragPoint;
	//��������
	QMap<int,std::wstring> m_mapIdToName;
	//�����Ƿ��ɸ�ģ�鷢����ȡӢ��װ������������
	bool m_bSendGetHeroSchemeReq;
	QLineEdit * m_pSchemeNameEdit;
	bool m_bDragReq;
	QMap<int, std::wstring> m_mapIdToEdit;
};

#endif