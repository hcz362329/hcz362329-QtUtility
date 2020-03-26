#include "EquipmentEffectModule.h"
#include <QSound>
#include <QDir>
#include <QDebug>
#include <QPainter>

#define CHECKBOX_WIDTH 110
#define CHECKBOX_HEIGHT 18
#define CHECKBOX_SPACE  20

#define X_POS_1 33 
#define X_POS_2 168
#define X_POS_3 299

#define Y_POS_1 17 
#define Y_POS_2 42
#define Y_POS_3 67
#define Y_POS_4 92 
#define Y_POS_5 117

EquipmentEffectModule::EquipmentEffectModule(QWidget* parent /* = NULL */)
	: EquipmentBase(parent)
	, m_pEquipEffectCheckMapper(nullptr)
	, m_pCheckBox1(nullptr)
	, m_pCheckBox2(nullptr)
	, m_pCheckBox3(nullptr)
	, m_pCheckBox4(nullptr)
	, m_pCheckBox5(nullptr)
	, m_pCheckBox6(nullptr)
	, m_pCheckBox7(nullptr)
	, m_pCheckBox8(nullptr)
	, m_pCheckBox9(nullptr)
	, m_pCheckBox10(nullptr)
	, m_pCheckBox11(nullptr)
	, m_pCheckBox12(nullptr)
	, m_pCheckBox13(nullptr)
	, m_pCheckBox14(nullptr)
	, m_pCheckBox15(nullptr)
	, m_pEquipEffectRadioMapper(nullptr)
	, m_pRadioLabel1(nullptr)
	, m_pRadioLabel2(nullptr)
	, m_pRadioLabel3(nullptr)
	, m_pRadioLabel4(nullptr)
	, m_pRadioLabel5(nullptr)
	, m_pRadioLabel6(nullptr)
	, m_pRadioLabel7(nullptr)
	, m_pRadioLabel8(nullptr)
	, m_pRadioLabel9(nullptr)
	, m_pRadioLabel10(nullptr)
	, m_pRadioLabel11(nullptr)
	, m_pRadioLabel12(nullptr)
	, m_pRadioLabel13(nullptr)
	, m_pRadioLabel14(nullptr)
	, m_pRadioLabel15(nullptr)
{
	setMouseTracking(true);
	constructCheckBox();
	constructRadioBox();

	if ( !m_pixEffectBG.load("./Images/Setting/QxEquipment/EffectBG.png") )
	{
		qDebug()<<"load EffectBG failed!";
	}
}

EquipmentEffectModule::~EquipmentEffectModule()
{

}

