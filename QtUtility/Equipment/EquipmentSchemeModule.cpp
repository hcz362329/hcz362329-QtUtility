#include "EquipmentSchemeModule.h"
#include "QxEquipment.h"
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QDebug>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QDir>
#include <QSound>
#include <QMessageBox>

#define X_POS 20
#define Y_POS 206
//������������X_POS,Y_POSΪzeeplin��λ��,���������ؼ�λ�ö���
#define RecommandItemClickRlue_Enabled 0

EquipmentSchemeModule::EquipmentSchemeModule(QWidget* parent /*= NULL*/)
	: EquipmentBase(parent)
	, m_pSchemeGroup(nullptr)
	, m_pSchemeBtn1(nullptr)
	, m_pSchemeBtn2(nullptr)
	, m_pSchemeBtn3(nullptr)
	, m_pSaveSetBtn(nullptr)
	, m_pRestBtn(nullptr)
	, m_nSchemeBtnPos(eSchemeOne)
	, m_bChangeSchemeInfo(false)
	, m_uiLegendId(0)
	, m_bSaveInfoChanged(false)
	, m_bSendGetHeroSchemeReq(false)
	, m_pSchemeNameEdit(nullptr)
	, m_bDragReq(true)
{
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);

	m_pixSchemeBG.load("./Images/Setting/QxEquipment/1_9.png");
	m_pixBorder.load("./Images/Setting/QxEquipment/QxEquipmentBorder.png");
	m_pixSelect.load("./Images/Setting/QxEquipment/QxEquipmentSelect.png");
	loadSchemeBtn();

	m_pSaveSetBtn = new QPushButton("Save",this);
	m_pSaveSetBtn->setGeometry(481,52,80,30);
	m_pSaveSetBtn->setObjectName("SchemeSaveSetBtn");
	m_pSaveSetBtn->setEnabled(false);
	connect(m_pSaveSetBtn,SIGNAL(clicked()),this,SLOT(OnSaveSetBtnClicked()));

	m_pRestBtn = new QPushButton("ReSet",this);
	//m_pRestBtn->setClickSound(QDir::currentPath()+"/Sound/btn_mus_cancelreturn.wav");
	m_pRestBtn->setGeometry(391,52,80,30);
	m_pRestBtn->setObjectName("SchemeResetBtn");
	m_pRestBtn->setEnabled(false);
	connect(m_pRestBtn,SIGNAL(clicked()),this,SLOT(OnRestClicked()));
	

	//���ط������Ʊ༭
	m_pSchemeNameEdit  = new QLineEdit(this);
	m_pSchemeNameEdit->setObjectName("EquipScheme");
	m_pSchemeNameEdit->setGeometry(19,56,351,25);
	m_pSchemeNameEdit->setFocusPolicy(Qt::ClickFocus);
	m_pSchemeNameEdit->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
	m_pSchemeNameEdit->setContextMenuPolicy(Qt::NoContextMenu);
	m_pSchemeNameEdit->installEventFilter(this);
	connect(m_pSchemeNameEdit,SIGNAL(textChanged(const QString &)),this,SLOT(OnTextChanged(const QString &)));
	connect(m_pSchemeNameEdit,SIGNAL(editingFinished()),this,SLOT(OnEditingFinished()));

	initBaseData();
	//������ק����
	setAcceptDrops(true);
	//�������߼�ģ����źŲ�����
	connectLogicalSignals();
	installEventFilter(this);
}

//���߼�ģ���ź�
void EquipmentSchemeModule::connectLogicalSignals()
{
#if 0
	bool bConnect =connect(CQxFrameHelper<>::GetModule(eModuleIdLogical), 
		SIGNAL(OnRspSignal(const STGetUserHeroConfigRsp&)),
		this, SLOT(OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&)));
	if ( !bConnect )
	{
		//LOG_INFO("������ʧ��:��ȡӢ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ!");
	}

	//�����û�Ӣ��������Ϣ��Ӧ�ź�
	bool bConnect2 =connect(CQxFrameHelper<>::GetModule(eModuleIdLogical), 
		SIGNAL(OnRspSignal(const STChangeUserHeroConfigRsp&)),
		this, SLOT(OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp&)));
	if ( !bConnect2 )
	{
		//LOG_INFO("������ʧ��:�����û�Ӣ��������Ϣ��Ӧ�ź�!");
	}
#endif
	
}

