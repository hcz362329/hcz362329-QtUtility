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
//上述两个常量X_POS,Y_POS为zeeplin上位置,方便其他控件位置对齐
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
	

	//加载方案名称编辑
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
	//允许拖拽放入
	setAcceptDrops(true);
	//建立和逻辑模块的信号槽连接
	connectLogicalSignals();
	installEventFilter(this);
}

//绑定逻辑模块信号
void EquipmentSchemeModule::connectLogicalSignals()
{
#if 0
	bool bConnect =connect(CQxFrameHelper<>::GetModule(eModuleIdLogical), 
		SIGNAL(OnRspSignal(const STGetUserHeroConfigRsp&)),
		this, SLOT(OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&)));
	if ( !bConnect )
	{
		//LOG_INFO("绑定连接失败:获取英雄对应的方案信息和推荐方案信息!");
	}

	//更改用户英雄配置信息响应信号
	bool bConnect2 =connect(CQxFrameHelper<>::GetModule(eModuleIdLogical), 
		SIGNAL(OnRspSignal(const STChangeUserHeroConfigRsp&)),
		this, SLOT(OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp&)));
	if ( !bConnect2 )
	{
		//LOG_INFO("绑定连接失败:更改用户英雄配置信息响应信号!");
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
		{m_pSchemeBtn1,QRect(102,3,90,30),QString("Common_Btn"),eSchemeOne,QString::fromWCharArray(L"方案1"),eSideNone},
		{m_pSchemeBtn2,QRect(194,3,90,30),QString("Common_Btn"),eSchemeTwo,QString::fromWCharArray(L"方案2"),eSideRight},
		{m_pSchemeBtn3,QRect(286,3,90,30),QString("Common_Btn"),eSchemeThree,QString::fromWCharArray(L"方案3"),eSideRight}
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
		//装备显示
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
	//选中装备标识
	if ( m_stEquipmentSet.iPos > 0 )
	{
		painter.drawPixmap(m_stEquipmentSet.rectEquipment.left(),m_stEquipmentSet.rectEquipment.top(),m_pixSelect.scaled(QSize(m_stEquipmentSet.rectEquipment.width(),m_stEquipmentSet.rectEquipment.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

void EquipmentSchemeModule::OnSchemeBtnClicked(int nScheme)
{
	//buttonClicked(int)只有在同一个组中 按钮选中发生变化时才会触发信号
	//方案按钮未变化不处理,信号本身也不会过来,加条件 防止其它情况进入
	//按钮组选中的按钮raise

	if ( m_nSchemeBtnPos != nScheme )
	{
		//保存当前方案点击槽位的装备信息
		m_mapPressedEquipmentSet[m_nSchemeBtnPos] = m_stEquipmentSet;
		//此操作 应考虑是否保存当前变化方案,具体做法等待产品需求变更,目前在客户端做操作,保存代码暂时不注释
		if ( GetUIChanged() )
		{
			int bChangeSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
			m_mapSTEquipmentScheme[bChangeSchemeId] = m_mapSTEquipmentSet;
			//还原方案状态变化信息 
			SetUIChanged(false);
		}
		//按钮位置在保存方案之后进行重新定位
		m_nSchemeBtnPos = nScheme;
		//获取方案Id
		int uiSchemeId = getSchemIdBySchemeBtnPos(nScheme);
		if ( uiSchemeId > 0 )
		{
			//获取方案信息,设置当前方案内容：QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
			updateEquipmentMapSet(getEquipmentSetBySchemeId(uiSchemeId));
		}
		else
		{
			qDebug()<<QString::fromLocal8Bit("方案Id:")<<uiSchemeId;
			////LOG_INFO("方案Id:"<<uiSchemeId);
		}
		//当前点击的装备信息还原到上一次点击状态
		m_stEquipmentSet = getSchemePressedEquipmentSetInfoBySchemePos(m_nSchemeBtnPos);

		update();
	}
	//设置装备方案名称编辑text
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
	//获取当前操作的方案Id,通过当前方案按钮获取
	if ( m_nSchemeBtnPos > 0 )
	{
		int operateSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
		//当前方案信息是否发生过变化,发生过变化则保存
		if ( GetUIChanged() )
		{
			m_mapSTEquipmentScheme[operateSchemeId] = m_mapSTEquipmentSet;
			//还原方案状态变化信息 
			SetUIChanged(false);
		}
	}
	else
	{
		////LOG_INFO("方案按钮索引设置失败!");
	}
	//保存装备方案信息
	ChangeEquipmentScheme();
}

void EquipmentSchemeModule::ChangeEquipmentScheme()
{
	////LOG_FUN("保存装备方案");
	////LOG_INFO("英雄Id:"<<m_uiLegendId);
	//STChangeUserHeroConfigReq stChangeUserHeroConfigReq;
	//stChangeUserHeroConfigReq.uiHeroId = m_uiLegendId;
#if 0
	QMap<int,QMap<UINT,STEquipmentSet>>::iterator iter = m_mapSTEquipmentScheme.begin();
	while ( iter != m_mapSTEquipmentScheme.end() )
	{
		STEquipmentScheme stEquipmentScheme;
		stEquipmentScheme.uiId = iter.key();
		stEquipmentScheme.strName = m_mapIdToEdit[stEquipmentScheme.uiId];//getSchemeNameBySchemeId(stEquipmentScheme.uiId).toStdWString();
		////LOG_INFO("方案名称:"<<stEquipmentScheme.strName);
		
		if ( iter.value().size() == 9 )
		{
			QString strTotalEquipmentInfo;
			int nEquipmentNum = 0;
			for ( int nSlot = 1 ; nSlot <= EQUIPMENT_SLOT_NUM ; ++nSlot )
			{
				//方案名称stEquipmentScheme.strName
				STItem stItem;
				QString strName = QString::fromLocal8Bit(iter.value()[nSlot].strItemName);
				if ( strName.length() > 0 )
				{
					nEquipmentNum++;
				}
				stItem.strItemName = strName.toStdWString();
				stEquipmentScheme.vecItem.push_back(stItem);
				//日志信息
				strTotalEquipmentInfo.append(strName);
				if ( nSlot < EQUIPMENT_SLOT_NUM )
				{
					strTotalEquipmentInfo.append(",");
				}
			}
			std::wstring stdwTotal = strTotalEquipmentInfo.toStdWString();
			////LOG_INFO("装备名称:"<<stdwTotal);
			////LOG_INFO("装备个数,装备名称不为空的个数:"<<nEquipmentNum);
		}
		else
		{
			////LOG_INFO("装备方案中的装备信息有误,个数小于9");
		}
		//stChangeUserHeroConfigReq.vecEquipmentScheme.push_back(stEquipmentScheme);
		++iter;
	}

	bool bResult = CQxLogicalAPIHelper<>::ChangeUserHeroConfigReq(stChangeUserHeroConfigReq);
	//设置发送
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
	//还原配置,还原到上一次方案具体信息
	if ( m_nSchemeBtnPos > 0 )
	{
		int operateSchemeId = getSchemIdBySchemeBtnPos(m_nSchemeBtnPos);
		//当前方案信息是否发生过变化,发生过变化则保存
		if ( m_bChangeSchemeInfo )
		{
			updateEquipmentMapSet(m_mapSTEquipmentScheme[operateSchemeId]);
			//还原方案状态变化信息 
			m_bChangeSchemeInfo = false;
			update();
		}
	}
	else
	{
		////LOG_INFO("方案按钮索引设置失败!");
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
		//模拟方案个数:3
		m_mapBtnToScheme[nScheme] = nScheme;//模拟方案Id 1,2,3
		m_mapSTEquipmentScheme[nScheme] = m_mapSTEquipmentSet;
		STEquipmentSet stEquipmentSet;
		m_mapPressedEquipmentSet[nScheme] = stEquipmentSet;
	}
}

void EquipmentSchemeModule::mousePressEvent(QMouseEvent *event)
{
	//左键设置当前点击需要加入的装备的位置
	if ( event->button() == Qt::LeftButton )
	{
		QSound::play(QDir::currentPath()+"/Sound/mus_equipclick.wav");
		setPressedSTEquipmentSet(event);
	}
	//右键 卸载 装备
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
			//设置数据进入拖拽对象,数据保存对象类型:QMimeData
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
	//获取悬浮装备信息的位置
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
	////LOG_INFO("发送获取英雄方案请求:"<<bSend);
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
			//卸载装备
			QSound::play(QDir::currentPath()+"/Sound/mus_equipchange.wav");

			iter->iEquipmentId = 0;
			memset(iter->strEquipmentEffect,0,sizeof(iter->strEquipmentEffect));
			memset(iter->strEquipmentIcon,0,sizeof(iter->strEquipmentIcon));
			memset(iter->strEquipmentName,0,sizeof(iter->strEquipmentName));
			memset(iter->strItemName,0,sizeof(iter->strItemName));
			//方案信息发生变化
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
	//装备表格(QxEquipmentTableView:SIGNAL))-->装备设置(EquipmentSetModule:SIGNAL)
	//--->路线( 装备方案(EquipmentSchemeModule:SLOT)
	//判断当前装备是否在当前方案中
	bool bExist = isEquiped(stEquipment);
	if ( !bExist )
	{
		//装备的安装
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
			//用户未指定装备的位置,默认装备第一个空的装备区域
			if(setFirstEmptyEquipmentInfo(stEquipment))
			{
				m_mapSTEquipmentScheme[m_nSchemeBtnPos] = m_mapSTEquipmentSet;
				SetUIChanged(true);
			}
#endif
		}
		//装备方案信息发生变化
	}
	else
	{
		int nExec = QMessageBox::information(NULL, "Title",  QString::fromWCharArray(L"当前配置已存在该装备"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		
	}
	update();
}

void EquipmentSchemeModule::moveSelectEquipment()
{
	//选中装备栏，在表格区域加载装备后顺序查找后续装备方案中空白区域
	//存在空白区域则顺序位移，没有则选中状态消失
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
			//装备信息发生变化
			SetUIChanged(true);
			update();
		}
	}
	else
	{
		QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"当前配置已存在该装备"), QXMSG_OK);
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
			//装备信息发生变化
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
	//点击的起始点位置,用于拖拽设置
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
	//从推荐方案和道具表格拖拽的数据
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
			QString strOutput = QString::fromWCharArray(L"装备Id:").append(QString::number(stEquiment->iEquipmentId)).append(QString::fromWCharArray(L"装备名称:")).append(QString::fromLocal8Bit(stEquiment->strEquipmentName));
			qDebug()<<strOutput;
			////LOG_INFO(strOutput.toStdWString());
			//验证拖拽的装备是否已存在
			if ( !isEquiped(m_stDragEquipment) )
			{
				LoadDragEquipment(event);
			}
			else
			{
				int nExec = QMessageBox::information(NULL, "Title",  QString::fromWCharArray(L"当前配置已存在该装备"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			}
		}
	}
	//当前方案中内部拖拽的数据
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
	//只变换数据,位置不发生变化
	//找到交换的位置,获取交换位置的数据
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
	////LOG_INFO("装备信息:"<<stdwName);
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
				//装备信息发生变化
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
	//英雄对应的方案信息和推荐方案信息
	//保存当前英雄的方案信息,英雄的推荐方案信息保存在推荐装备模块 RecommandModule

	//获取英雄装备方案信息,更新
	////当前方案按钮对应的方案Id : QMap<INT,int> m_mapBtnToScheme;直接修改值,顺序修改m_mapBtnToScheme[INT]=int
	////LOG_FUN("");
	if ( !GetHeroSchemeRspValid(stGetUserHeroConfigRsp.uiHeroId) )
	{
		////LOG_INFO("获取英雄装备信息的请求非本模块发送,不做处理");
		return;
	}
	else
	{
		SetSendGetHeroSchemeReq(false);
	}
	initBaseData();
	for ( int nIndex = 0 ; nIndex < stGetUserHeroConfigRsp.vecEquipmentScheme.size();++nIndex )
	{
		//当前英雄的方案QMap<方案Id,装备方案>,Map[Id]
		//QMap<int,QMap<UINT,STEquipmentSet>> m_mapSTEquipmentScheme; QMap<UINT,STEquipmentSet> 中的STEquipment信息修改
		//设置方案名称
		std::wstring str = stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].strName;
		if ( str.empty() )
		{
			str = L"默认方案名";
		}
		m_mapIdToName[nIndex+1]=str;
		m_mapIdToEdit[nIndex+1]=str;

		setSchemeName(nIndex+1,QString::fromStdWString(str));
		//加载方案中的装备信息
		QMap<int,QMap<UINT,STEquipmentSet>>::iterator iter = m_mapSTEquipmentScheme.find(stGetUserHeroConfigRsp.vecEquipmentScheme[nIndex].uiId);
		if ( iter != m_mapSTEquipmentScheme.end() )
		{
			////LOG_INFO("装备方案槽位个数:"<<iter.value().size());
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
	//刷新界面
	update();
#endif
	
}

void EquipmentSchemeModule::OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp& stChangeUserHeroConfigRsp)
{
#if 0
	if ( stChangeUserHeroConfigRsp.uiErrorCode == 0 )
	{
		////LOG_INFO("装备方案保存成功!");
		m_mapUnSaveSTEquipmentScheme = m_mapSTEquipmentScheme;
		if ( isVisible() )
		{
			QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"装备配置保存成功"), QXMSG_OK);
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
		////LOG_INFO("装备方案保存失败!");
		if ( isVisible() )
		{
			QxMsgBox::information(CQxLobbyAPIHelper<>::GetLobbyWidget(), tr("SaveSchemeTip"), QString::fromWCharArray(L"装备配置保存失败"), QXMSG_OK);
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