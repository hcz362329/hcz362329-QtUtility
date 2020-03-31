#include "live_time_set.h"
#include "qss.h"
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "common_msg_widget.h"
LiveTimeSet::LiveTimeSet(QWidget * parent)
	: RoundedWidget(parent)
	, pLablTitle(nullptr)
	, pBtnClose(nullptr)
	, pLiveTitleEdit(nullptr)
	, pTipBtn(nullptr)
	, pLabelTimeTip(nullptr)
	, pBtnNotLive(nullptr)
	, pBtnLive(nullptr)
	, m_bLeftBtnPress(false)
	, pLiveItemsVLayout(nullptr)
	, pLiveTimeCount(nullptr)
	, pLiveTimeCountTip(nullptr)
	, pLiveTimeCountTip2(nullptr)
	, nEditItem(0)
	, pTimeSpecify(nullptr)
{
	setWindowFlags(Qt::FramelessWindowHint);
	pLablTitle = new QLabel(this);
	pLablTitle->setFixedHeight(22);
	pLablTitle->setText(QStringLiteral("我的开播设置"));
	//pLablTitle->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	pLablTitle->setStyleSheet("font-size:16px;font-family:PingFangSC-Medium, PingFang SC;font-weight:500;color:rgba(255,255,255,255);line-height:22px;");
	pBtnClose = new QPushButton(this);
	pBtnClose->setFixedSize(22, 22);
	pBtnClose->setStyleSheet(strStyleButtonSet.arg(":/res/Resources/images/close_0.png").arg(":/res/Resources/images/close_1.png").arg(":/res/Resources/images/close_1.png"));
	QHBoxLayout* pLayoutTitle = new QHBoxLayout;
	pLayoutTitle->setContentsMargins(0, 0, 0, 0);
	pLayoutTitle->addSpacing(10);
	pLayoutTitle->addWidget(pLablTitle);
	pLayoutTitle->addStretch();
	pLayoutTitle->addWidget(pBtnClose);
	pLayoutTitle->addSpacing(10);
	QVBoxLayout* pMainLayout = new QVBoxLayout;
	pMainLayout->setContentsMargins(0, 0, 0, 0);
	pMainLayout->addSpacing(10);
	pMainLayout->addLayout(pLayoutTitle);

	//分割线
	QLabel* pSeparateLine = new QLabel(this);
	pSeparateLine->setFixedHeight(1);
	QHBoxLayout* pLineLayout = new QHBoxLayout;
	pLineLayout->setContentsMargins(0, 0, 0, 0);
	pSeparateLine->setStyleSheet("background:#313131;");
	pLineLayout->addWidget(pSeparateLine);
	pMainLayout->addSpacing(5);
	pMainLayout->addLayout(pLineLayout);
	//开播标题
	QLabel* pLiveTitle = new QLabel(QStringLiteral("填写开播标题"), this);
	pLiveTitle->setStyleSheet("font-size:12px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:17px; ");
	pLiveTitle->setFixedHeight(17);
	QHBoxLayout* pLiveTitleLayout = new QHBoxLayout;
	pLiveTitleLayout->setContentsMargins(0, 0, 0, 0);
	pLiveTitleLayout->addSpacing(10);
	pLiveTitleLayout->addWidget(pLiveTitle);
	pLiveTitleLayout->addStretch();

	pMainLayout->addSpacing(5);
	pMainLayout->addLayout(pLiveTitleLayout);
	//标题内容
	pLiveTitleEdit = new QLineEdit(this);
	pLiveTitleEdit->setFixedHeight(36);
	pLiveTitleEdit->setMaxLength(50);
	pLiveTitleEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLiveTitleEdit->setPlaceholderText(QStringLiteral("好的标题更能吸引用户～"));
	pLiveTitleEdit->setStyleSheet("padding:0px 8px 0px 8px;border:none;background:rgb(21,21,21);font-size:14px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:16px; ");
	QHBoxLayout* pLiveTitleEditLayout = new QHBoxLayout;
	pLiveTitleEditLayout->addSpacing(6);
	pLiveTitleEditLayout->addWidget(pLiveTitleEdit);
	pLiveTitleEditLayout->addSpacing(6);

	pMainLayout->addSpacing(3);
	pMainLayout->addLayout(pLiveTitleEditLayout);
	

	QLabel* pLiveTimeTitle = new QLabel(QStringLiteral("填写开播时间(非必填)"), this);
	pLiveTimeTitle->setFixedHeight(17);
	pLiveTimeTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLiveTimeTitle->setStyleSheet("font-size:12px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:17px;");
	pTipBtn = new QPushButton(this);
	pTipBtn->setFixedSize(14, 14);
	pTipBtn->setStyleSheet(strStyleButtonSet.arg(":/res/Resources/images/tip_live_set.png").arg(":/res/Resources/images/tip_live_set.png").arg(":/res/Resources/images/tip_live_set.png"));
	pTipBtn->installEventFilter(this);

	pLiveTimeCount = new QPushButton(QStringLiteral("+添加 (3/3)"),this);
	pLiveTimeCount->setFixedHeight(17);
	pLiveTimeCount->setStyleSheet("background:rgba(255,255,255,0);font-size:12px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(178,178,180);line-height:17px;");
	pLiveTimeCount->installEventFilter(this);

	pLiveTimeCountTip = new QPushButton(this);
	pLiveTimeCountTip->setStyleSheet("border-image:url(:/res/Resources/images/add_tip.png);");
	pLiveTimeCountTip->setGeometry(414, 159, 110, 30);

	pLiveTimeCountTip2 = new QLabel(QStringLiteral("最多添加3个时间"), pLiveTimeCountTip);
	pLiveTimeCountTip2->setFixedHeight(17);
	pLiveTimeCountTip2->setGeometry(10, 10, 95, 16);
	pLiveTimeCountTip2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLiveTimeCountTip2->setStyleSheet("font-size:11px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(178,178,178,255);line-height:16px;");
	
	pLiveTimeCountTip->hide();
	
	QHBoxLayout* pLayoutTimeTip = new QHBoxLayout;
	pLayoutTimeTip->setContentsMargins(0, 0, 0, 0);
	pLayoutTimeTip->addSpacing(10);
	pLayoutTimeTip->addWidget(pLiveTimeTitle);
	pLayoutTimeTip->addSpacing(0);
	pLayoutTimeTip->addWidget(pTipBtn);
	pLayoutTimeTip->addStretch();
	pLayoutTimeTip->addWidget(pLiveTimeCount);
	pLayoutTimeTip->addSpacing(10);

	pMainLayout->addSpacing(6);
	pMainLayout->addLayout(pLayoutTimeTip);

	pLabelTimeTip = new QLabel(this);
	pLabelTimeTip->setGeometry(119,157,259,137);
	pLabelTimeTip->setStyleSheet("background:rgba(255,255,255,0);background-image:url(:/res/Resources/images/live_tip.png);");
	pLabelTimeTip->hide();
	
	/////items////
	pLiveItemsVLayout = new QVBoxLayout;
	pLiveItemsVLayout->setContentsMargins(0, 0, 0, 0);
	pLiveItemsVLayout->setSpacing(3);
	pMainLayout->addLayout(pLiveItemsVLayout);
	//////////////
	pMainLayout->addStretch();
	pBtnNotLive = new QPushButton(this);
	pBtnNotLive->setFixedSize(104,35);
	pBtnNotLive->setStyleSheet(strStyleButtonSet.arg(":/res/Resources/images/not_live_0.png").arg(":/res/Resources/images/not_live_1.png").arg(":/res/Resources/images/not_live_1.png"));
	pBtnLive = new QPushButton(this);
	pBtnLive->setFixedSize(105, 35);
	pBtnLive->setStyleSheet(strStyleButtonSet.arg(":/res/Resources/images/ensure_live_0.png").arg(":/res/Resources/images/ensure_live_1.png").arg(":/res/Resources/images/ensure_live_1.png"));
	
	
	QHBoxLayout* pBtnLayout = new QHBoxLayout;
	pBtnLayout->setContentsMargins(0, 0, 0, 0);
	pBtnLayout->addStretch();
	pBtnLayout->addWidget(pBtnNotLive);
	pBtnLayout->addSpacing(23);
	pBtnLayout->addWidget(pBtnLive);
	pBtnLayout->addSpacing(10);

	pMainLayout->addLayout(pBtnLayout);
	pMainLayout->addSpacing(18);
	setLayout(pMainLayout);

	connect(pBtnNotLive, &QPushButton::clicked, this, [=] {
		OnBtnClicked(eLiveSetBtnCancle);
	}, Qt::UniqueConnection);
	connect(pBtnLive, &QPushButton::clicked, this, [=] {
		OnBtnClicked(eLiveSetBtnOk);
	}, Qt::UniqueConnection);
	connect(pBtnClose, &QPushButton::clicked, this, [=] {
		OnBtnClicked(eLiveSetBtnClose);
	}, Qt::UniqueConnection);
	connect(pLiveTitleEdit,&QLineEdit::textChanged,this,&LiveTimeSet::OnTextChangeSlot);
}