void EquipmentEffectModule::constructCheckBox()
{
	//复选框
	m_pEquipEffectCheckMapper = new QSignalMapper(this);
	//攻击力						   法术强度							  生命值
	m_pCheckBox1 = new QCheckBox(this);m_pCheckBox2 = new QCheckBox(this);m_pCheckBox3 = new QCheckBox(this);
	//护甲穿透						   法术穿透							  护甲
	m_pCheckBox4 = new QCheckBox(this);m_pCheckBox5 = new QCheckBox(this);m_pCheckBox6 = new QCheckBox(this);
	//攻击速度					    	冷却缩减						  法术抗性
	m_pCheckBox7 = new QCheckBox(this);m_pCheckBox8 = new QCheckBox(this);m_pCheckBox9 = new QCheckBox(this);
	//物理暴击						    法力值								生命恢复
	m_pCheckBox10 = new QCheckBox(this);m_pCheckBox11 = new QCheckBox(this);m_pCheckBox12 = new QCheckBox(this);
	//生命偷取								法力恢复							移动速度
	m_pCheckBox13 = new QCheckBox(this);m_pCheckBox14 = new QCheckBox(this);m_pCheckBox15 = new QCheckBox(this);
	struct STEffectCheckBox
	{
		QCheckBox* pCheckBox;
		QRect rect;
		EEquipmentEffect eEquipmentEffect;
	}stEffectCheckBoxs[]={
		{m_pCheckBox1,QRect(X_POS_1,Y_POS_1,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectGJL},
		{m_pCheckBox2,QRect(X_POS_2,Y_POS_1,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFSQD},
		{m_pCheckBox3,QRect(X_POS_3,Y_POS_1,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectSMZ},
		{m_pCheckBox4,QRect(X_POS_1,Y_POS_2,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectHJCT},
		{m_pCheckBox5,QRect(X_POS_2,Y_POS_2,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFSCT},
		{m_pCheckBox6,QRect(X_POS_3,Y_POS_2,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFYL},
		{m_pCheckBox7,QRect(X_POS_1,Y_POS_3,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectGJSD},
		{m_pCheckBox8,QRect(X_POS_2,Y_POS_3,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectLQSJ},
		{m_pCheckBox9,QRect(X_POS_3,Y_POS_3,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFSKX},
		{m_pCheckBox10,QRect(X_POS_1,Y_POS_4,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectWLBJ},
		{m_pCheckBox11,QRect(X_POS_2,Y_POS_4,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFLZ},
		{m_pCheckBox12,QRect(X_POS_3,Y_POS_4,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectSMHF},
		{m_pCheckBox13,QRect(X_POS_1,Y_POS_5,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectSMTQ},
		{m_pCheckBox14,QRect(X_POS_2,Y_POS_5,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectFLHF},
		{m_pCheckBox15,QRect(X_POS_3,Y_POS_5,CHECKBOX_WIDTH,CHECKBOX_HEIGHT),eEquipmentEffectYDSD},
	};
	for ( int nIndex = 0 ;nIndex < _countof(stEffectCheckBoxs);++nIndex )
	{
		stEffectCheckBoxs[nIndex].pCheckBox->setGeometry(stEffectCheckBoxs[nIndex].rect);
		m_pEquipEffectCheckMapper->setMapping(stEffectCheckBoxs[nIndex].pCheckBox,stEffectCheckBoxs[nIndex].eEquipmentEffect);
		//stEffectCheckBoxs[nIndex].pCheckBox->hide();
		connect(stEffectCheckBoxs[nIndex].pCheckBox,SIGNAL(clicked()),m_pEquipEffectCheckMapper,SLOT(map()));
	}
	connect(m_pEquipEffectCheckMapper,SIGNAL(mapped(int)), this, SLOT(OnCheckBoxTypeClicked(int)));
}

void EquipmentEffectModule::constructRadioBox()
{
	//单选框
	m_pEquipEffectRadioMapper = new QSignalMapper(this);
	//攻击力						   法术强度							  生命值
	m_pRadioLabel1 = new QxRadioLabel(this);m_pRadioLabel2 = new QxRadioLabel(this);m_pRadioLabel3 = new QxRadioLabel(this);
	//护甲穿透						   法术穿透							  护甲
	m_pRadioLabel4 = new QxRadioLabel(this);m_pRadioLabel5 = new QxRadioLabel(this);m_pRadioLabel6 = new QxRadioLabel(this);
	//攻击速度					    	冷却缩减						  法术抗性
	m_pRadioLabel7 = new QxRadioLabel(this);m_pRadioLabel8 = new QxRadioLabel(this);m_pRadioLabel9 = new QxRadioLabel(this);
	//物理暴击						    法力值								生命恢复
	m_pRadioLabel10 = new QxRadioLabel(this);m_pRadioLabel11 = new QxRadioLabel(this);m_pRadioLabel12 = new QxRadioLabel(this);
	//生命偷取								法力恢复							移动速度
	m_pRadioLabel13 = new QxRadioLabel(this);m_pRadioLabel14 = new QxRadioLabel(this);m_pRadioLabel15 = new QxRadioLabel(this);
	struct STEffectRadioBox
	{
		QxRadioLabel* pRadioLabel;
		QRect rect;
		EEquipmentEffect eEquipmentEffect;
		QString strEffectTypeName;
	}stEffectRadioBoxs[]={
		{m_pRadioLabel1,QRect(X_POS_1+25,Y_POS_1,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectGJL,QString::fromWCharArray(L"攻击力")},
		{m_pRadioLabel2,QRect(X_POS_2+25,Y_POS_1,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFSQD,QString::fromWCharArray(L"法术强度")},
		{m_pRadioLabel3,QRect(X_POS_3+25,Y_POS_1,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectSMZ,QString::fromWCharArray(L"生命值")},
		{m_pRadioLabel4,QRect(X_POS_1+25,Y_POS_2,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectHJCT,QString::fromWCharArray(L"护甲穿透")},
		{m_pRadioLabel5,QRect(X_POS_2+25,Y_POS_2,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFSCT,QString::fromWCharArray(L"法术穿透")},
		{m_pRadioLabel6,QRect(X_POS_3+25,Y_POS_2,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFYL,QString::fromWCharArray(L"护甲")},
		{m_pRadioLabel7,QRect(X_POS_1+25,Y_POS_3,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectGJSD,QString::fromWCharArray(L"攻击速度")},
		{m_pRadioLabel8,QRect(X_POS_2+25,Y_POS_3,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectLQSJ,QString::fromWCharArray(L"冷却缩减")},
		{m_pRadioLabel9,QRect(X_POS_3+25,Y_POS_3,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFSKX,QString::fromWCharArray(L"法术抗性")},
		{m_pRadioLabel10,QRect(X_POS_1+25,Y_POS_4,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectWLBJ,QString::fromWCharArray(L"物理暴击")},
		{m_pRadioLabel11,QRect(X_POS_2+25,Y_POS_4,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFLZ,QString::fromWCharArray(L"法力值")},
		{m_pRadioLabel12,QRect(X_POS_3+25,Y_POS_4,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectSMHF,QString::fromWCharArray(L"生命恢复")},
		{m_pRadioLabel13,QRect(X_POS_1+25,Y_POS_5,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectSMTQ,QString::fromWCharArray(L"生命偷取")},
		{m_pRadioLabel14,QRect(X_POS_2+25,Y_POS_5,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectFLHF,QString::fromWCharArray(L"法力恢复")},
		{m_pRadioLabel15,QRect(X_POS_3+25,Y_POS_5,CHECKBOX_WIDTH-25,CHECKBOX_HEIGHT),eEquipmentEffectYDSD,QString::fromWCharArray(L"移动速度")},
	};
	for ( int nIndex = 0 ;nIndex < _countof(stEffectRadioBoxs);++nIndex )
	{
		stEffectRadioBoxs[nIndex].pRadioLabel->setGeometry(stEffectRadioBoxs[nIndex].rect);
		stEffectRadioBoxs[nIndex].pRadioLabel->setText(stEffectRadioBoxs[nIndex].strEffectTypeName);
		stEffectRadioBoxs[nIndex].pRadioLabel->setObjectName("radioLabel");
		m_pEquipEffectRadioMapper->setMapping(stEffectRadioBoxs[nIndex].pRadioLabel,stEffectRadioBoxs[nIndex].eEquipmentEffect);
		connect(stEffectRadioBoxs[nIndex].pRadioLabel,SIGNAL(clicked()),m_pEquipEffectRadioMapper,SLOT(map()));
	}
	connect(m_pEquipEffectRadioMapper,SIGNAL(mapped(int)), this, SLOT(OnRadioTypeClicked(int)));
}

void EquipmentEffectModule::OnRadioTypeClicked(int nCheckType)
{
	QSound::play(QDir::currentPath()+"/Sound/btn_mus_chkboxclick.wav");
	resetCheckBoxState();

	//单选,SQL查询数据库
	QVector<int> vecType;
	QCheckBox* pCheckBox = (QCheckBox*)m_pEquipEffectCheckMapper->mapping(nCheckType);
	if ( pCheckBox != nullptr )
	{
		pCheckBox->setChecked(true);
		vecType.push_back(nCheckType);
	}
	emit equipmentEffectCheckedResult(vecType);
}

void EquipmentEffectModule::OnCheckBoxTypeClicked(int nCheckType)
{
	qDebug()<<"nCheckType:"<<nCheckType;
	QVector<int> vecType;
	for (int nType = eEquipmentEffectGJL;nType<=eEquipmentEffectYDSD;++nType)
	{
		QCheckBox* pCheckBox = (QCheckBox*)m_pEquipEffectCheckMapper->mapping(nType);
		if ( pCheckBox != nullptr && pCheckBox->isChecked() )
		{
			vecType.push_back(nType);
		}
	}
	emit equipmentEffectCheckedResult(vecType);
}

void EquipmentEffectModule::resetCheckBoxState()
{
	for (int nType = eEquipmentEffectGJL;nType<=eEquipmentEffectYDSD;++nType)
	{
		QCheckBox* pCheckBox = (QCheckBox*)m_pEquipEffectCheckMapper->mapping(nType);
		if (pCheckBox != nullptr)
		{
			pCheckBox->setChecked(false);
			pCheckBox->setEnabled(true);
		}
	}
}

void EquipmentEffectModule::setCheckBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable)
{
	QCheckBox* pCheckBox = (QCheckBox*)m_pEquipEffectCheckMapper->mapping(eEquipmentEffect);
	if (pCheckBox != nullptr)
	{
		pCheckBox->setEnabled(bEnable);
	}
}

void EquipmentEffectModule::setRadioBoxEnable(EEquipmentEffect eEquipmentEffect, bool bEnable)
{
	QxRadioLabel* pRadioLabel = (QxRadioLabel*)m_pEquipEffectRadioMapper->mapping(eEquipmentEffect);
	if (pRadioLabel != nullptr)
	{
		pRadioLabel->setEnabled(bEnable);
	}
}

void EquipmentEffectModule::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
}