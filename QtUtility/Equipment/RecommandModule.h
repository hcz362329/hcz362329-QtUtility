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
	//绑定逻辑模块信号
	void connectLogicalSignals();
	void SetSendGetHeroSchemeReq(bool bSend);
	//获取是否由该模块发送的获取英雄装备信息请求
	bool GetSendGetHeroSchemeReq();
	//判断获取英雄方案的操作是否正确
	bool GetHeroSchemeRspValid(int uiHeroId);
	//设置推荐方案的名称
	void SetRecommandSchemeNames(const QMap<int,std::wstring> & mapId2Name);
public slots:
	//获取英雄选择结果
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
	//获取英雄对应的方案信息和推荐方案信息
	void OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&);
signals:
	void recomandEquipment(const STEquipmentSet & stEquipmentSet);
	void recomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
private:
	//推荐装备信息QMap<方案Id,QMap<UINT,STEquipmentSet>>
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapId2EquipmentScheme;
	//推荐装备子模块
	QVector<RecommandSchemeItem*> m_vecRecommandScheme;
	int m_uiLegendId;
	//设置是否由该模块发出获取英雄装备方案的请求
	bool m_bSendGetHeroSchemeReq;
	//推荐方案的名称QMap<方案Id,方案名称>
	QMap<int,std::wstring> m_mapId2SchemeName;
};
#endif