#include "HDTrumpet.h"

#include "Helper/QtHelper.hpp"
#include <QPainter>
HDTrumpet::HDTrumpet(QWidget * parent)
	: QWidget(parent)
	, m_pCompositeBtn(nullptr)
	, m_pFullServiceBtn(nullptr)
	, m_pSystemBtn(nullptr)
	, m_pTeamBtn(nullptr)
	, m_pShrinkBtn(nullptr)
	, m_pTeamInviteBtn(nullptr)
	, m_pSendBtn(nullptr)
	, m_pCompositeTextEdit(nullptr)
	, m_pFullServiceTextEdit(nullptr)
	, m_pSystemTextEdit(nullptr)
	, m_pTeamTextEdit(nullptr)
	, m_eTrumpetType(eTrumpetTypeComposite)
	, m_eShowType(eShowType_HomePage)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	setFixedSize(613,234);
	m_pixHomePage = QtHelper::GetTrumpetPixmap(width()-7,height()-39);
	InitCtrl();
	SetShowType(eShowType_HomePage);
}

HDTrumpet::~HDTrumpet()
{

}

void HDTrumpet::InitCtrl()
{
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setGeometry(3,height()-32,width()-5,30);
	m_pLineEdit->setStyleSheet("background:rgba(35,28,21,255);font-size:12px;font-family:Microsoft YaHei;font-weight:400;color:rgba(201,182,150,255);");
	m_pCompositeBtn				= new QPushButtonEx(this);	
	m_pFullServiceBtn			= new QPushButtonEx(this);	
	m_pSystemBtn				= new QPushButtonEx(this);		
	m_pTeamBtn					= new QPushButtonEx(this);	
	m_pShrinkBtn				= new QPushButtonEx(this);		
	m_pTeamInviteBtn			= new QPushButtonEx(this);
	m_pSendBtn					= new QPushButtonEx(this);
	
	QString strSheet = QString("QPushButton{border-width: 0;border-radius: 0;background-color:rgba(0,0,0,0);border:1px solid #9D855B;font-size:18px;font-weight:400;color:rgba(187,175,149,255);}\
							   QPushButton:checked{border-width: 0;border-radius: 0;background-color:#9D855B;font-size:18px;font-weight:400;color:rgba(242,221,186,255);}");
	
	QString strSheet_btn_zhankai = QString("QPushButton{border-width: 0;border-radius: 0;border-image: url(./homepage/btn_zhankai.png) 0 0 0 0 repeat;}");
	QString strSheetSend = QString("QPushButton{border-width: 0;border-radius: 0;border-image: url(./homepage/Btn_67x30_red1.png) 0 0 0 0 repeat;}");
	QString strFamily = QString::fromWCharArray(L"汉仪小隶书简");
	STRenderText stRenderText;
	stRenderText.fontText.setFamily(strFamily);
	stRenderText.fontText.setPixelSize(22);
	stRenderText.fontText.setBold(false);
	stRenderText.text_color = QColor(187,175,149);
	m_pGroup = new QButtonGroup(this);
	struct STBtn
	{
		QPushButtonEx* pBtn;
		QString strText;
		ETrumpetType eType;
		QRect rect;
	}stBtns[]=
	{
		{m_pCompositeBtn,QString::fromWCharArray(L"综合频道"),eTrumpetTypeComposite,QRect(4,4,99,30)},
		{m_pFullServiceBtn,QString::fromWCharArray(L"全服频道"),eTrumpetTypeFullService,QRect(4+(99+6),4,99,30)},
		{m_pSystemBtn,QString::fromWCharArray(L"系统频道"),eTrumpetTypeSystem,QRect(4+(99+6)*2,4,99,30)},
		{m_pTeamBtn,QString::fromWCharArray(L"队伍频道"),eTrumpetTypeTeam,QRect(4+(99+6)*3,4,99,30)},

		{m_pShrinkBtn,QString(""),eTrumpetTypeNone,QRect(width()-20,6,14,13)},
		{m_pTeamInviteBtn,QString::fromWCharArray(L"组队邀请"),eTrumpetTypeNone,QRect(width()-(67*2+5),height()-32,67,30)},
		{m_pSendBtn,QString(""),eTrumpetTypeNone,QRect(width()-69,height()-32,67,30)}
	};

	for ( int i = 0 ; i < _countof(stBtns) ; ++i )
	{
		stRenderText.strRenderText = stBtns[i].strText;
		
		stBtns[i].pBtn->setGeometry(stBtns[i].rect);

		if ( stBtns[i].eType != eTrumpetTypeNone )
		{
			stBtns[i].pBtn->setFocusPolicy(Qt::NoFocus);
			stBtns[i].pBtn->setCheckable(true);
			stBtns[i].pBtn->setStyleSheet(strSheet);
			m_pGroup->addButton(stBtns[i].pBtn,stBtns[i].eType);
			stRenderText.fontText.setPixelSize(22);
		}
		else
		{
			stRenderText.fontText.setPixelSize(14);
		}
		stBtns[i].pBtn->SetRenderText(stRenderText);
	}
	m_pCompositeBtn->setChecked(true);
	connect(m_pGroup,SIGNAL(buttonClicked(int)),this,SLOT(OnTrumpetTypeClicked(int)));

	m_pCompositeTextEdit	= new QTextEdit(this);
	m_pCompositeTextEdit->setGeometry(10,36,width()-20,height()-72);

	m_pFullServiceTextEdit	= new QTextEdit(this);
	m_pFullServiceTextEdit->setGeometry(10,36,width()-20,height()-72);
	m_pFullServiceTextEdit->hide();

	m_pSystemTextEdit		= new QTextEdit(this);
	m_pSystemTextEdit->setGeometry(10,36,width()-20,height()-72);
	m_pSystemTextEdit->hide();

	m_pTeamTextEdit			= new QTextEdit(this);
	m_pTeamTextEdit->setGeometry(10,36,width()-20,height()-72);
	m_pTeamTextEdit->hide();

	m_pShrinkBtn->setStyleSheet(strSheet_btn_zhankai);
	m_pSendBtn->setStyleSheet(strSheetSend);
}

void HDTrumpet::OnTrumpetTypeClicked(int nType)
{
	SetTrumpetTyle((ETrumpetType)nType);
	m_pCompositeTextEdit->setVisible(GetTrumpetType()==eTrumpetTypeComposite);
	m_pFullServiceTextEdit->setVisible(GetTrumpetType()==eTrumpetTypeFullService);
	m_pSystemTextEdit->setVisible(GetTrumpetType()==eTrumpetTypeSystem);
	m_pTeamTextEdit->setVisible(GetTrumpetType()==eTrumpetTypeTeam);
}

void HDTrumpet::SetTrumpetTyle(const ETrumpetType& eTrumpetType)
{
	m_eTrumpetType = eTrumpetType;
}

ETrumpetType HDTrumpet::GetTrumpetType()
{
	return m_eTrumpetType;
}

void HDTrumpet::SetShowType(const EShowType & type)
{
	m_eShowType = type;
	m_pTeamInviteBtn->setVisible(m_eShowType != eShowType_HomePage);
}

EShowType HDTrumpet::GetShowType()
{
	return m_eShowType;
}

void HDTrumpet::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if ( GetTrumpetType()==eTrumpetTypeComposite )
	{
		if ( !m_pixHomePage.isNull() )
		{
			painter.drawPixmap(4,3,m_pixHomePage);
		}
	}
}