LiveTimeSet::~LiveTimeSet() 
{
	
}

void LiveTimeSet::OnTextChangeSlot(const QString & text)
{
	qDebug() << "text:" << text;

}

void LiveTimeSet::OnBtnClicked(ELiveSetBtn eBtn)
{
	switch (eBtn)
	{
	case eLiveSetBtnClose:
	{
		close();
	}
		break;
	case eLiveSetBtnOk:
		break;
	case eLiveSetBtnCancle:
		break;
	default:
		break;
	}
}

void LiveTimeSet::OnItemEditSot(const int& index)
{
	nEditItem = index;
	if (pTimeSpecify==nullptr)
	{
		pTimeSpecify = new TimeSpecify(this);
		pTimeSpecify->setGeometry(87,24,360,298);
	}
	pTimeSpecify->show();
	pTimeSpecify->raise();
}

bool LiveTimeSet::eventFilter(QObject *watched, QEvent *event)
{
	if (pTipBtn==watched && pLabelTimeTip!=nullptr)
	{
		if (event->type() == QEvent::Enter)
		{
			pLabelTimeTip->show();
			pLabelTimeTip->raise();
		}
		else if (event->type() == QEvent::Leave)
		{
			pLabelTimeTip->hide();
		}
	}
	else if (pLiveTimeCount == watched && pLiveTimeCountTip != nullptr)
	{
		if (event->type() == QEvent::Enter)
		{
			pLiveTimeCountTip->show();
			pLiveTimeCountTip->raise();
		}
		else if (event->type() == QEvent::Leave)
		{
			pLiveTimeCountTip->hide();
		}
	}
	return RoundedWidget::eventFilter(watched, event);
}