void EquipmentSchemeModule::loadSchemeBtn()
{
	m_pSchemeGroup = new QButtonGroup(this);
	m_pSchemeBtn1 = new QPushButton(this);
	m_pSchemeBtn2 = new QPushButton(this);
	m_pSchemeBtn3 = new QPushButton(this);
	//m_pSchemeBtn1->setClickSound(QDir::currentPath()+"/Sound/btn_mus_Lv3click.wav");
	//m_pSchemeBtn2->setClickSound(QDir::currentPath()+"/Sound/btn_mus_Lv3click.wav");
	//m_pSchemeBtn3->setClickSound(QDir::currentPath()+"/Sound/btn_mus_Lv3click.wav");

	struct STSchemeBtn
	{
		QPushButton* pButton;
		QRect rect;
		QString strObjectName;
		EScheme eScheme;
		QString strText;
		ESide eSide;
	}stSchemeBtns[]={
		{m_pSchemeBtn1,QRect(102,3,90,30),QString("Common_Btn"),eSchemeOne,QString::fromWCharArray(L"����1"),eSideNone},
		{m_pSchemeBtn2,QRect(194,3,90,30),QString("Common_Btn"),eSchemeTwo,QString::fromWCharArray(L"����2"),eSideRight},
		{m_pSchemeBtn3,QRect(286,3,90,30),QString("Common_Btn"),eSchemeThree,QString::fromWCharArray(L"����3"),eSideRight}
	};
	for (int nIndex = 0; nIndex < _countof(stSchemeBtns);++nIndex )
	{
		stSchemeBtns[nIndex].pButton->setGeometry(stSchemeBtns[nIndex].rect);
		stSchemeBtns[nIndex].pButton->setObjectName(stSchemeBtns[nIndex].strObjectName);
		stSchemeBtns[nIndex].pButton->setStyleSheet(stSchemeBtns[nIndex].pButton->styleSheet().append(QStringLiteral("font-family: FZZhengHeiS-M-GB;")));
		stSchemeBtns[nIndex].pButton->setText(stSchemeBtns[nIndex].strText);
		stSchemeBtns[nIndex].pButton->setCheckable(true);
		stSchemeBtns[nIndex].pButton->setFocusPolicy(Qt::NoFocus);
		m_mapSchemeBtn[stSchemeBtns[nIndex].eScheme] = stSchemeBtns[nIndex].pButton;
		m_pSchemeGroup->addButton(stSchemeBtns[nIndex].pButton,stSchemeBtns[nIndex].eScheme);
	}
	connect(m_pSchemeGroup,SIGNAL(buttonClicked(int)),this,SLOT(OnSchemeBtnClicked(int)));
	m_pSchemeBtn1->setChecked(true);
}

EquipmentSchemeModule::~EquipmentSchemeModule()
{

}

void EquipmentSchemeModule::setLegendScheme(int iLegendId)
{
	////LOG_FUN("");
	////LOG_INFO("m_uiLegendId="<<iLegendId);
	m_uiLegendId = iLegendId;
	SetSendGetHeroSchemeReq(true);
}

