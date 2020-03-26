#include "stdafx.h"
#include "QxEquipment.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QMouseEvent>
#include <QDir>
#include "BaseDataDef.h"
#include "QxEquipmentDB.h"
//#include "Log4cplusWrapper.h"

#define X_POS 0
#define Y_POS 117
#define Develop_Mode 1

QxEquipment * QxEquipment::m_pQxEquipmentObj = NULL;

QxEquipment * QxEquipment::getInstance()
{
	if ( m_pQxEquipmentObj == NULL )
	{
		//δ���ø�����
		m_pQxEquipmentObj = new QxEquipment;
	}
	return m_pQxEquipmentObj;
}
void QxEquipment::DeleteInstance()
{
	if ( m_pQxEquipmentObj != NULL )
	{
		delete m_pQxEquipmentObj;
	}
}

QxEquipment::QxEquipment(QWidget* parent /* = NULL */)
	: QWidget(parent)
	, m_pEquipmentEffectModule(nullptr)
	, m_pEquipmentTable(nullptr)
	, m_pEquipmentSimplify(nullptr)
	, m_pEquipmentAll(nullptr)
	, m_pEquipmentGroup(nullptr)
	, m_pEquipmentSetModule(nullptr)
	, m_pRecommandModule(nullptr)
	, m_pRecommandScrollBar(nullptr)
	, m_eEquipmentBtnType(eEquipmentBtnTypeSimplify)
	, m_pEquipmentTip(nullptr)
{
	setGeometry(100,100,1056,651);
	//��ʼ����������
	InitWindowFlags();
	//����ͼƬ��Դ
	InitPixmap();
	//������ʽ��
	InitStyleSheets();
	//�������ݿ�(�ڴ����ݿ�,���߱������ݿ�,������ģʽ��ʹ�ñ������ݿ�,�����汾ʹ���ڴ����ݿ�)
	consctuctData();
	//���ؿؼ�
	InitCtrls();
	//���źŲ�
	InitConnections();
	
	//����װ����ʾ
	m_pEquipmentTip = new EquipmentTip(this);
	m_pEquipmentTip->hide();
}

QxEquipment::~QxEquipment()
{
	QxEquipmentDB::deleteInstance();
	m_pQxEquipmentObj = NULL;
}

void QxEquipment::InitConnections()
{
	//����ģʽ,���е���
	if ( m_pEquipmentSimplify !=nullptr&& m_pEquipmentAll != nullptr )
	{
		connect(m_pEquipmentSimplify,SIGNAL(clicked()),this,SLOT(OnEquipmentSimplifyBtnClicked()));
		connect(m_pEquipmentAll,SIGNAL(clicked()),this,SLOT(OnEquipmentAllBtnClicked()));
	}
	if ( m_pEquipmentSetModule != nullptr && m_pEquipmentTable != nullptr )
	{
		//�Ҽ��������е�װ��
		connect(m_pEquipmentTable,&QxEquipmentTableView::equipmentTableClicled,m_pEquipmentSetModule,&EquipmentSetModule::equipmentTableClicled);
	}
	if ( m_pEquipmentSetModule != nullptr && m_pRecommandModule != nullptr )
	{
		//��Ӣ��ѡ�����ź�
		bool bConnect =connect(m_pEquipmentSetModule,&EquipmentSetModule::selectLegend,m_pRecommandModule,&RecommandModule::OnSelectLegend);
		if ( !bConnect )
		{
			////LOG_INFO("װ������ģ���װ�������Ƽ�ģ���ź�����ʧ��!");
		}
	}
}

void QxEquipment::OnEquipmentSimplifyBtnClicked()
{
	//setEffectModuleVisible(true);
	//resizeEquipmentTableHeight(QRect(665,290-Y_POS,378,370));
	//װ�������л���֮ǰ��ѡ��ѡ��״̬
	//OnCheckBoxTypeClicked(m_vecCheckType);
}