void LiveTimeSet::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QRect rectMainTop(0, 0, rect().width(), 30);
		if (rectMainTop.contains(event->pos()))
		{
			m_bLeftBtnPress = true;
			m_relativeInit = event->globalPos() - pos();
		}
	}
	RoundedWidget::mousePressEvent(event);
}

void LiveTimeSet::mouseReleaseEvent(QMouseEvent *e)
{
	m_bLeftBtnPress = false;
	RoundedWidget::mouseReleaseEvent(e);
}

void LiveTimeSet::mouseMoveEvent(QMouseEvent *e)
{
	if (m_bLeftBtnPress)
	{
		QPoint move_pos = e->globalPos();
		QPoint move_to = move_pos - m_relativeInit;
		move(move_to);
	}
	RoundedWidget::mouseMoveEvent(e);
}

void LiveTimeSet::AddLiveStartEndTime(const STLiveTime& stLiveTime)
{
	if (mapIndex2Item.size()<3)
	{
		LiveTimeItem* pItem = new LiveTimeItem(this);
		connect(pItem,SIGNAL(sigEdit(const int&)),this,SLOT(OnItemEditSot(const int&)));
		pItem->setFixedSize(533, 36);
		int size_ = mapIndex2Item.size();
		if (pLiveItemsVLayout !=nullptr )
		{
			pLiveItemsVLayout->addWidget(pItem);
		}
	}
}

