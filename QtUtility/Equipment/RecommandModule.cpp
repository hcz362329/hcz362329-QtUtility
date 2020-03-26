#include "stdafx.h"
#include "RecommandModule.h"
#define Y_POS 117
#define X_POS 265

RecommandModule::RecommandModule(QWidget* parent /*= NULL*/)
	: EquipmentBase(parent)
	, m_bSendGetHeroSchemeReq(false)
	, m_uiLegendId(0)
{
	setMouseTracking(true);
	connectLogicalSignals();
}

void RecommandModule::updateRecommandSchem()
{
	//�˴�ֱ����nIndex��������ֱ�Ӷ�λ��m_mapId2EquipmentScheme�е�Ԫ������Ϊ����Id�Ǵ�1,2,3,4....���������
	//����������ִ�����˴�������
	
	for ( int nIndex = 1 ; nIndex <= m_mapId2EquipmentScheme.size(); ++nIndex )
	{
		RecommandSchemeItem* pScheme = new RecommandSchemeItem(this);
		pScheme->setSchemeId(nIndex);
		pScheme->SetSchemeName(m_mapId2SchemeName[nIndex]);
		bool bConn = connect(pScheme,&RecommandSchemeItem::recomandEquipment,this,&RecommandModule::recomandEquipment);
		bool bConn2 = connect(pScheme,&RecommandSchemeItem::recomandEquipmentApply,this,&RecommandModule::recomandEquipmentApply);
		m_vecRecommandScheme.push_back(pScheme);
		pScheme->setGeometry(0,108*(nIndex-1),564,108);
		pScheme->setEquipmentMapInfo(m_mapId2EquipmentScheme[nIndex]);
		pScheme->show();
	}
	resize(rect().width(),108*m_mapId2EquipmentScheme.size());
}

void RecommandModule::setLegendId(int uiLegendId)
{
	m_uiLegendId = uiLegendId;
	SetSendGetHeroSchemeReq(true);
}


RecommandModule::~RecommandModule()
{

}

void RecommandModule::OnSelectLegend(const STEquipmentLegend & stEquipmentLegend)
{
	setLegendId(stEquipmentLegend.iLegendId);
}

void RecommandModule::connectLogicalSignals()
{
#if 0
	bool bConnect =connect(CQxFrameHelper<>::GetModule(eModuleIdLogical), 
		SIGNAL(OnRspSignal(const STGetUserHeroConfigRsp&)),
		this, SLOT(OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&)));
	if ( !bConnect )
	{
		//LOG_INFO("������ʧ��:��ȡӢ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ!");
	}
#endif
	
}

void RecommandModule::OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp& stGetUserHeroConfigRsp)
{
#if 0
	//LOG_FUN("");
	//LOG_INFO("stGetUserHeroConfigRsp.uiHeroId="<<stGetUserHeroConfigRsp.uiHeroId);
	if ( !GetHeroSchemeRspValid(stGetUserHeroConfigRsp.uiHeroId) )
	{
		//LOG_INFO("��ȡӢ��װ����Ϣ������Ǳ�ģ�鷢��,��������");
		return;
	}
	else
	{
		SetSendGetHeroSchemeReq(false);
	}
	//Ӣ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ
	//�����Ƽ�������Ϣ,��ǰӢ�۵ķ�����Ϣ������װ��ģ�� EquipmentSchemeModule,�ۺ���ͬ��,��������
	for ( int nIndex = 0 ; nIndex < m_vecRecommandScheme.size() ; ++nIndex )
	{
		if ( m_vecRecommandScheme[nIndex] != NULL )
		{
			delete m_vecRecommandScheme[nIndex];
			m_vecRecommandScheme[nIndex] = NULL;
		}
	}
	//����Ƽ������е���Ϣ
	m_mapId2EquipmentScheme.clear();
	//��ȡ��ǰӢ���Ƽ���װ������
	//����װ����Ϣ
	QMap<int,std::wstring>  mapId2Name;
	for ( int nRank = 1 ; nRank <= stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended.size() ; ++nRank )
	{
		QMap<UINT,STEquipmentSet> mapEquipmentInfo;
		//LOG_INFO("�Ƽ������е�װ������:"<<stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem.size());
		///����Id(1, 2, 3)
		int uiId	 = stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].uiId;
		std::wstring strName=stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].strName;
		//LOG_INFO("Recommand id:"<<uiId<<",name:"<<strName);
		if (strName.empty() )
		{
			wchar_t buf[100];
			swprintf(buf,L"%s%d",L"�Ƽ�����",uiId);
			strName = buf;
		}
		mapId2Name[uiId] = strName;
		for(int nSlot = 0 ; nSlot < stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem.size(); ++nSlot )
		{
			UINT64 uiEquipmentId = stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem[nSlot].uiItemId;
			QString strShowName = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem[nSlot].strItemShowName);
			QString strEffectType = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem[nSlot].strItemTags);
			QString strIcon = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem[nSlot].strItemIcon);
			QString strItemName = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentSchemeRecommended[nRank-1].vecItem[nSlot].strItemName);
			STEquipmentSet stEquipmentSet;
			stEquipmentSet.iEquipmentId = uiEquipmentId;
			strcpy(stEquipmentSet.strEquipmentEffect,strEffectType.toLocal8Bit());
			strcpy(stEquipmentSet.strEquipmentName,strShowName.toLocal8Bit());
			strcpy(stEquipmentSet.strEquipmentIcon,strIcon.toLocal8Bit());
			strcpy(stEquipmentSet.strItemName,strItemName.toLocal8Bit());
			stEquipmentSet.iPos = nSlot+1;
			mapEquipmentInfo[stEquipmentSet.iPos] = stEquipmentSet;
		}
		m_mapId2EquipmentScheme[nRank] = mapEquipmentInfo;
		QMap<UINT,STEquipmentSet>::const_iterator iter = mapEquipmentInfo.begin();
		/*
		while ( iter != mapEquipmentInfo.end() )
		{
			//LOG_INFO("uiEquipmentId="<<iter->iEquipmentId<<",strEquipmentName="<<iter->strEquipmentName
				<<",strEffectType="<<iter->strEquipmentEffect<<",strEquipmentIcon="<<iter->strEquipmentIcon<<",strItemName"<<iter->strItemName);
			iter++;
		}
		*/
		
	}
	//QMap<UINT,STEquipmentSet>
	//��������
	//�����Ƽ�����������,���ƺ�װ�����ݷֿ��ţ��������ں������,Ϊ�˺�֮ǰ�Ĳ���ͻ�ڴ˴�����������
	SetRecommandSchemeNames(mapId2Name);
	updateRecommandSchem();
	update();
#endif
	
}

void RecommandModule::SetRecommandSchemeNames(const QMap<int,std::wstring> & mapId2Name)
{
	m_mapId2SchemeName.clear();
	m_mapId2SchemeName = mapId2Name;
}

void RecommandModule::SetSendGetHeroSchemeReq(bool bSend)
{
#if 0
	//LOG_FUN("");
	//LOG_INFO("���ͻ�ȡӢ�۷�������:"<<bSend);
#endif
	
	m_bSendGetHeroSchemeReq = bSend;
}

bool RecommandModule::GetSendGetHeroSchemeReq()
{
	return m_bSendGetHeroSchemeReq;
}

bool RecommandModule::GetHeroSchemeRspValid(int uiHeroId)
{
	bool bValid = false;
	if ( m_uiLegendId == uiHeroId && GetSendGetHeroSchemeReq() )
	{
		bValid = true;
	}
	return bValid;
}