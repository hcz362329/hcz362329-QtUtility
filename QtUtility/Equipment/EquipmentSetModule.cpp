#include "stdafx.h"
#include "EquipmentSetModule.h"
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#define X_POS 20
#define Y_POS 116

//上述两个常量X_POS,Y_POS为zeeplin上位置,方便其他控件位置对齐
EquipmentSetModule::EquipmentSetModule(QWidget* parent /*= NULL*/)
	: EquipmentBase(parent)
	, m_pEquipmentSchemeModule(nullptr)
	, m_pChangeHero(nullptr)
	, m_pNotChangeHero(nullptr)
{
	setMouseTracking(true);

	//加载装备方案模块
	m_pEquipmentSchemeModule = new EquipmentSchemeModule(this);
	m_pEquipmentSchemeModule->setGeometry(0,67,582,190);
	//右键点击装备表格区域
	bool bConnect = connect(this,&EquipmentSetModule::equipmentTableClicled,m_pEquipmentSchemeModule,&EquipmentSchemeModule::OnEquipmentTableClicled);
	//右键点击推荐装备栏中的推荐装备
	bool bConnect2 = connect(this,&EquipmentSetModule::recomandEquipment,m_pEquipmentSchemeModule,&EquipmentSchemeModule::OnRecomandEquipment);
	//装备栏 应用 按钮点击 应用整个装备栏中的装备
	bool bConnect3 = connect(this,&EquipmentSetModule::recomandEquipmentApply,m_pEquipmentSchemeModule,&EquipmentSchemeModule::OnRecomandEquipmentApply);
	//m_pEquipmentSchemeModule->hide();
	

	m_pChangeHero = new QPushButton(this);
	//m_pChangeHero->setClickSound(QDir::currentPath()+"/Sound/btn_mus_normalclick.wav");
	m_pChangeHero->setGeometry(485,17,80,22);
	m_pChangeHero->setObjectName("ChangeHeroBtn");

	m_pNotChangeHero = new QPushButton(this);
	//m_pNotChangeHero->setClickSound(QDir::currentPath()+"/Sound/btn_mus_normalclick.wav");
	m_pNotChangeHero->setGeometry(485,17,80,22);
	m_pNotChangeHero->setObjectName("NotChangeHeroBtn");
	m_pNotChangeHero->hide();

	connect(m_pChangeHero,SIGNAL(clicked()),this,SLOT(OnChangeHeroBtnClicked()));
	connect(m_pNotChangeHero,SIGNAL(clicked()),this,SLOT(OnNotChangeHeroBtnClicked()));

	m_pixLegend.load("./Images/Setting/QxEquipment/legendbg.png");
	//获取英雄头像资源
	
}

EquipmentSetModule::~EquipmentSetModule()
{
	
}

void EquipmentSetModule::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setOpacity(0.3);
	QPen penRect("#b39351");
	penRect.setWidth(2);
	QBrush brush("#000000");
	painter.setPen(penRect);
	painter.setBrush(brush);
	painter.drawRect(rect());
	penRect.setWidth(1);
	painter.setPen(penRect);
	painter.drawLine(2,99,580,99);
	painter.setOpacity(1);
	QPixmap head;
	head.load("./Images/Lobby/head_v4.png");
	
	
}

void EquipmentSetModule::OnChangeHeroBtnClicked()
{
	//切换到英雄选择模块,同时显示放弃更改按钮
	if ( m_pEquipmentSchemeModule != nullptr )
	{
		//装备信息是否保存
		if ( m_pEquipmentSchemeModule->isEquipmentSchemeInfoChanged() )
		{
			int nExec =QMessageBox::information(NULL, "Title", QString::fromWCharArray(L"装备方案未保存,是否保存？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				
			if ( QDialog::Accepted == nExec )
			{
				m_pEquipmentSchemeModule->ChangeEquipmentScheme();
			}
			else
			{
				m_pEquipmentSchemeModule->ChangeEquipmentSchemeMapToUnSaveMap();
			}
		}
	}
}

void EquipmentSetModule::OnNotChangeHeroBtnClicked()
{
	//切换到装备选择模块,同时显示更改英雄按钮
	
}

void EquipmentSetModule::OnSelectLegend(const STEquipmentLegend & stEquipmentLegend)
{
	if ( stEquipmentLegend.iLegendId > 0 )
	{
		m_stEquipmentLegend = stEquipmentLegend;
		//显示装备配置模块,隐藏英雄选择模块, OnNotChangeHeroBtnClicked 函数功能和此描述一致
		OnNotChangeHeroBtnClicked();
		//发送选择的英雄信息给装逼方案推荐模块
		emit selectLegend(stEquipmentLegend);
		LoadLegendPixmap(stEquipmentLegend.iLegendId);
		update();
		
	}
}

void EquipmentSetModule::SetLegend(DWORD dwLegendId)
{
	
	LoadLegendPixmap(dwLegendId);
}

void EquipmentSetModule::LoadLegendPixmap(DWORD dwLegendId)
{
	QString strPath = QString("./Images/Setting/QxEquipment/legend/%1.jpg").arg(QString::number(dwLegendId));
	m_pixLegend.load(strPath);
	update();
}