////item line 
const QString strItemLabel = QString("background-color:rgba(46,47,51,255);border-radius:2px;");
const QString strItemText = QString("font-size:12px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgba(255,255,255,153);line-height:17px;");
const QString strTimeText = QString("font-size:12px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(255,255,255,255);line-height:17px; ");
const QString strBtn = QString("QPushButton{border-image:url(%1);}QPushButton::hover{border-image:url(%2);background-color:rgba(255,255,255,60);}QPushButton::pressed{border-image:url(%3);background-color:rgba(255,255,255,60);}");
LiveTimeItem::LiveTimeItem(QWidget * parent)
	: QWidget(parent)
	, pLabelBg(nullptr)
	, pStartTime(nullptr)
	, pEndTime(nullptr)
	, pBtnEdit(nullptr)
	, pBtnDelete(nullptr)
	, nIndex(0)
{
	resize(533,36);
	pLabelBg = new QLabel(this);
	pLabelBg->setGeometry(0,0,289,36);
	pLabelBg->setStyleSheet(strItemLabel);

	QHBoxLayout* pLayout = new QHBoxLayout;
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(19);
	QLabel* pOpen = new QLabel(QStringLiteral("开播时间:"),this);
	pOpen->setFixedSize(55,17);
	pOpen->setStyleSheet(strItemText);
	pLayout->addWidget(pOpen);
	pStartTime = new QLabel("00:000000000",this);
	pStartTime->setFixedSize(59,17);
	pStartTime->setStyleSheet(strTimeText);
	pStartTime->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLayout->addWidget(pStartTime);
	QLabel* pEnd = new QLabel(QStringLiteral("结束时间:"), this);
	pEnd->setFixedSize(55, 17);
	pEnd->setStyleSheet(strItemText);
	pLayout->addWidget(pEnd);
	pEndTime = new QLabel("00:000000000",this);
	pEndTime->setFixedSize(88,17);
	pEndTime->setStyleSheet(strTimeText);
	pEndTime->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	pLayout->addWidget(pEndTime);
	pLayout->addSpacing(8);
	pBtnEdit = new QPushButton(this);
	pBtnEdit->setFixedSize(20,20);
	pBtnEdit->setStyleSheet(strBtn.arg(":/res/Resources/images/edit.png").arg(":/res/Resources/images/edit.png").arg(":/res/Resources/images/edit.png"));
	pLayout->addWidget(pBtnEdit);
	pLayout->addSpacing(6);
	pBtnDelete = new QPushButton(this);
	pBtnDelete->setFixedSize(20, 18);
	pBtnDelete->setStyleSheet(strBtn.arg(":/res/Resources/images/clear.png").arg(":/res/Resources/images/clear.png").arg(":/res/Resources/images/clear.png"));
	pLayout->addWidget(pBtnDelete);
	pLayout->addStretch();

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	pVLayout->setContentsMargins(0, 0, 0, 0);
	pVLayout->addLayout(pLayout);

	auto edit_slot = [=]() {
		OnBtnClicked(eLiveSetBtnEdit);
	};
	auto delete_slot{ [=]() {
		OnBtnClicked(eLiveSetBtnDelete);
	} };
	connect(pBtnEdit,&QPushButton::clicked, edit_slot);
	connect(pBtnDelete, &QPushButton::clicked, delete_slot);
}

LiveTimeItem::~LiveTimeItem()
{

}

void LiveTimeItem::SetIndex(int index)
{
	nIndex = index;
}

void LiveTimeItem::OnBtnClicked(ELiveSetBtn eBtn)
{
	switch (eBtn)
	{
	case eLiveSetBtnEdit:
	{
		emit sigEdit(nIndex);
	}
		break;
	case eLiveSetBtnDelete:
	{
		int nExec = CommonMsgWidget::information(nullptr, QStringLiteral("确定删除开播时间?"), eMsgCancleOk);
		qDebug() << "nExec:" << nExec;
	}
		break;
	default:
		break;
	}
}