void EquipmentSchemeModule::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	if ( !m_pixSchemeBG.isNull() )
	{
		painter.drawPixmap(19,109,m_pixSchemeBG.scaled(QSize(m_pixSchemeBG.width(),m_pixSchemeBG.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
	
	OutputSchemeInfo();
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		
		painter.drawRect(iter->rectEquipment);
		//װ����ʾ
		if ( iter->iEquipmentId > 0 )
		{
			QMap<QString,QPixmap>::iterator iterIcon = m_mapEquipmentIcon.find(QString::fromLocal8Bit(iter->strEquipmentIcon));
			if ( iterIcon != m_mapEquipmentIcon.end()  )
			{
				painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),iterIcon->scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			}
			else
			{
				QPixmap pix;
				QString strIcon = QString("./ItemIcon/")+QString::fromLocal8Bit(iter->strEquipmentIcon);
				bool bLoad = pix.load(strIcon);
				if ( bLoad )
				{
					m_mapEquipmentIcon[QString::fromLocal8Bit(iter->strEquipmentIcon)] = pix;
					painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),pix.scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
				}
				else
				{
					qDebug()<<"load pixmap in m_mapEquipmentIcon:failed!";
				}
			}
			painter.drawPixmap(iter->rectEquipment.left(),iter->rectEquipment.top(),m_pixBorder.scaled(QSize(iter->rectEquipment.width(),iter->rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		}
		iter++;
	}
	//ѡ��װ����ʶ
	if ( m_stEquipmentSet.iPos > 0 )
	{
		painter.drawPixmap(m_stEquipmentSet.rectEquipment.left(),m_stEquipmentSet.rectEquipment.top(),m_pixSelect.scaled(QSize(m_stEquipmentSet.rectEquipment.width(),m_stEquipmentSet.rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

void EquipmentSchemeModule::OnSchemeBtnClicked(int nScheme)
{
	//buttonClicked(int)ֻ����ͬһ������ ��ťѡ�з����仯ʱ�Żᴥ���ź�
	//������ťδ�仯������,�źű���Ҳ�������,������ ��ֹ�����������
	//��ť��ѡ�еİ�ťraise

	if ( m_nSchemeBtnPos != nScheme )
	{
		//���浱ǰ���������λ��װ����Ϣ
		m_mapPressedEquipmentSet[m_nSchemeBtnPos] = m_stEquipmentSet;
		//�˲��� Ӧ�����Ƿ񱣴浱ǰ�仯����,���������ȴ���Ʒ������,Ŀǰ�ڿͻ���������,���������ʱ��ע��
		if ( GetUIChanged() )
		{
			int bChangeSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
			m_mapSTEquipmentScheme[bChangeSchemeId] = m_mapSTEquipmentSet;
			//��ԭ����״̬�仯��Ϣ 
			SetUIChanged(false);
		}
		//��ťλ���ڱ��淽��֮��������¶�λ
		m_nSchemeBtnPos = nScheme;
		//��ȡ����Id
		int uiSchemeId = getSchemIdBySchemeBtnPos(nScheme);
		if ( uiSchemeId > 0 )
		{
			//��ȡ������Ϣ,���õ�ǰ�������ݣ�QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
			updateEquipmentMapSet(getEquipmentSetBySchemeId(uiSchemeId));
		}
		else
		{
			qDebug()<<QString::fromLocal8Bit("����Id:")<<uiSchemeId;
			////LOG_INFO("����Id:"<<uiSchemeId);
		}
		//��ǰ�����װ����Ϣ��ԭ����һ�ε��״̬
		m_stEquipmentSet = getSchemePressedEquipmentSetInfoBySchemePos(m_nSchemeBtnPos);

		update();
	}
	//����װ���������Ʊ༭text
	SetEditSchemeNameText();
	SetUIChanged(false);
}

int EquipmentSchemeModule::getSchemIdBySchemeBtnPos(int nBtnPos)
{
	int uiSchemeId = 0;
	if ( nBtnPos > 0 )
	{
		uiSchemeId = m_mapBtnToScheme[nBtnPos];
	}
	return uiSchemeId;
}

QMap<UINT,STEquipmentSet> EquipmentSchemeModule::getEquipmentSetBySchemeId(int uiSchemeId)
{
	return m_mapSTEquipmentScheme[uiSchemeId];
}

STEquipmentSet EquipmentSchemeModule::getSchemePressedEquipmentSetInfoBySchemePos(int nSchemePos)
{
	STEquipmentSet stEquipmentSet;
	QMap<INT,STEquipmentSet>::iterator iter = m_mapPressedEquipmentSet.find(nSchemePos);
	if ( iter != m_mapPressedEquipmentSet.end() )
	{
		stEquipmentSet = iter.value();
	}
	return stEquipmentSet;
}

void EquipmentSchemeModule::OnSaveSetBtnClicked()
{
	//��ȡ��ǰ�����ķ���Id,ͨ����ǰ������ť��ȡ
	if ( m_nSchemeBtnPos > 0 )
	{
		int operateSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
		//��ǰ������Ϣ�Ƿ������仯,�������仯�򱣴�
		if ( GetUIChanged() )
		{
			m_mapSTEquipmentScheme[operateSchemeId] = m_mapSTEquipmentSet;
			//��ԭ����״̬�仯��Ϣ 
			SetUIChanged(false);
		}
	}
	else
	{
		////LOG_INFO("������ť��������ʧ��!");
	}
	//����װ��������Ϣ
	ChangeEquipmentScheme();
}

void EquipmentSchemeModule::ChangeEquipmentScheme()
{
	////LOG_FUN("����װ������");
	////LOG_INFO("Ӣ��Id:"<<m_uiLegendId);
	//STChangeUserHeroConfigReq stChangeUserHeroConfigReq;
	//stChangeUserHeroConfigReq.uiHeroId = m_uiLegendId;
#if 0
	QMap<int,QMap<UINT,STEquipmentSet>>::iterator iter = m_mapSTEquipmentScheme.begin();
	while ( iter != m_mapSTEquipmentScheme.end() )
	{
		STEquipmentScheme stEquipmentScheme;
		stEquipmentScheme.uiId = iter.key();
		stEquipmentScheme.strName = m_mapIdToEdit[stEquipmentScheme.uiId];//getSchemeNameBySchemeId(stEquipmentScheme.uiId).toStdWString();
		////LOG_INFO("��������:"<<stEquipmentScheme.strName);
		
		if ( iter.value().size() == 9 )
		{
			QString strTotalEquipmentInfo;
			int nEquipmentNum = 0;
			for ( int nSlot = 1 ; nSlot <= EQUIPMENT_SLOT_NUM ; ++nSlot )
			{
				//��������stEquipmentScheme.strName
				STItem stItem;
				QString strName = QString::fromLocal8Bit(iter.value()[nSlot].strItemName);
				if ( strName.length() > 0 )
				{
					nEquipmentNum++;
				}
				stItem.strItemName = strName.toStdWString();
				stEquipmentScheme.vecItem.push_back(stItem);
				//��־��Ϣ
				strTotalEquipmentInfo.append(strName);
				if ( nSlot < EQUIPMENT_SLOT_NUM )
				{
					strTotalEquipmentInfo.append(",");
				}
			}
			std::wstring stdwTotal = strTotalEquipmentInfo.toStdWString();
			////LOG_INFO("װ������:"<<stdwTotal);
			////LOG_INFO("װ������,װ�����Ʋ�Ϊ�յĸ���:"<<nEquipmentNum);
		}
		else
		{
			////LOG_INFO("װ�������е�װ����Ϣ����,����С��9");
		}
		//stChangeUserHeroConfigReq.vecEquipmentScheme.push_back(stEquipmentScheme);
		++iter;
	}

	bool bResult = CQxLogicalAPIHelper<>::ChangeUserHeroConfigReq(stChangeUserHeroConfigReq);
	//���÷���
	if ( bResult )
	{

	}
#endif
}

QString EquipmentSchemeModule::getSchemeNameBySchemeId(int nScheme)
{
	QString strName;
	switch ( nScheme )
	{
	case eSchemeOne:
		strName = m_pSchemeBtn1->text();
		break;
	case eSchemeTwo:
		strName = m_pSchemeBtn2->text();
		break;
	case eSchemeThree:
		strName = m_pSchemeBtn3->text();
		break;
	default:
		break;
	}
	return strName;
}

void EquipmentSchemeModule::OnRestClicked()
{
	////LOG_FUN("");
	int nExec = QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if ( nExec == QDialog::Accepted )
	{
		if ( isEquipmentSchemeInfoChanged() )
		{
			ChangeEquipmentSchemeMapToUnSaveMap();
			setSchemeName(1,QString::fromStdWString(m_mapIdToName[1]));
			setSchemeName(2,QString::fromStdWString(m_mapIdToName[2]));
			setSchemeName(3,QString::fromStdWString(m_mapIdToName[3]));
			m_mapSTEquipmentSet = m_mapSTEquipmentScheme[m_nSchemeBtnPos];
			update();
		}
	}
#if 0
	//��ԭ����,��ԭ����һ�η���������Ϣ
	if ( m_nSchemeBtnPos > 0 )
	{
		int operateSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
		//��ǰ������Ϣ�Ƿ������仯,�������仯�򱣴�
		if ( m_bChangeSchemeInfo )
		{
			updateEquipmentMapSet(m_mapSTEquipmentScheme[operateSchemeId]);
			//��ԭ����״̬�仯��Ϣ 
			m_bChangeSchemeInfo = false;
			update();
		}
	}
	else
	{
		////LOG_INFO("������ť��������ʧ��!");
	}
#endif
	
}

void EquipmentSchemeModule::initBaseData()
{
	m_mapSTEquipmentScheme.clear();
	m_mapSTEquipmentSet.clear();
	m_mapPressedEquipmentSet.clear();
	SetUIChanged(false);
	for ( int nIndex = 1 ; nIndex < 10 ; ++nIndex )
	{
		STEquipmentSet stEquipmentSet;
		stEquipmentSet.iPos = nIndex;
		stEquipmentSet.rectEquipment = QRect(19 +(nIndex-1)*60,109,50,50);
		m_mapSTEquipmentSet[stEquipmentSet.iPos] = stEquipmentSet;
	}
	for ( int nScheme = 1; nScheme <= 3 ; ++nScheme )
	{
		//ģ�ⷽ������:3
		m_mapBtnToScheme[nScheme] = nScheme;//ģ�ⷽ��Id 1,2,3
		m_mapSTEquipmentScheme[nScheme] = m_mapSTEquipmentSet;
		STEquipmentSet stEquipmentSet;
		m_mapPressedEquipmentSet[nScheme] = stEquipmentSet;
	}
}

void EquipmentSchemeModule::mousePressEvent(QMouseEvent *event)
{
	//������õ�ǰ�����Ҫ�����װ����λ��
	if ( event->button() == Qt::LeftButton )
	{
		QSound::play(QDir::currentPath()+"/Sound/mus_equipclick.wav");
		setPressedSTEquipmentSet(event);
	}
	//�Ҽ� ж�� װ��
	if ( event->button() == Qt::RightButton )
	{
		UnLoadSTEquipmentSet(event);
	}
	EquipmentBase::mousePressEvent(event);
}

void EquipmentSchemeModule::mouseMoveEvent(QMouseEvent *event)
{
	if ( (event->buttons() & Qt::LeftButton) && GetDragReq() && m_stEquipmentSet.iEquipmentId > 0 )
	{
		int nDistance = (event->pos() - m_pDragPoint).manhattanLength();
		if ( nDistance >= QApplication::startDragDistance() )
		{
			//�������ݽ�����ק����,���ݱ����������:QMimeData
			QMimeData* mimeData = new QMimeData;
			QByteArray seEquipmentSetData;
			seEquipmentSetData.append((char*)&m_stEquipmentSet,sizeof(m_stEquipmentSet));
			mimeData->setData(QxEquipment_Inner_Drag_Data_Type,seEquipmentSetData);
			QString strPixmap = QString("./ItemIcon/")+QString::fromLocal8Bit(m_stEquipmentSet.strEquipmentIcon);
			QPixmap pixmap;
			pixmap.load(strPixmap);
			QPixmap pixResize = pixmap.scaled(QSize(44,44),Qt::KeepAspectRatio,Qt::SmoothTransformation);
			QPoint ptSpot = QPoint(pixResize.width() / 2, pixResize.height() / 2);
			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setHotSpot( ptSpot);
			drag->setPixmap(pixResize);
			drag->exec(Qt::MoveAction);
		}
	}
	LoadEquipmentInfoTip(event);
}

void EquipmentSchemeModule::LoadEquipmentInfoTip(QMouseEvent *event)
{
	STEquipmentSet stEquipmentSet;
	bool bShowTip = false;
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	QPoint pos1 = event->pos();
	//��ȡ����װ����Ϣ��λ��
	int nEquipmentPos=0;
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains(event->pos()) )
		{
			stEquipmentSet = iter.value();
			bShowTip = true;
			nEquipmentPos = stEquipmentSet.iPos;
			break;
		}
		++iter;
	}
	
	QxEquipment::getInstance()->showEquipmentTip(QPoint(95+(nEquipmentPos-1)*65,200),(STEquipment&)stEquipmentSet,bShowTip);
}

void EquipmentSchemeModule::ChangeEquipmentSchemeMapToUnSaveMap()
{
	m_mapSTEquipmentScheme = m_mapUnSaveSTEquipmentScheme;
	m_mapSTEquipmentSet = m_mapSTEquipmentScheme[m_nSchemeBtnPos];
	SetUIChanged(false);
	update();
}

void EquipmentSchemeModule::SetSendGetHeroSchemeReq(bool bSend)
{
	////LOG_FUN("");
	////LOG_INFO("���ͻ�ȡӢ�۷�������:"<<bSend);
	m_bSendGetHeroSchemeReq = bSend;
}

bool EquipmentSchemeModule::GetSendGetHeroSchemeReq()
{
	return m_bSendGetHeroSchemeReq;
}

bool EquipmentSchemeModule::GetHeroSchemeRspValid(int uiHeroId)
{
	bool bValid = false;
	if ( m_uiLegendId == uiHeroId && GetSendGetHeroSchemeReq() )
	{
		bValid = true;
	}
	return bValid;
}

void EquipmentSchemeModule::leaveEvent(QEvent *event)
{
	QxEquipment::getInstance()->hideEquipmentTip();
	EquipmentBase::leaveEvent(event);
}

void EquipmentSchemeModule::UnLoadSTEquipmentSet(QMouseEvent *event)
{
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains(event->pos()) )
		{
			//ж��װ��
			QSound::play(QDir::currentPath()+"/Sound/mus_equipchange.wav");

			iter->iEquipmentId = 0;
			memset(iter->strEquipmentEffect,0,sizeof(iter->strEquipmentEffect));
			memset(iter->strEquipmentIcon,0,sizeof(iter->strEquipmentIcon));
			memset(iter->strEquipmentName,0,sizeof(iter->strEquipmentName));
			memset(iter->strItemName,0,sizeof(iter->strItemName));
			//������Ϣ�����仯
			SetUIChanged(true);
			m_mapSTEquipmentScheme[m_nSchemeBtnPos] = m_mapSTEquipmentSet;
			break;
		}
		++iter;
	}
	update();
}

void EquipmentSchemeModule::OnEquipmentTableClicled(const STEquipment & stEquipment)
{
	//װ�����(QxEquipmentTableView:SIGNAL))-->װ������(EquipmentSetModule:SIGNAL)
	//--->·��( װ������(EquipmentSchemeModule:SLOT)
	//�жϵ�ǰװ���Ƿ��ڵ�ǰ������
	bool bExist = isEquiped(stEquipment);
	if ( !bExist )
	{
		//װ���İ�װ
		QSound::play(QDir::currentPath()+"/Sound/mus_equipchange.wav");

		if ( m_stEquipmentSet.iPos > 0 )
		{
			(STEquipment&)m_stEquipmentSet = stEquipment;
			m_mapSTEquipmentSet[m_stEquipmentSet.iPos] = m_stEquipmentSet;
			SetUIChanged(true);
			moveSelectEquipment();
		}
		else
		{
#if 1
			//�û�δָ��װ����λ��,Ĭ��װ����һ���յ�װ������
			if(setFirstEmptyEquipmentInfo(stEquipment))
			{
				m_mapSTEquipmentScheme[m_nSchemeBtnPos] = m_mapSTEquipmentSet;
				SetUIChanged(true);
			}
#endif
		}
		//װ��������Ϣ�����仯
	}
	else
	{
		int nExec = QMessageBox::information(NULL, "Title",  QString::fromWCharArray(L"��ǰ�����Ѵ��ڸ�װ��"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		
	}
	update();
}

void EquipmentSchemeModule::moveSelectEquipment()
{
	//ѡ��װ�������ڱ���������װ����˳����Һ���װ�������пհ�����
	//���ڿհ�������˳��λ�ƣ�û����ѡ��״̬��ʧ
	int nPos = m_stEquipmentSet.iPos;
	bool bFound = false;
	int nMove =  1;
	int nFound = 0;
	while ( !bFound && nMove < 9 )
	{
		int nFind = nMove + nPos > 9 ? nMove + nPos - 9 : nMove + nPos;
		QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.find(nFind);
		if ( iter != m_mapSTEquipmentSet.end() )
		{
			if ( iter->iEquipmentId > 0 )
			{
				nMove++;
			}
			else
			{
				nFound = nFind;
				bFound = true;
			}
		}
	}
	if ( bFound )
	{
		m_stEquipmentSet = m_mapSTEquipmentSet[nFound];
	}
	else
	{
		m_stEquipmentSet.iPos = 0;
	}
}

void EquipmentSchemeModule::OnRecomandEquipment(const STEquipmentSet & stEquipmentSet)
{
	STEquipment stEquipment = (STEquipment)stEquipmentSet;
#if RecommandItemClickRlue_Enabled
	if ( !isEquiped(stEquipment) )
	{
		QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.find(stEquipmentSet.iPos);
		if ( iter != m_mapSTEquipmentSet.end() )
		{
			iter->iEquipmentId = stEquipmentSet.iEquipmentId;
			iter->iEquipmentEffectCost = stEquipmentSet.iEquipmentEffectCost;
			strcpy(iter->strEquipmentEffect,stEquipmentSet.strEquipmentEffect);
			strcpy(iter->strEquipmentIcon,stEquipmentSet.strEquipmentIcon);
			strcpy(iter->strEquipmentName,stEquipmentSet.strEquipmentName);
			strcpy(iter->strItemName,stEquipmentSet.strItemName);
			//װ����Ϣ�����仯
			SetUIChanged(true);
			update();
		}
	}
	else
	{
		QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"��ǰ�����Ѵ��ڸ�װ��"), QXMSG_OK);
	}
	update();
#else
	OnEquipmentTableClicled(stEquipment);
#endif
}

void EquipmentSchemeModule::OnRecomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap)
{
	//LOG_FUN("");
	QMap<UINT,STEquipmentSet>::const_iterator iter = stEquipmentSetMap.begin();
	while ( iter != stEquipmentSetMap.end() )
	{
		QMap<UINT,STEquipmentSet>::iterator iterSet = m_mapSTEquipmentSet.find(iter->iPos);
		if ( iterSet != m_mapSTEquipmentSet.end() )
		{
			iterSet->iEquipmentId = iter->iEquipmentId;
			iterSet->iEquipmentEffectCost = iter->iEquipmentEffectCost;
			strcpy(iterSet->strEquipmentEffect,iter->strEquipmentEffect);
			strcpy(iterSet->strEquipmentIcon,iter->strEquipmentIcon);
			strcpy(iterSet->strEquipmentName,iter->strEquipmentName);
			strcpy(iterSet->strItemName,iter->strItemName);
			//װ����Ϣ�����仯
			SetUIChanged(true);
		}
		++iter;
	}
	update();
}

bool EquipmentSchemeModule::isEquipmentSchemeInfoChanged()
{
	bool bChanged = false;
	//m_mapUnSaveSTEquipmentScheme = m_mapSTEquipmentScheme;
	if ( GetUIChanged() )
	{
		m_mapSTEquipmentScheme[m_nSchemeBtnPos] = m_mapSTEquipmentSet;
		SetUIChanged(false);
	}
	if ( m_mapUnSaveSTEquipmentScheme.size() == 3 && m_mapSTEquipmentScheme.size() == 3 )
	{
		
		for ( int nScheme = 1; nScheme <= 3 ; nScheme ++ )
		{
			std::wstring str1 = m_mapIdToName[nScheme];
			QString str2 = getSchemeNameBySchemeId(nScheme);
			if ( QString::fromStdWString(str1).compare(str2) != 0 )
			{
				bChanged = true;
			}
			QMap<UINT,STEquipmentSet> UnSaveMap = m_mapUnSaveSTEquipmentScheme[nScheme];
			QMap<UINT,STEquipmentSet> UiMap = m_mapSTEquipmentScheme[nScheme];

			for ( int nSlot = 1 ; nSlot <= 9 ; nSlot ++ )
			{
				QString strUnSaveString = QString::fromLocal8Bit(UnSaveMap[nSlot].strItemName);
				QString strUiString = QString::fromLocal8Bit(UiMap[nSlot].strItemName);
				if ( strcmp(UnSaveMap[nSlot].strItemName,UiMap[nSlot].strItemName) )
				{
					bChanged = true;
				}
			}
		}
	}
	return bChanged;
}

void EquipmentSchemeModule::OnSelectLegend(const STEquipmentLegend & stEquipmentLegend)
{
	setLegendScheme(stEquipmentLegend.iLegendId);
}

bool EquipmentSchemeModule::isEquiped(const STEquipment & stEquipment)
{
	bool equip = false;
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->iEquipmentId == stEquipment.iEquipmentId )
		{
			equip = true;
		}
		++iter;
	}
	return equip;
}

bool EquipmentSchemeModule::setFirstEmptyEquipmentInfo(const STEquipment & stEquipment)
{
	bool bSet = false;
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->iPos > 0 && iter->iEquipmentId == 0 && stEquipment.iEquipmentId > 0 )
		{
			(STEquipment&)(iter.value()) = stEquipment;
			bSet = true;
			break;
		}
		++iter;
	}
	return bSet;
}

