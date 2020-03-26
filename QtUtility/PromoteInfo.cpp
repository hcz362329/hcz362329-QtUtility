#include "PromoteInfo.h"
#include <QPainter>
#include "RankHelp.hpp"
PromoteInfo::PromoteInfo(QWidget* parent)
	: BaseWidget(parent)
	, m_pLabelTip(nullptr)
	, m_pLabel1(nullptr)
	, m_pLabel2(nullptr)
	, m_pLabel3(nullptr)
{
	bool bLoad = m_pixBG.load("./bg_promote.png");
	resize(m_pixBG.width(),m_pixBG.height());
	m_pLabelTip		= new QLabel(this);
	m_pLabelTip->setGeometry(15,0,550,height());
	m_pLabelTip->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_pLabelTip->setStyleSheet("font-size:20px;font-family:Microsoft YaHei;color:#C9B696;");
	m_pLabel1		= new QLabel(this);
	m_pLabel1->setGeometry(571,8,20,20);
	m_pLabel2		= new QLabel(this);
	m_pLabel2->setGeometry(596,8,20,20);
	m_pLabel3		= new QLabel(this);
	m_pLabel3->setGeometry(621,8,20,20);
	
	QPixmap pixmapIcon;
	bLoad =pixmapIcon.load("./promote.png");
	m_pixWin=		pixmapIcon.copy(QRect(0,0,20,20));
	m_pixDefeat=	pixmapIcon.copy(QRect(0,20,20,20));
	m_pixDoubt=		pixmapIcon.copy(QRect(0,40,20,20));
}

PromoteInfo::~PromoteInfo()
{

}

void PromoteInfo::SetRankInfo(int score,int state)
{
	SetScore(score);
	SetRankState((ERankState)state);
}

void PromoteInfo::SetRankState(ERankState eState)
{
	bool bShow = false;
	m_pLabel1->hide();
	m_pLabel2->hide();
	m_pLabel3->hide();
	m_pLabelTip->setGeometry(15,0,550,height());
	switch (eState)
	{
	case eRankStateLargePromotion://大段晋级中
		{
			m_pLabel1->setPixmap(m_pixDoubt);
			m_pLabel2->setPixmap(m_pixDoubt);
			m_pLabel3->setPixmap(m_pixDoubt);
			m_pLabel1->show();
			m_pLabel2->show();
			m_pLabel3->show();
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为跨段晋级赛，获得2场胜利，将会晋升到");
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			bShow = true;
		}
		break;
	case eRankStateLarge110://大段晋级1胜
		{
			m_pLabel1->setPixmap(m_pixWin);
			m_pLabel2->setPixmap(m_pixDoubt);
			m_pLabel3->setPixmap(m_pixDoubt);
			m_pLabel1->show();
			m_pLabel2->show();
			m_pLabel3->show();
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为跨段晋级赛，再获得1场胜利，将会晋升到");
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			bShow = true;
		}
		break;
	case eRankStateLarge120:////大段晋级第一场失败
		{
			m_pLabel1->setPixmap(m_pixDefeat);
			m_pLabel2->setPixmap(m_pixDoubt);
			m_pLabel3->setPixmap(m_pixDoubt);
			m_pLabel1->show();
			m_pLabel2->show();
			m_pLabel3->show();
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为跨段晋级赛，获得2场胜利，将会晋升到");
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			bShow = true;
		}
		break;
	case eRankStateLarge112://大段晋级第一场胜利第二场失败
		{
			m_pLabel1->setPixmap(m_pixWin);
			m_pLabel2->setPixmap(m_pixDefeat);
			m_pLabel3->setPixmap(m_pixDoubt);
			m_pLabel1->show();
			m_pLabel2->show();
			m_pLabel3->show();
			m_pLabelTip->setGeometry(15,0,600,height());
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为跨段晋级赛，再获得1场胜利，将会晋升到");
			bShow = true;
		}
		break;
	case eRankStateLarge121:
		{
			m_pLabel1->setPixmap(m_pixDefeat);
			m_pLabel2->setPixmap(m_pixWin);
			m_pLabel3->setPixmap(m_pixDoubt);
			m_pLabel1->show();
			m_pLabel2->show();
			m_pLabel3->show();
			m_pLabelTip->setGeometry(15,0,600,height());
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为跨段晋级赛，再获得1场胜利，将会晋升到");
			bShow = true;
		}
		break;
	case eRankStateSmallPromotion://小段晋级中
		{
			m_pLabelTip->setGeometry(15,0,600,height());
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为小段晋级赛，获得一场胜利后，将会晋升到");
			m_pLabelTip->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
			bShow = true;
		}
		break;
	case eRankStateAvoidRelegation:
		{
			m_strRankInfo = QString::fromWCharArray(L"本局游戏为保级赛");
			m_pLabelTip->setAlignment(Qt::AlignCenter);
			bShow = true;
		}
		break;
	default:
		break;
	}
	if (eState>= eRankStateLargePromotion && eState <= eRankStateSmallPromotion )
	{
		QString strInfo = m_strRankInfo + m_strRankName;
		m_pLabelTip->setText(strInfo);
	}
	else
	{
		m_pLabelTip->setText(m_strRankInfo);
	}
	m_pLabelTip->show();
	if (bShow)
	{
		show();
		raise();
	}
	else
	{
		hide();
	}
}

void PromoteInfo::SetScore(int score)
{
	//根据积分计算段位
	std::wstring strName = HD::RankHelp::GetNextRankNameByScore(score);

	QString strFormat = "<span style='font-size:20px;font-family:Microsoft YaHei;color:#F5A238;'>%1</span>";
	m_strRankName = strFormat.arg(QString::fromStdWString(strName));
}

void PromoteInfo::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (!m_pixBG.isNull())
	{
		painter.drawPixmap(0,0,m_pixBG);
	}
}