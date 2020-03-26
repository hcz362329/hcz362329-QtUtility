#ifndef BASEDATADEF_H
#define BASEDATADEF_H
#pragma pack(push,_CRT_PACKING)
#define DELEGATE_PRESSED_ENABLED 1
#define Construct_Data_Enabled 1
#define QxEquipment_Drag_Data_Type "image/QxEquippment"
#define QxEquipment_Inner_Drag_Data_Type "image/QxEquippmentInner"
#define STRING_LENGTH 64
#define EQUIPMENT_SLOT_NUM 9
#define GossipSchemeMaxNum 9
#define DevelopProduct2ItemIdEnabled 1
#include <windows.h>
#include <QObject>
#include <QRect>
#include <QPixmap>
#include <QMetaType>

enum ECultivateSlotStatus
{
	eCSSSlot1Open,
	eCSSSlot2Open,
	eCSSSlot3Open,
	eCSSSlot4Open,
	eCSSSlot5Open,
	eCSSSlot6Open,
	eCSSSlot7Open,
	eCSSSlot8Open,
	eCSSSlot9Open,
	eCSSSlot10Open,
	eCSSSlot11Open,
	eCSSSlot12Open,
	eCSSSlot13Open,
	eCSSSlot14Open,
	eCSSSlot15Open,
	eCSSSlot16Open,
};
class STGetAllHeroInfoRsp;
class STGetUserHeroConfigRsp;
class STChangeUserHeroConfigRsp;
enum EHeroStatusFlag
{
	eHeroStatusFlagNone = 0,
};

//�������ɵ��ߵ���ƷId
#define CultivateTypeId 20004270

enum ETable
{
	eTableLegend=1,			//Ӣ��
	eTableEquipment=2,		//װ��
	eTableDevelopLegend=3,	//����ģ���е�Ӣ��
	eTableProp = 4,			//����ģ���еĵ���
	eTableGossip = 5,		//����
};

enum EScheme
{
	eSchemeNone = 0,
	eSchemeOne,		//����1
	eSchemeTwo,		//����2
	eSchemeThree,	//����3
	eSchemeFour,	//����4
	eSchemeFive,	//����5
	eSchemeSix,		//����6
	eSchemeSeven,	//����7
	eSchemeEight,	//����8
	eSchemeNine,	//����9
};
/* ����������ö��ֵ
սʿ��1
��ʦ��2
���֣�3
��ܣ�4
�̿ͣ�5
*/
enum ELegendType
{
	eLegendCurSelected = -1,// ��ǰѡ�е�
	eLegendAll,//ȫ��Ӣ��
	eLegendMT=4,//���
	eLegendZS=1,//սʿ
	eLegendSS=3,//����
	eLegendFS=2,//��ʦ
	eLegendCK=5,//�̿�
	eLegendFZ=6//����
};

//�����б�
enum EPropType
{
	ePropTypeNone =0,
	ePropYSYN = 1,//��ʿ����
	ePropYLYZ = 2,//Ӣ����־
	ePropYXCH = 3,//Ӣ�۲л�
	ePropQWZL = 4,//����֮��
};

//�����б�
enum EOwnType
{
	eOwnTypeNone =0,
	eOwnTypeAll		= 1,//����
	eOwnTypeOwned	= 2,//��ӵ��
	eOwnTypeUnOwned	= 3,//δӵ��
};

struct STProp
{
	int uiItemTypeId;//����Id
	char   strDesc[STRING_LENGTH];//��������

};

//װ������ö����������ʹ��ƴ������ĸ,�����Ҳ���
enum EEquipmentEffect
{
	eEquipmentEffectNone=0,	//Ĭ����Ч��
	//������						   ����ǿ��							  ����ֵ
	eEquipmentEffectGJL=1,			eEquipmentEffectFSQD=2,				eEquipmentEffectSMZ=3,	
	//���״�͸						   ������͸							  ����
	eEquipmentEffectHJCT=4,			eEquipmentEffectFSCT=5,				eEquipmentEffectFYL=6,
	//�����ٶ�					    	��ȴ����						  ��������
	eEquipmentEffectGJSD=7,			eEquipmentEffectLQSJ=8,				eEquipmentEffectFSKX=9,	
	//������						    ����ֵ								�����ָ�
	eEquipmentEffectWLBJ=10,		eEquipmentEffectFLZ=11,				eEquipmentEffectSMHF=12,	
	//����͵ȡ								�����ָ�							�ƶ��ٶ�
	eEquipmentEffectSMTQ=13,			eEquipmentEffectFLHF=14,			eEquipmentEffectYDSD=15,	
};