void EquipmentSchemeModule::setPressedSTEquipmentSet(QMouseEvent *event)
{
	ZeroMemory(&m_stEquipmentSet,sizeof(m_stEquipmentSet));
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains( event->pos() ))
		{
			if ( iter->iPos > 0 )
			{
				m_stEquipmentSet = iter.value();
				update();
			}
		}
		++iter;
	}
	//�������ʼ��λ��,������ק����
	m_pDragPoint = event->pos();
}

void EquipmentSchemeModule::dragEnterEvent(QDragEnterEvent *event)
{
	EquipmentBase::dragEnterEvent(event);
	if ( event->mimeData()->hasFormat(QxEquipment_Drag_Data_Type) || event->mimeData()->hasFormat(QxEquipment_Inner_Drag_Data_Type))
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void EquipmentSchemeModule::dropEvent(QDropEvent *event)
{
	//���Ƽ������͵��߱����ק������
	if ( event->mimeData()->hasFormat(QxEquipment_Drag_Data_Type) )
	{
		QStringList strFormat = event->mimeData()->formats();
		qDebug()<<"strFormat:"<<strFormat;
		const QMimeData* equipData = event->mimeData();
		QByteArray byteArray = equipData->data(QxEquipment_Drag_Data_Type);
		STEquipment* stEquiment = (STEquipment*)byteArray.data();
		if ( stEquiment->iEquipmentId > 0 )
		{
			memset(&m_stDragEquipment,0,sizeof(m_stDragEquipment));
			memcpy(&m_stDragEquipment,stEquiment,sizeof(m_stDragEquipment));
			QString strOutput = QString::fromWCharArray(L"װ��Id:").append(QString::number(stEquiment->iEquipmentId)).append(QString::fromWCharArray(L"װ������:")).append(QString::fromLocal8Bit(stEquiment->strEquipmentName));
			qDebug()<<strOutput;
			////LOG_INFO(strOutput.toStdWString());
			//��֤��ק��װ���Ƿ��Ѵ���
			if ( !isEquiped(m_stDragEquipment) )
			{
				LoadDragEquipment(event);
			}
			else
			{
				int nExec = QMessageBox::information(NULL, "Title",  QString::fromWCharArray(L"��ǰ�����Ѵ��ڸ�װ��"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			}
		}
	}
	//��ǰ�������ڲ���ק������
	if ( event->mimeData()->hasFormat(QxEquipment_Inner_Drag_Data_Type) )
	{
		QStringList strFormat = event->mimeData()->formats();
		qDebug()<<"strFormat:"<<strFormat;
		const QMimeData* innerDragData = event->mimeData();
		QByteArray byteArray = innerDragData->data(QxEquipment_Inner_Drag_Data_Type);
		STEquipmentSet* stEquipmentSet = (STEquipmentSet*)byteArray.data();
		if ( stEquipmentSet->iEquipmentId > 0 )
		{
			LoadInnerDratEquipment(*stEquipmentSet,event);
			update();
		}
	}
	
}

void EquipmentSchemeModule::LoadInnerDratEquipment(STEquipmentSet stEquipmentSet,QDropEvent *event)
{
	//ֻ�任����,λ�ò������仯
	//�ҵ�������λ��,��ȡ����λ�õ�����
	int nDstPos = 0;
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains( event->pos() ))
		{
			if ( iter->iPos > 0 )
			{
				nDstPos = iter->iPos;
			}
		}
		++iter;
	}
	if ( nDstPos > 0 && stEquipmentSet.iPos != nDstPos)
	{
		int nSrcPos = stEquipmentSet.iPos;
		OutputSchemeInfo();
		std::swap((STEquipment&)m_mapSTEquipmentSet[nSrcPos],(STEquipment&)m_mapSTEquipmentSet[nDstPos]);
		OutputSchemeInfo();
		SetUIChanged(true);
	}
}

void EquipmentSchemeModule::OutputSchemeInfo()
{
	////LOG_FUN("");
	QString strName = QString::fromLocal8Bit(m_mapSTEquipmentSet[1].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[2].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[3].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[4].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[5].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[6].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[7].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[8].strItemName) + QString(", ")+QString::fromLocal8Bit(m_mapSTEquipmentSet[9].strItemName) + QString(", ");
	std::wstring stdwName = strName.toStdWString();
	////LOG_INFO("װ����Ϣ:"<<stdwName);
}

void EquipmentSchemeModule::updateEquipmentMapSet(QMap<UINT,STEquipmentSet> mapSTEquipmentSet)
{
	m_mapSTEquipmentSet.clear();
	m_mapSTEquipmentSet = mapSTEquipmentSet;
}

void EquipmentSchemeModule::LoadDragEquipment(QDropEvent *event)
{
	QMap<UINT,STEquipmentSet>::iterator iter = m_mapSTEquipmentSet.begin();
	while ( iter != m_mapSTEquipmentSet.end() )
	{
		if ( iter->rectEquipment.contains( event->pos() ))
		{
			if ( iter->iPos > 0 )
			{
				(STEquipment&)(iter.value()) = m_stDragEquipment;
				//װ����Ϣ�����仯
				SetUIChanged(true);
				update();
			}
		}
		++iter;
	}
}

void EquipmentSchemeModule::OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp& stGetUserHeroConfigRsp)
{
#if 0
	//Ӣ�۶�Ӧ�ķ�����Ϣ���Ƽ�������Ϣ
	//���浱ǰӢ�۵ķ�����Ϣ,Ӣ�۵��Ƽ�������Ϣ�������Ƽ�װ��ģ�� RecommandModule

	//��ȡӢ��װ��������Ϣ,����
	////��ǰ������ť��Ӧ�ķ���Id : QMap<INT,int> m_mapBtnToScheme;ֱ���޸�ֵ,˳���޸�m_mapBtnToScheme[INT]=int
	////LOG_FUN("");
	if ( !GetHeroSchemeRspValid(stGetUserHeroConfigRsp.uiHeroId) )
	{
		////LOG_INFO("��ȡӢ��װ����Ϣ������Ǳ�ģ�鷢��,��������");
		return;
	}
	else
	{
		SetSendGetHeroSchemeReq(false);
	}
	initBaseData();
	for ( int nIndex = 0 ; nIndex < stGetUserHeroConfigRsp.vecEquipmentScheme.size();++nIndex )
	{
		//��ǰӢ�۵ķ���QMap<����Id,װ������>,Map[Id]
		//QMap<int,QMap<UINT,STEquipmentSet>> m_mapSTEquipmentScheme; QMap<UINT,STEquipmentSet> �е�STEquipment��Ϣ�޸�
		//���÷�������
		std::wstring str = stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].strName;
		if ( str.empty() )
		{
			str = L"Ĭ�Ϸ�����";
		}
		m_mapIdToName[nIndex+1]=str;
		m_mapIdToEdit[nIndex+1]=str;

		setSchemeName(nIndex+1,QString::fromStdWString(str));
		//���ط����е�װ����Ϣ
		QMap<int,QMap<UINT,STEquipmentSet>>::iterator iter = m_mapSTEquipmentScheme.find(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].uiId);
		if ( iter != m_mapSTEquipmentScheme.end() )
		{
			////LOG_INFO("װ��������λ����:"<<iter.value().size());
			for ( int nSlot = 0 ; nSlot < iter.value().size() && nSlot < stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem.size() ;++nSlot )
			{
				iter.value()[nSlot+1].iEquipmentId = stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem[nSlot].uiItemId;
				QString strShowName = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem[nSlot].strItemShowName);
				strcpy(iter.value()[nSlot+1].strEquipmentName,strShowName.toLocal8Bit());
				QString strEffectType = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem[nSlot].strItemTags);
				strcpy(iter.value()[nSlot+1].strEquipmentEffect,strEffectType.toLocal8Bit());
				QString strIcon = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem[nSlot].strItemIcon);
				strcpy(iter.value()[nSlot+1].strEquipmentIcon,strIcon.toLocal8Bit());
				QString strItemName = QString::fromStdWString(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].vecItem[nSlot].strItemName);
				strcpy(iter.value()[nSlot+1].strItemName,strItemName.toLocal8Bit());
				//LOG_INFO("uiEquipmentId="<<iter.value()[nSlot+1].iEquipmentId<<",strEquipmentName="<<iter.value()[nSlot+1].strEquipmentName
					<<",strEffectType="<<iter.value()[nSlot+1].strEquipmentEffect<<",strEquipmentIcon="<<iter.value()[nSlot+1].strEquipmentIcon
					<<",strItemName="<<iter.value()[nSlot+1].strItemName);
			}
		}
	}
	OnSchemeBtnClicked(m_nSchemeBtnPos);
	m_mapUnSaveSTEquipmentScheme = m_mapSTEquipmentScheme;
	m_mapSTEquipmentSet = m_mapSTEquipmentScheme[m_nSchemeBtnPos];
	//ˢ�½���
	update();
