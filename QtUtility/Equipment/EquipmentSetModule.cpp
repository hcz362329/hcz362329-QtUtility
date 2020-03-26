#include "stdafx.h"
#include "EquipmentSetModule.h"
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#define X_POS 20
#define Y_POS 116

//������������X_POS,Y_POSΪzeeplin��λ��,���������ؼ�λ�ö���
EquipmentSetModule::EquipmentSetModule(QWidget* parent /*= NULL*/)
	: EquipmentBase(parent)
	, m_pEquipmentSchemeModule(nullptr)
	, m_pChangeHero(nullptr)
	, m_pNotChangeHero(nullptr)
{
	setMouseTracking(true);

	//����װ������ģ��
	m_pEquipmentSchemeModule = new EquipmentSchemeModule(this);
	m_pEquipmentSchemeModule->setGeometry(0,67,582,190);
	//�Ҽ����װ���������
	bool bConnect = connect(this,&EquipmentSetModule::equipmentTableClicled,m_pEquipmentSchemeModule,&EquipmentSchemeModule::OnEquipmentTableClicled);
	//�Ҽ�����Ƽ�װ�����е��Ƽ�װ��
	bool bConnect2 = connect(this,&EquipmentSetModule::recomandEquipment,m_pEquipmentSchemeModule,&EquipmentSchemeModule::OnRecomandEquipment);
	//װ���� Ӧ�� ��ť��� Ӧ������װ�����е�װ��
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
	//��ȡӢ��ͷ����Դ
	
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
	//�л���Ӣ��ѡ��ģ��,ͬʱ��ʾ�������İ�ť
	if ( m_pEquipmentSchemeModule != nullptr )
	{
		//װ����Ϣ�Ƿ񱣴�
		if ( m_pEquipmentSchemeModule->isEquipmentSchemeInfoChanged() )
		{
			int nExec =QMessageBox::information(NULL, "Title", QString::fromWCharArray(L"װ������δ����,�Ƿ񱣴棿"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				
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
	//�л���װ��ѡ��ģ��,ͬʱ��ʾ����Ӣ�۰�ť
	
}

void EquipmentSetModule::OnSelectLegend(const STEquipmentLegend & stEquipmentLegend)
{
	if ( stEquipmentLegend.iLegendId > 0 )
	{
		m_stEquipmentLegend = stEquipmentLegend;
		//��ʾװ������ģ��,����Ӣ��ѡ��ģ��, OnNotChangeHeroBtnClicked �������ܺʹ�����һ��
		OnNotChangeHeroBtnClicked();
		//����ѡ���Ӣ����Ϣ��װ�Ʒ����Ƽ�ģ��
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