struct STEquipment
{
	int iEquipmentId;
	int iItemOrder;
	int iDisplay;//0����ʾ,1��ʾ
	int iEquipmentEffectCost;		//װ�����Ľ�Ǯ
	char strEquipmentEffect[STRING_LENGTH];		//Ч������
	char strEquipmentName[STRING_LENGTH];		//װ������
	char strEquipmentIcon[STRING_LENGTH];		//װ��ͼ��
	char strItemName[STRING_LENGTH];//����װ������ʱ������Ϣ
	STEquipment()
	{
		iEquipmentId = 0;
		iEquipmentEffectCost = 0;
		iItemOrder = 0;
		memset(strEquipmentEffect,0,sizeof(strEquipmentEffect));
		memset(strEquipmentName,0,sizeof(strEquipmentName));
		memset(strEquipmentIcon,0,sizeof(strEquipmentIcon));
		memset(strItemName,0,sizeof(strItemName));
	}
};
Q_DECLARE_METATYPE(STEquipment)

struct STEquipmentLegend
{
	int iLegendId;					//Ӣ��Id
	char strLegendName[STRING_LENGTH];	//Ӣ������
	char strLegendIcon[STRING_LENGTH];	//Ӣ��ͷ��
	int  iLevel;
	ELegendType eLegendType;			//Ӣ������,Ĭ�ϳ�ʼ������ eLegendMT(����ע��ת��ELegendType�鿴)
	EHeroStatusFlag eHeroStatusFlag;	//�Ƿ�ӵ�и�Ӣ��
	STEquipmentLegend()
	{
		iLevel = 0;
		iLegendId = 0;
		memset(strLegendName,0,sizeof(strLegendName));
		memset(strLegendIcon,0,sizeof(strLegendIcon));
		eLegendType = eLegendMT;
	}
};
Q_DECLARE_METATYPE(STEquipmentLegend)

struct STEquipmentSet : public STEquipment
{
	UINT iPos;			//װ����λ,��ǰģ����ʼ��װ��λ��,������ģ��Խ�,ͨ��װ����λ�Խ�װ������
	QRect rectEquipment;//װ������λ��,����ͻ��˴���,����ģ�鲻���ṩ,���磺�߼�ģ�鲻���ṩ
	STEquipmentSet()
	{
		iPos = 0;
	}
};
Q_DECLARE_METATYPE(STEquipmentSet)

struct STProperty
{
	std::wstring strName;
	float fValue;
	bool bIsPassive;
	std::wstring strDesc;
	STProperty()
	{
		bIsPassive = false;
		strName = L"";
		fValue = 0.0;
		strDesc = L"";
	}
};
Q_DECLARE_METATYPE(STProperty)



//ͨ���׶�ʹ��ƴ����ʶ
enum EGossipType
{
	// Ǭqian��kun��kan��li��zhen��gen��xun��dui
	eGossipNone =0,
	eGossipQian		=1 ,//Ǭ
	eGossipKun		=2 ,//��
	eGossipZhen		=3 ,//��
	eGossipXuan		=4 ,//��
	eGossipKan		=5 ,//��
	eGossipLi		=6 ,//��
	eGossipGen		=7 ,//��
	eGossipDui		=8 ,//��
	eGossipTian		=9 ,//��Ǭ
	eGossipTu		=10 ,//����
	eGossipMu		=11 ,//ľ��
	eGossipFeng		=12 ,//����
	eGossipShui		=13 ,//ˮ��
	eGossipHuo		=14 ,//����
	eGossipShan		=15 ,//ɽ��
	eGossipZe		=16,//���
};

enum EGossipId
{
	eGossipIdNone = 0,
	eGossipIdOne,		//����1
	eGossipIdTwo,		//����2
	eGossipIdThree,		//����3
	eGossipIdFour,		//����4
	eGossipIdFive,		//����5
	eGossipIdSix,		//����6
	eGossipIdSeven,		//����7
	eGossipIdEight,		//����8
	eGossipIdNine,		//����9
};

enum EGossipItemShowType
{
	eGossipItemShowTypeNone		= 0,
	eGossipItemShowTypeLock		= 1,//δ����
	eGossipItemShowTypeUnLock	= 2,//�Ѿ�������δ��Ӷ���
	eGossipItemShowTypeNormal	= 3,//�������ж���
	eGossipItemShowTypeDamage	= 4,//������  ��ɫ
	eGossipItemShowTypeDestroy	= 5,//��ȫ��  ��ɫ (�ɰ�,��ȷ��)
};
//#pragma pack(show)

enum EGossipPassivityType
{
	eGossipPassivityNone = 0,
	eGossipPassivityRed = 2,
	eGossipPassivityBlue = 1,
	eGossipPassivityThree = 3,
};

struct STGossipPassivity
{
	EGossipPassivityType eGossipPassivity;
	QRect rect;
	bool  lock;
	QPixmap pixmap;
	STGossipPassivity()
	{
		eGossipPassivity = eGossipPassivityNone;
		lock = true;
	}
};
Q_DECLARE_METATYPE(STGossipPassivity)
#pragma pack(pop)//�����ֽ� ����ջ
//#pragma pack()//�ָ���Ĭ�϶��뷽ʽ
//#pragma pack(show)
#endif