#endif
	
}

void EquipmentSchemeModule::OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp& stChangeUserHeroConfigRsp)
{
#if 0
	if ( stChangeUserHeroConfigRsp.uiErrorCode == 0 )
	{
		////LOG_INFO("װ����������ɹ�!");
		m_mapUnSaveSTEquipmentScheme = m_mapSTEquipmentScheme;
		if ( isVisible() )
		{
			QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"װ�����ñ���ɹ�"), QXMSG_OK);
		}
		SetUIChanged(false);
		m_bSaveInfoChanged = false;
		for ( int nIndex = 1 ; nIndex <= 3 ;nIndex++)
		{
			m_mapIdToName[nIndex] = getSchemeNameBySchemeId(nIndex).toStdWString();
		}
		m_mapSTEquipmentSet = m_mapUnSaveSTEquipmentScheme[m_nSchemeBtnPos];
		setSchemeName(m_nSchemeBtnPos,QString::fromStdWString(m_mapIdToName[m_nSchemeBtnPos]));
	}
	else
	{
		////LOG_INFO("װ����������ʧ��!");
		if ( isVisible() )
		{
			QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"װ�����ñ���ʧ��"), QXMSG_OK);
		}
	}
#endif
	
	SetDragReq(true);
	update();
}

void EquipmentSchemeModule::setSchemeName(int nSchemeBtnPos,QString strName)
{
	int nLength8Bit = strName.toLocal8Bit().length();
	QString strTextShow;
	if ( nLength8Bit > 10 )
	{
		QByteArray byteLocal8Bit = strName.toLocal8Bit().left(8);
		strTextShow = QString::fromLocal8Bit(byteLocal8Bit);
		strTextShow.append("...");
	}
	else
	{
		strTextShow = strName;
	}
	switch (nSchemeBtnPos)
	{
	case eSchemeOne:
		{
			m_pSchemeBtn1->setText(strTextShow);
		}
		break;
	case eSchemeTwo:
		{
			m_pSchemeBtn2->setText(strTextShow);
		}
		break;
	case eSchemeThree:
		{
			m_pSchemeBtn3->setText(strTextShow);
		}
		break;
	default:
		break;
	}
}