TimeSpecify::TimeSpecify(QWidget* parent)
	:QWidget(parent)
	,pViewStart(nullptr)
	,pViewStop(nullptr)
{
	resize(360,298);
	QLabel* pLabel = new QLabel(this);
	pLabel->setGeometry(0, 0, 360, 298);
	pLabel->setStyleSheet("background:white;");
	QLabel* pLabelTitle = new QLabel(QStringLiteral("直播时间："),this);
	pLabelTitle->setAlignment(Qt::AlignLeft);
	pLabelTitle->setFixedHeight(22);
	pLabelTitle->setStyleSheet("color:#333333;font-size:16px;font-family:PingFangSC-Medium, PingFang SC;font-weight:500;line-height:22px;");
	QLabel* pLabelTitle2 = new QLabel(QStringLiteral("请选择时间"), this);
	pLabelTitle2->setStyleSheet("color:#999999;font-size:16px;font-family:PingFangSC-Medium, PingFang SC;font-weight:500;line-height:22px;");
	pLabelTitle2->setFixedHeight(22);
	pLabelTitle2->setAlignment(Qt::AlignLeft);
	QHBoxLayout* pLayout = new QHBoxLayout;
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(14);
	pLayout->addWidget(pLabelTitle);
	pLayout->addWidget(pLabelTitle2);
	pLayout->addStretch();
	QVBoxLayout* pMainLayout = new QVBoxLayout;
	pMainLayout->setContentsMargins(0, 0, 0, 0);
	pMainLayout->addSpacing(14);
	pMainLayout->addLayout(pLayout);

	QLabel* pStartTimeDisplay = new QLabel(QStringLiteral("开播时间"),this);
	QLabel* pStopTimeDisplay = new QLabel(QStringLiteral("关播时间"), this);
	QLabel* pStartTime = new QLabel(this);
	QLabel* pSeprate		= new QLabel(this);
	QLabel* pStopTime = new QLabel(this);
	pStartTimeDisplay->setAlignment(Qt::AlignCenter);
	pStopTimeDisplay->setAlignment(Qt::AlignCenter);
	pStartTime->setAlignment(Qt::AlignCenter);
	pStopTime->setAlignment(Qt::AlignCenter);
	pStartTime->setText("00:00");
	pStopTime->setText("00:00");

	pStartTimeDisplay->setFixedSize(154, 22);
	pStopTimeDisplay->setFixedSize(154, 22);
	pStartTime->setFixedSize(154, 36);
	pSeprate->setFixedSize(12,1);
	pStopTime->setFixedSize(154, 36);

	pStartTimeDisplay->setStyleSheet(QString("font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(167,167,167);line-height:22px;"));
	pStopTimeDisplay->setStyleSheet(QString(";font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(167,167,167);line-height:22px;"));
	pStartTime->setStyleSheet(QString("font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:600;color:rgb(51,51,51);line-height:22px;"));
	pSeprate->setStyleSheet(QString("background-color:#E0E0E0"));
	pStopTime->setStyleSheet(QString("font-size:16px;font-family:PingFangSC-Regular,PingFang SC;font-weight:600;color:rgb(51,51,51);line-height:22px;"));
	QHBoxLayout* pLayoutLine2 = new QHBoxLayout;
	pLayoutLine2->setContentsMargins(0, 0, 0, 0);
	pLayoutLine2->addSpacing(20);
	pLayoutLine2->addWidget(pStartTimeDisplay);
	pLayoutLine2->addSpacing(12);
	pLayoutLine2->addWidget(pStopTimeDisplay);
	pLayoutLine2->addSpacing(20);
	pMainLayout->addSpacing(10);
	pMainLayout->addLayout(pLayoutLine2);

	QHBoxLayout* pLayoutLine3 = new QHBoxLayout;
	pLayoutLine3->setContentsMargins(0, 0, 0, 0);
	pLayoutLine3->addSpacing(20);
	pLayoutLine3->addWidget(pStartTime);
	pLayoutLine3->addWidget(pSeprate);
	pLayoutLine3->addWidget(pStopTime);
	pLayoutLine3->addSpacing(20);
	pMainLayout->addSpacing(5);
	pMainLayout->addLayout(pLayoutLine3);

	pViewStart = new View(this);
	pViewStart->setFixedSize(160, 90);
	QVector<int> vecHour1;
	vecHour1 << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21 << 22 << 23;
	pViewStart->updateAll(vecHour1);
	pViewStart->SetMaxStep(vecHour1.size() - 3);


	pViewStop = new View(this);
	pViewStop->setFixedSize(160, 90);
	QVector<int> vecHour;
	vecHour << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21 << 22 << 23 << 24 << 25 << 26 << 27 << 28 << 29 << 30 << 31 << 32 << 33 << 34 << 35 << 36 << 37 << 38 << 39 << 40 << 41 << 42 << 43 << 44 << 45 << 46 << 47 << 48 << 49 << 50 << 51 << 52 << 53 << 54 << 55 << 56 << 57 << 58 << 59;
	pViewStop->updateAll(vecHour);
	pViewStop->SetMaxStep(vecHour.size() - 3);

	auto slot_view1 = [=](const int & value) {
		pStartTime->setText(QString::number(value));
	};
	auto slot_view2 = [=](const int & value) {
		pStopTime->setText(QString::number(value));
	};
	QObject::connect(pViewStart, &View::sigSelect, slot_view1);
	QObject::connect(pViewStop, &View::sigSelect, slot_view2);

	QHBoxLayout* pLayoutView = new QHBoxLayout;
	pLayoutView->setContentsMargins(0, 0, 0, 0);
	pLayoutView->addSpacing(20);
	pLayoutView->addWidget(pViewStart);
	pLayoutView->addSpacing(0);
	pLayoutView->addWidget(pViewStop);
	pLayoutView->addSpacing(20);
	pMainLayout->addSpacing(1);
	pMainLayout->addLayout(pLayoutView);

	QLabel* pSeprateLine2 = new QLabel(this);
	pSeprateLine2->setStyleSheet("background:#E0E0E0;");
	pSeprateLine2->setGeometry(0,167,360,1);

	pMainLayout->addSpacing(20);

	QPushButton* pBtnCancle = new QPushButton(QStringLiteral("取消"),this);
	pBtnCancle->setStyleSheet("QPushButton{border:none;background-color:rgba(255,255,255,0);font-size:17px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(92,92,92);line-height:24px;}QPushButton::hover{background-color:rgba(255,255,255,60);}");
	pBtnCancle->setFixedSize(179, 40);
	QLabel* pSeprate3 = new QLabel(this);
	pSeprate3->setGeometry(180, 167, 1, 40);
	pSeprate3->setStyleSheet("background:#E0E0E0;");
	QPushButton* pBtnOk = new QPushButton(QStringLiteral("确定"), this);
	pBtnOk->setStyleSheet("QPushButton{border:none;background-color:rgba(255,255,255,0);font-size:17px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(255,28,117);line-height:24px;}QPushButton::hover{border:none;background-color:rgba(255,255,255,255);font-size:17px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(255,28,117);line-height:24px;}");
	pBtnOk->setFixedSize(179, 40);
	pMainLayout->addSpacing(0);
	QHBoxLayout* pLayoutBtn = new QHBoxLayout;
	pLayoutBtn->setContentsMargins(0, 0, 0, 0);
	pLayoutBtn->addWidget(pBtnCancle);
	pLayoutBtn->addSpacing(2);
	pLayoutBtn->addWidget(pBtnOk);
	pMainLayout->addLayout(pLayoutBtn);
	pMainLayout->addStretch();
	setLayout(pMainLayout);
}

TimeSpecify::~TimeSpecify()
{

}

void TimeSpecify::OnBtnClicked(ELiveSetBtn eBtn)
{
	switch (eBtn)
	{
	case eLiveSetBtnClose:
		break;
	case eLiveSetBtnOk:
		break;
	case eLiveSetBtnCancle:
		break;
	default:
		break;
	}
}