void QxEquipment::OnEquipmentAllBtnClicked()
{
	//setEffectModuleVisible(false);
	//resizeEquipmentTableHeight(QRect(665,180-Y_POS,378,444));
	//װ�������л�������ģʽѡ��״̬(һ��δѡ��Ҳ��ͬ�����и�ѡ��ѡ��)
	//updateEquipmentTable();
}

void QxEquipment::OnEquipmentBtnTypeClicked(int nEquipmentBtnType)
{
	switch ( nEquipmentBtnType )
	{
	case eEquipmentBtnTypeSimplify:
		{
			m_eEquipmentBtnType = eEquipmentBtnTypeSimplify;
		}
		break;
	case eEquipmentBtnTypeAll:
		{
			m_eEquipmentBtnType = eEquipmentBtnTypeAll;
		}
		break;
	default:
		break;
	}
	OnCheckBoxTypeClicked(m_vecCheckType);
}

void QxEquipment::InitStyleSheets()
{
	QFile file("./css/qxequipment.css");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QByteArray equipmentByte = file.readAll();
		file.close();
		setStyleSheet(styleSheet().append(equipmentByte));
	}
	else
	{
		qDebug()<<"cannot open qxequipment.css .";
	}
}

void QxEquipment::InitPixmap()
{
	//���ش��ڵ�ͼ
}

void QxEquipment::InitWindowFlags()
{
	//setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	//setAttribute(Qt::WA_TranslucentBackground);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
	installEventFilter(this);
}