void EquipmentSchemeModule::hideEvent(QHideEvent *)
{
	QxEquipment::getInstance()->hideEquipmentTip();
}

bool EquipmentSchemeModule::eventFilter(QObject *obj, QEvent *event)
{
	if ( obj == m_pSchemeNameEdit )
	{
		if (event->type() == QEvent::KeyPress )
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter )
			{
				if ( NULL != m_pSchemeNameEdit->text() )
				{
					m_pSaveSetBtn->setFocus();
				}
				return true;
			}
		}
	}
	return EquipmentBase::eventFilter(obj,event);
}

void EquipmentSchemeModule::OnTextChanged(const QString &strText)
{
	int nLength8Bit = strText.toLocal8Bit().length();
	QString strTextShow;
	if ( nLength8Bit > 14 )
	{
		QByteArray byteLocal8Bit = strText.toLocal8Bit().left(14);
		strTextShow = QString::fromLocal8Bit(byteLocal8Bit);
		m_pSchemeNameEdit->setText(strTextShow);
	}
	else
	{
		strTextShow = strText;
	}

	m_mapIdToEdit[m_nSchemeBtnPos] = strText.toStdWString();
	if ( strTextShow.compare(QString::fromStdWString(m_mapIdToName[m_nSchemeBtnPos])) != 0 )
	{
		SetUIChanged(true);
		setSchemeName(m_nSchemeBtnPos,QString::fromStdWString(m_mapIdToEdit[m_nSchemeBtnPos]));
	}
}

