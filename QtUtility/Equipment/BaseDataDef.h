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

//购买养成道具的商品Id
#define CultivateTypeId 20004270

enum ETable
{
	eTableLegend=1,			//英雄
	eTableEquipment=2,		//装备
	eTableDevelopLegend=3,	//养成模块中的英雄
	eTableProp = 4,			//养成模块中的道具
	eTableGossip = 5,		//八卦
};

enum EScheme
{
	eSchemeNone = 0,
	eSchemeOne,		//方案1
	eSchemeTwo,		//方案2
	eSchemeThree,	//方案3
	eSchemeFour,	//方案4
	eSchemeFive,	//方案5
	eSchemeSix,		//方案6
	eSchemeSeven,	//方案7
	eSchemeEight,	//方案8
	eSchemeNine,	//方案9
};
/* 服务器定义枚举值
战士：1
法师：2
射手：3
肉盾：4
刺客：5
*/
enum ELegendType
{
	eLegendCurSelected = -1,// 当前选中的
	eLegendAll,//全部英雄
	eLegendMT=4,//肉盾
	eLegendZS=1,//战士
	eLegendSS=3,//射手
	eLegendFS=2,//法师
	eLegendCK=5,//刺客
	eLegendFZ=6//辅助
};

//道具列表
enum EPropType
{
	ePropTypeNone =0,
	ePropYSYN = 1,//勇士余念
	ePropYLYZ = 2,//英灵意志
	ePropYXCH = 3,//英雄残魂
	ePropQWZL = 4,//器物之灵
};

//道具列表
enum EOwnType
{
	eOwnTypeNone =0,
	eOwnTypeAll		= 1,//所有
	eOwnTypeOwned	= 2,//已拥有
	eOwnTypeUnOwned	= 3,//未拥有
};

struct STProp
{
	int uiItemTypeId;//道具Id
	char   strDesc[STRING_LENGTH];//道具描述

};

//装备属性枚举名称命名使用拼音首字母,方便大家查阅
enum EEquipmentEffect
{
	eEquipmentEffectNone=0,	//默认无效果
	//攻击力						   法术强度							  生命值
	eEquipmentEffectGJL=1,			eEquipmentEffectFSQD=2,				eEquipmentEffectSMZ=3,	
	//护甲穿透						   法术穿透							  护甲
	eEquipmentEffectHJCT=4,			eEquipmentEffectFSCT=5,				eEquipmentEffectFYL=6,
	//攻击速度					    	冷却缩减						  法术抗性
	eEquipmentEffectGJSD=7,			eEquipmentEffectLQSJ=8,				eEquipmentEffectFSKX=9,	
	//物理暴击						    法力值								生命恢复
	eEquipmentEffectWLBJ=10,		eEquipmentEffectFLZ=11,				eEquipmentEffectSMHF=12,	
	//生命偷取								法力恢复							移动速度
	eEquipmentEffectSMTQ=13,			eEquipmentEffectFLHF=14,			eEquipmentEffectYDSD=15,	
};

struct STEquipment
{
	int iEquipmentId;
	int iItemOrder;
	int iDisplay;//0不显示,1显示
	int iEquipmentEffectCost;		//装备消耗金钱
	char strEquipmentEffect[STRING_LENGTH];		//效果分类
	char strEquipmentName[STRING_LENGTH];		//装备名称
	char strEquipmentIcon[STRING_LENGTH];		//装备图像
	char strItemName[STRING_LENGTH];//保存装备方案时回填信息
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
	int iLegendId;					//英雄Id
	char strLegendName[STRING_LENGTH];	//英雄名称
	char strLegendIcon[STRING_LENGTH];	//英雄头像
	int  iLevel;
	ELegendType eLegendType;			//英雄类型,默认初始换类型 eLegendMT(具体注释转到ELegendType查看)
	EHeroStatusFlag eHeroStatusFlag;	//是否拥有该英雄
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
	UINT iPos;			//装备槽位,当前模块会初始化装备位置,与其他模块对接,通过装备槽位对接装备数据
	QRect rectEquipment;//装备区域位置,仅需客户端处理,其他模块不需提供,例如：逻辑模块不用提供
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



//通俗易懂使用拼音标识
enum EGossipType
{
	// 乾qian坤kun坎kan离li震zhen艮gen巽xun兑dui
	eGossipNone =0,
	eGossipQian		=1 ,//乾
	eGossipKun		=2 ,//坤
	eGossipZhen		=3 ,//震
	eGossipXuan		=4 ,//巽
	eGossipKan		=5 ,//坎
	eGossipLi		=6 ,//离
	eGossipGen		=7 ,//艮
	eGossipDui		=8 ,//兑
	eGossipTian		=9 ,//天乾
	eGossipTu		=10 ,//土坤
	eGossipMu		=11 ,//木震
	eGossipFeng		=12 ,//风巽
	eGossipShui		=13 ,//水坎
	eGossipHuo		=14 ,//火离
	eGossipShan		=15 ,//山艮
	eGossipZe		=16,//泽兑
};

enum EGossipId
{
	eGossipIdNone = 0,
	eGossipIdOne,		//八卦1
	eGossipIdTwo,		//八卦2
	eGossipIdThree,		//八卦3
	eGossipIdFour,		//八卦4
	eGossipIdFive,		//八卦5
	eGossipIdSix,		//八卦6
	eGossipIdSeven,		//八卦7
	eGossipIdEight,		//八卦8
	eGossipIdNine,		//八卦9
};

enum EGossipItemShowType
{
	eGossipItemShowTypeNone		= 0,
	eGossipItemShowTypeLock		= 1,//未解锁
	eGossipItemShowTypeUnLock	= 2,//已经解锁，未添加东西
	eGossipItemShowTypeNormal	= 3,//解锁了有东西
	eGossipItemShowTypeDamage	= 4,//东西损坏  黄色
	eGossipItemShowTypeDestroy	= 5,//完全损坏  红色 (蒙版,待确认)
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
#pragma pack(pop)//对齐字节 出堆栈
//#pragma pack()//恢复成默认对齐方式
//#pragma pack(show)
#endif