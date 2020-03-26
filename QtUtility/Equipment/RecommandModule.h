#ifndef RECOMMANDMODULE_H
#define RECOMMANDMODULE_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "RecommandSchemeItem.h"
#include <QScrollBar>
class RecommandModule : public EquipmentBase
{
	Q_OBJECT
public:
	explicit RecommandModule(QWidget* parent = NULL);
	~RecommandModule();
	void setLegendId(int uiLegendId);
	void updateRecommandSchem();
	//���߼�ģ���ź�
	void connectLogicalSignals();
	void SetSendGetHeroSchemeReq(bool bSend);
	//��ȡ�Ƿ��ɸ�ģ�鷢�͵Ļ�ȡӢ��װ����Ϣ����
	bool GetSendGetHeroSchemeReq();
	//�жϻ�ȡӢ�۷����Ĳ����Ƿ���ȷ
	bool GetHeroSchemeRspValid(int uiHeroId);
	//�����Ƽ�����������
	void SetRecommandSchemeNames(const QMap<int,std::wstring> & mapId2Name);
public slots:
	//��ȡӢ��ѡ����
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
	//��ȡӢ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ
	void OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&);
signals:
	void recomandEquipment(const STEquipmentSet & stEquipmentSet);
	void recomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
private:
	//�Ƽ�װ����ϢQMap<����Id,QMap<UINT,STEquipmentSet>>
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapId2EquipmentScheme;
	//�Ƽ�װ����ģ��
	QVector<RecommandSchemeItem*> m_vecRecommandScheme;
	int m_uiLegendId;
	//�����Ƿ��ɸ�ģ�鷢����ȡӢ��װ������������
	bool m_bSendGetHeroSchemeReq;
	//�Ƽ�����������QMap<����Id,��������>
	QMap<int,std::wstring> m_mapId2SchemeName;
};
#endif