void EquipmentSchemeModule::OnEditingFinished()
{
#if 0
	if ( m_pSchemeNameEdit != nullptr )
	{
		QString strText = m_pSchemeNameEdit->text();
		QString strId2Name = QString::fromStdWString(m_mapIdToName[m_nSchemeBtnPos]);
		if ( strId2Name.compare(strText)==0)
		{
			return;
		}
		m_mapSchemeBtn[m_nSchemeBtnPos]->setText(strText);
		ChangeEquipmentScheme();
		SetDragReq(false);
		m_pSchemeNameEdit->clearFocus();
		SetUIChanged(false);
	}
#endif
}

void EquipmentSchemeModule::SetEditSchemeNameText()
{
	QString strText = QString::fromStdWString(m_mapIdToEdit[m_nSchemeBtnPos]);
	if ( m_pSchemeNameEdit != nullptr )
	{
		m_pSchemeNameEdit->setText(strText);
	}
	
}

void EquipmentSchemeModule::SetDragReq(bool bDrag)
{
	m_bDragReq = bDrag;
}

bool EquipmentSchemeModule::GetDragReq()
{
	return m_bDragReq;
}

void EquipmentSchemeModule::SetUIChanged(bool bChange)
{
	m_bChangeSchemeInfo = bChange;
	m_pRestBtn->setEnabled(m_bChangeSchemeInfo);
	m_pSaveSetBtn->setEnabled(m_bChangeSchemeInfo);
}

bool EquipmentSchemeModule::GetUIChanged()
{
	return m_bChangeSchemeInfo;
}