void QxEquipment::InitCtrls()
{
	//���ظ�ѡ��ģ��
	m_pEquipmentEffectModule = new EquipmentEffectModule(this);
	m_pEquipmentEffectModule->setGeometry(616,148-Y_POS,412,136);
	connect(m_pEquipmentEffectModule,&EquipmentEffectModule::equipmentEffectCheckedResult,this,&QxEquipment::OnCheckBoxTypeClicked);

	//���ط������
	m_pEquipmentTable = new QxEquipmentTableView(this);
	m_pEquipmentTable->setGeometry(633,304-Y_POS,385,420);
	m_pEquipmentTable->setETable(eTableEquipment);
	m_pEquipmentTable->resizeTableContent();

	//���ؾ���ģʽ��ť,���е��߰�ť
	m_pEquipmentGroup = new QButtonGroup(this);
	m_pEquipmentSimplify	= new QPushButton(this);
	m_pEquipmentAll			= new QPushButton(this);
	//m_pEquipmentSimplify->setClickSound(QDir::currentPath()+"/Sound/btn_mus_Lv3click.wav");
	//m_pEquipmentAll->setClickSound(QDir::currentPath()+"/Sound/btn_mus_Lv3click.wav");

	struct STButton
	{
		QPushButton* pButton;
		QRect rect;
		QString srObjName;
		EEquipmentBtnType eEquipmentBtnType;
		QString strText;
	}stButtons[]={
		{m_pEquipmentSimplify,QRect(616,117-Y_POS,90,30),QString("Common_Btn"),eEquipmentBtnTypeSimplify,QString::fromWCharArray(L"����ģʽ")},
		{m_pEquipmentAll,QRect(708,117-Y_POS,90,30),QString("Common_Btn"),eEquipmentBtnTypeAll,QString::fromWCharArray(L"ȫ������")}
	};
	for (int nIndex = 0; nIndex < _countof(stButtons);++nIndex)
	{
		stButtons[nIndex].pButton->setGeometry(stButtons[nIndex].rect);
		stButtons[nIndex].pButton->setCheckable(true);
		stButtons[nIndex].pButton->setObjectName(stButtons[nIndex].srObjName);
		stButtons[nIndex].pButton->setStyleSheet(stButtons[nIndex].pButton->styleSheet().append(QStringLiteral("font-family: FZZhengHeiS-M-GB;")));
		stButtons[nIndex].pButton->setText(stButtons[nIndex].strText);
		m_pEquipmentGroup->addButton(stButtons[nIndex].pButton,stButtons[nIndex].eEquipmentBtnType);
	}
	connect(m_pEquipmentGroup, SIGNAL(buttonClicked(int)), this, SLOT(OnEquipmentBtnTypeClicked(int)));
	m_pEquipmentSimplify->setChecked(true);

	//����װ������ģ��
	m_pEquipmentSetModule = new EquipmentSetModule(this);
	m_pEquipmentSetModule->setGeometry(26,123-Y_POS,582,258);

	//����װ����������ģ���װ��ģ�������
	m_pRecommandModule = new RecommandModule(this);
	m_pRecommandModule->setGeometry(29,398-Y_POS,582,330);

	bool bConnect = connect(m_pRecommandModule,&RecommandModule::recomandEquipment,m_pEquipmentSetModule,&EquipmentSetModule::recomandEquipment);
	bool bConnect2 = connect(m_pRecommandModule,&RecommandModule::recomandEquipmentApply,m_pEquipmentSetModule,&EquipmentSetModule::recomandEquipmentApply);
	m_pRecommandScrollBar = new QScrollArea(this);
	m_pRecommandScrollBar->setGeometry(29,398-Y_POS,582,330);
	m_pRecommandScrollBar->setStyleSheet("background-color:transparent;border:0px;");
	m_pRecommandScrollBar->viewport()->setStyleSheet("background-color:transparent;");
	m_pRecommandScrollBar->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pRecommandScrollBar->setWidget(m_pRecommandModule);
	m_pRecommandScrollBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void QxEquipment::setEffectModuleVisible(bool visable)
{
	if ( m_pEquipmentEffectModule != nullptr )
	{
		m_pEquipmentEffectModule->setVisible(visable);
	}
}

void QxEquipment::resizeEquipmentTableHeight(QRect rect)
{
	if ( m_pEquipmentTable != nullptr )
	{
		m_pEquipmentTable->verticalScrollBar()->setValue(0);
		m_pEquipmentTable->setGeometry(rect);
	}
}

void QxEquipment::updateEquipmentTable(QString sql)
{
	if ( m_pEquipmentTable != nullptr )
	{
		if ( sql.isEmpty() )
		{
			if ( m_eEquipmentBtnType == eEquipmentBtnTypeSimplify )
			{
				sql = QString("select * from EquipmentEffect where ");
				QString strSimply = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����"));
				QString strOrder = QString("  order by uiItemOrder asc;");
				sql.append(strSimply).append(strOrder);
			}
			else
			{
				sql = QString("select * from EquipmentEffect order by uiItemOrder asc;");
			}
		}
		m_pEquipmentTable->updateTable(QxEquipmentDB::getInstance()->selectSTEquipmentTable(sql));
	}
}

void QxEquipment::LoadTranslator()
{

}

void QxEquipment::consctuctData()
{
	////LOG_INFO("consctuctData begin");
	QxEquipmentDB::getInstance()->createTable("EquipmentEffect");
#if Construct_Data_Enabled
	QVector<STEquipment> vecData;
	char equip1[][64]=
	{
		"ItemIcon.chitiejian","ItemIcon.fengzhoudoupeng","ItemIcon.guijiangchui","ItemIcon.jidizhanjia","ItemIcon.lieyanfazhang",
		"ItemIcon.linghuzhihuan","ItemIcon.longhunhufu","ItemIcon.longmiandoumao","ItemIcon.luoxuanfazhang","ItemIcon.qinglonghufu",
	};
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectGJL*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"������");
		strcpy(stEquipment.strEquipmentName,"������װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);

	}
	
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFSQD*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"����ǿ��");
		strcpy(stEquipment.strEquipmentName,"����ǿ��װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectSMZ*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"����ֵ");
		strcpy(stEquipment.strEquipmentName,"����ֵװ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectHJCT*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"���״�͸");
		strcpy(stEquipment.strEquipmentName,"���״�͸װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFSCT*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"������͸");
		strcpy(stEquipment.strEquipmentName,"������͸װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFYL*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"����");
		strcpy(stEquipment.strEquipmentName,"����װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectGJSD*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"�����ٶ�");
		strcpy(stEquipment.strEquipmentName,"�����ٶ�װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectLQSJ*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"��ȴ����");
		strcpy(stEquipment.strEquipmentName,"��ȴ����װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFSKX*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"��������");
		strcpy(stEquipment.strEquipmentName,"��������װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectWLBJ*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"������");
		strcpy(stEquipment.strEquipmentName,"������װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFLZ*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"����ֵ");
		strcpy(stEquipment.strEquipmentName,"����ֵװ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectSMHF*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"�����ָ�");
		strcpy(stEquipment.strEquipmentName,"�����ָ�װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectSMTQ*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"����͵ȡ");
		strcpy(stEquipment.strEquipmentName,"����͵ȡװ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectFLHF*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"�����ָ�");
		strcpy(stEquipment.strEquipmentName,"�����ָ�װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	for ( int nIndex = 0 ; nIndex < 10; ++nIndex )
	{
		STEquipment stEquipment;
		stEquipment.iEquipmentId = eEquipmentEffectYDSD*100 + nIndex;
		strcpy(stEquipment.strEquipmentEffect,"�ƶ��ٶ�");
		strcpy(stEquipment.strEquipmentName,"�ƶ��ٶ�װ��");
		strcpy(stEquipment.strEquipmentIcon,equip1[nIndex]);
		stEquipment.iEquipmentEffectCost = 2000+stEquipment.iEquipmentId;
		vecData.push_back(stEquipment);
	}
	//LOG_INFO("consctuctData end");
	qDebug()<<"construct_data size:"<<vecData.size();
	QxEquipmentDB::getInstance()->insertSTEquipmentTable(vecData);
#else
	const TSTItemMap& mapItem = CQxLogicalAPIHelper<>::GetItem();
	QVector<STEquipment> vecData;
	TSTItemMap::const_iterator iter = mapItem.cbegin();
	while ( iter != mapItem.cend() )
	{
		if ( !iter->second.strItemIcon.empty() && !iter->second.strItemName.empty() )
		{
			STEquipment stEquipment;
			stEquipment.iEquipmentId = iter->second.uiItemId;
			stEquipment.iItemOrder	 = iter->second.uiItemOrder;
			stEquipment.iDisplay   =(iter->second.bShow?1:0);
			QString strShowName = QString::fromStdWString(iter->second.strItemShowName);
			QString strEffectType = QString::fromStdWString(iter->second.strItemTags);
			QString strIcon = QString::fromStdWString(iter->second.strItemIcon);
			QString strItemName = QString::fromStdWString(iter->second.strItemName);
			strcpy(stEquipment.strEquipmentName,strShowName.toLocal8Bit());
			strcpy(stEquipment.strEquipmentEffect,strEffectType.toLocal8Bit());
			strcpy(stEquipment.strEquipmentIcon,strIcon.toLocal8Bit());
			strcpy(stEquipment.strItemName,strItemName.toLocal8Bit());
			stEquipment.iEquipmentEffectCost = iter->second.uiPrice;
			vecData.push_back(stEquipment);
			////LOG_INFO("iEquipmentId:"<<stEquipment.iEquipmentId<<",strEquipmentName"<<stEquipment.strEquipmentName<<",strEquipmentEffect"<<stEquipment.strEquipmentEffect<<",strEquipmentIcon"<<stEquipment.strEquipmentIcon<<",strItemName"<<stEquipment.strItemName);
		}
		++iter;
	}
	////LOG_INFO("��������:"<<vecData.size());
	bool bInsert = QxEquipmentDB::getInstance()->insertSTEquipmentTable(vecData);
	if ( !bInsert )
	{
		////LOG_INFO("�������ʧ��");
	}
#endif
}

void QxEquipment::InitModules()
{

}

void QxEquipment::paintEvent(QPaintEvent *)
{
	/*QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setOpacity(0.3);
	QRect rectTV = QRect(616,148-Y_POS,412,580);
	QPen penRect("#b39351");
	penRect.setWidth(2);
	QBrush brush("#000000");
	painter.setPen(penRect);
	painter.setBrush(brush);
	painter.drawRect(rectTV);
	QPen pen("#b08255");
	painter.setPen(pen);
	painter.drawLine(633,300-Y_POS,633+369,300-Y_POS);*/
}

void QxEquipment::mousePressEvent(QMouseEvent *event)
{
#if Develop_Mode
#endif
}

void QxEquipment::showEvent(QShowEvent *e)
{
	//ͬ����ѡ��enable״̬
	syncEquipmentEffectRadioBoxState();
	//ͬ����ѡ��enable״̬
	syncEquipmentEffectCheckBoxState();
	//ͬ���������
	OnCheckBoxTypeClicked(m_vecCheckType);
	//updateEquipmentTable();

	e->accept();
}

void QxEquipment::hideEvent(QHideEvent *)
{
	//m_vecCheckType.clear();
	hideEquipmentTip();
}

void QxEquipment::syncEquipmentEffectCheckBoxState()
{
	for (int nType = eEquipmentEffectGJL;nType<=eEquipmentEffectYDSD;++nType)
	{
		if (!m_vecCheckType.contains(nType))
		{
			QVector<int> vecCheckType = m_vecCheckType;
			vecCheckType.append(nType);

			QString sql = QString("select * from EquipmentEffect");
			QString strCondition;
			if ( m_eEquipmentBtnType == eEquipmentBtnTypeSimplify )
			{
				QString strSimply = QString(" where strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����"));
				sql.append(strSimply);
				strCondition.append(" and ");
			}
			else
			{
				strCondition.append(" where ");
			}

			for ( int nIndex = 0 ; nIndex < vecCheckType.size() ; ++nIndex )
			{
				const QString& strItemFilter = getSqlStringByEffectType((EEquipmentEffect)vecCheckType[nIndex]);
				strCondition.append(strItemFilter);
				if (nIndex != vecCheckType.size() - 1)
				{
					strCondition.append(" and ");
				}
			}
			sql.append(strCondition);
			sql.append(" order by uiItemOrder asc;");
			const QVector<QVariant>& vecItem = QxEquipmentDB::getInstance()->selectSTEquipmentTable(sql);
			m_pEquipmentEffectModule->setCheckBoxEnable((EEquipmentEffect)nType, (vecItem.size() > 0));
		}
	}
}

void QxEquipment::syncEquipmentEffectRadioBoxState()
{
	for (int nType = eEquipmentEffectGJL;nType<=eEquipmentEffectYDSD;++nType)
	{
		QString sql = QString("select * from EquipmentEffect");
		QString strCondition;
		if ( m_eEquipmentBtnType == eEquipmentBtnTypeSimplify )
		{
			QString strSimply = QString(" where strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����"));
			sql.append(strSimply);
			strCondition.append(" and ");
		}
		else
		{
			strCondition.append(" where ");
		}
		const QString& strItemFilter = getSqlStringByEffectType((EEquipmentEffect)nType);
		strCondition.append(strItemFilter);
		sql.append(strCondition);
		sql.append(" order by uiItemOrder asc;");
		const QVector<QVariant>& vecItem = QxEquipmentDB::getInstance()->selectSTEquipmentTable(sql);
		m_pEquipmentEffectModule->setRadioBoxEnable((EEquipmentEffect)nType, (vecItem.size() > 0));
	}
}

void QxEquipment::OnCheckBoxTypeClicked(const QVector<int>& vecType)
{
	m_vecCheckType = vecType;
	QString sql = QString("select * from EquipmentEffect");
	QString strCondition;
	if ( m_eEquipmentBtnType == eEquipmentBtnTypeSimplify )
	{
		QString strSimply = QString(" where strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����"));
		sql.append(strSimply);
		if ( vecType.size() != 0 )
		{
			strCondition.append(" and ");
		}
	}
	else
	{
		if ( vecType.size() != 0 )
		{
			strCondition.append(" where ");
		}
	}
	for ( int nIndex = 0 ; nIndex < vecType.size() ; ++nIndex )
	{
		const QString& strItemFilter = getSqlStringByEffectType((EEquipmentEffect)vecType[nIndex]);
		strCondition.append(strItemFilter);
		if (nIndex != vecType.size() - 1 )
		{
			strCondition.append(" and ");
		}
	}
	sql.append(strCondition);
	sql.append(" order by uiItemOrder asc;");
	updateEquipmentTable(sql);
	syncEquipmentEffectCheckBoxState();
}

QString QxEquipment::getSqlStringByEffectType(EEquipmentEffect eType)
{
	QString strSqlString;
	switch ( eType )
	{
	case eEquipmentEffectGJL://������
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"������"));
		break;
	case eEquipmentEffectFSQD://����ǿ�� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����ǿ��"));
		break;
	case eEquipmentEffectSMZ://����ֵ
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����ֵ"));
		break;
	case eEquipmentEffectHJCT://���״�͸ 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"���״�͸"));
		break;
	case eEquipmentEffectFSCT://������͸ 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"������͸"));
		break;
	case eEquipmentEffectFYL://���� 
		{
			//��鵱ǰɸѡ�������Ƿ���ڻ��״�͸������
			if ( IsEquipmentTypeExist(eEquipmentEffectHJCT) )
			{
				strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����"));
			}
			else
			{
				strSqlString = QString("strEquipmentEffect like '%%1%' and strEquipmentEffect not like '%%2%' ").arg(QStringLiteral("����")).arg(QStringLiteral("���״�͸"));
			}
		}
		break;
	case eEquipmentEffectGJSD://�����ٶ� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"�����ٶ�"));
		break;
	case eEquipmentEffectLQSJ://��ȴ���� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"��ȴ����"));
		break;
	case eEquipmentEffectFSKX://�������� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"��������"));
		break;
	case eEquipmentEffectWLBJ://������ 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"������"));
		break;
	case eEquipmentEffectFLZ://����ֵ 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����ֵ"));
		break;
	case eEquipmentEffectSMHF://�����ָ� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"�����ָ�"));
		break;	
	case eEquipmentEffectSMTQ://����͵ȡ 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"����͵ȡ"));
		break;
	case eEquipmentEffectFLHF://�����ָ� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"�����ָ�"));
		break;
	case eEquipmentEffectYDSD://�ƶ��ٶ� 
		strSqlString = QString("strEquipmentEffect like '%%1%'").arg(QString::fromWCharArray(L"�ƶ��ٶ�"));
		break;
	default:
		break;
	}
	return strSqlString;
}

bool QxEquipment::IsEquipmentTypeExist(int nType)
{
	bool bExist = false;
	QVector<int>::const_iterator iter = std::find_if(m_vecCheckType.begin(),m_vecCheckType.end(),
		[&](const int & nTypeIterator)->bool
	{
		return (nTypeIterator == nType );
	});
	bExist = ( iter != m_vecCheckType.end() );
	return bExist;
}

void QxEquipment::showEquipmentTip(QPoint pos,STEquipment stEquipment,bool bShow )
{
	if ( m_pEquipmentTip != nullptr )
	{
		if ( bShow && stEquipment.iEquipmentId > 0 )
		{
#if 0
			QWidget* pWidget = CQxLobbyAPIHelper<>::GetLobbyWidget();
			QPoint pMove= QPoint(pWidget->pos().rx(),pWidget->pos().ry()+110);
#endif
			
			m_pEquipmentTip->setEquipmentInfo(stEquipment);
			m_pEquipmentTip->move(pos);
			m_pEquipmentTip->show();
			m_pEquipmentTip->raise();
		}
		else
		{
			m_pEquipmentTip->hide();
		}
	}
}

void QxEquipment::hideEquipmentTip()
{
	if ( m_pEquipmentTip != nullptr )
	{
		m_pEquipmentTip->hide();
	}
}

void QxEquipment::setLegendId(DWORD dwLegendId)
{
	if ( m_pEquipmentSetModule != nullptr )
	{
		m_pEquipmentSetModule->SetLegend(dwLegendId);
	}
}

bool QxEquipment::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::WindowDeactivate || 
		event->type() == QEvent::Hide ||
		event->type() == QEvent::Leave)
	{
		m_pEquipmentTip->hide();
	}
	return QWidget::eventFilter(obj, event);
}