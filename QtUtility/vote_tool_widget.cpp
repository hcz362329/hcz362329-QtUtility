#include "vote_tool_widget.h"
#include <QTime>
#include <QEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
const QString scrollBarStyle = QString("QScrollBar:vertical\
									{\
										width: 10px;\
										min-height: 60px;\
										margin: 0px;\
										padding: 0px;\
										background-color: transparent;\
									}\
									QScrollBar::handle:vertical\
									{\
										width: 5px;\
										min-height: 20px;\
										border: 0px;\
										border-radius: 2px;\
										background-color: rgb(65,66,70);\
									}\
									QScrollBar::sub-line:vertical\
									{\
										height: 0px;\
										border-width: 0px;\
										subcontrol-position: top;\
									}\
									QScrollBar::add-line:vertical\
									{\
										height: 0px;\
										border-width: 0px;\
										subcontrol-position: bottom;\
									}\
									QScrollBar::down-arrow:vertical, QScrollBar::up-arrow:vertical\
									{\
										background: none;\
									} \
									QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
									{\
										margin: 0px 1px 0px 1px;\
										background-color: transparent;\
									}");

const QString strListStye = QString("QListWidget{outline:0px;border:none;padding:0px;padding-top:0px; background:rgba(24,24,26,1);"
	"border-radius:2px;}"
	"QListWidget::Item{padding:0 0px;background:rgba(24,24,26,1);}"
	"QListWidget::Item:hover{background:rgba(24,24,26,0.3);padding:0 0px;}"
	"QListWidget::item:selected{background:rgba(24,24,26,0.6);padding:0 0px;}"
	"QListWidget::item:selected:!active{background:rgba(24,24,26,1);padding:0 0px;}");

const QString strCommon = QString("background-color:black;color:white;font-size:14px;");

VoteToolWidget::VoteToolWidget(QWidget* parent)
	: QDialog(parent),
	times(119),
	title(nullptr),
	tip(nullptr),
	voteTime(nullptr),
	seprateLine(nullptr),
	voteRuleWidget(nullptr),
	voteRule(nullptr),
	selectTitle(nullptr),
	resultTip(nullptr){
	//setWindowFlags(Qt::FramelessWindowHint);
	title = new QLabel(this);
	tip = new QLabel(this);
	tip->installEventFilter(this);
	voteTime = new QLabel(this);
	seprateLine = new QLabel(this);

	voteRuleWidget = new QWidget(this);
	voteRuleWidget->setFixedHeight(40);
	voteRule = new QLabel(QStringLiteral("ͶƱ\n����"), voteRuleWidget);
	voteTotalNum = new QLabel(QStringLiteral("����ͶƱӵ����Ʊ����10"), voteRuleWidget);
	voteMaxNum = new QLabel(QStringLiteral("ÿ������Ͷ��3"), voteRuleWidget);
	QHBoxLayout* hRule = new QHBoxLayout(voteRuleWidget);
	hRule->setSpacing(0);
	hRule->setContentsMargins(0, 0, 0, 0);
	hRule->addSpacing(10);
	hRule->addWidget(voteRule);
	hRule->addSpacing(10);
	hRule->addWidget(voteTotalNum);
	hRule->addSpacing(10);
	hRule->addWidget(voteMaxNum);
	hRule->addStretch();
	selectTitle = new QLabel(QStringLiteral("ѡ����֧�ֵ�����"),this);
	resultTip = new QLabel(this);
	resultTip->setAlignment(Qt::AlignLeft);
	struct STLabel {
		QLabel* label;
		QString strSyle;
		int width;
		int height;
	}stLabels[] = {
		{ title ,strCommon,0,20},
		{ tip ,strCommon,20,20 },
		{ voteTime ,strCommon,0,20 },
		{ seprateLine ,strCommon,0,1 },
		{ voteRule ,strCommon,0,40 },
		{ voteTotalNum ,strCommon,0,20 },
		{ voteMaxNum ,strCommon,0,20 },
		{ selectTitle ,strCommon,0,20 },
		{ resultTip ,strCommon,0,20 },
	};
	for (int i = 0; i < _countof(stLabels); ++i) {
		if (stLabels[i].strSyle.length() > 0)
			stLabels[i].label->setStyleSheet(stLabels[i].strSyle);
		if (stLabels[i].width > 0)
			stLabels[i].label->setFixedWidth(stLabels[i].width);
		if (stLabels[i].height > 0)
			stLabels[i].label->setFixedHeight(stLabels[i].height);
	}
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->addSpacing(10);

	QHBoxLayout* topLay = new QHBoxLayout;
	topLay->setSpacing(0);
	topLay->setContentsMargins(0, 0, 0, 0);
	topLay->addWidget(title);
	topLay->addSpacing(5);
	topLay->addWidget(tip);
	topLay->addStretch();
	topLay->addWidget(voteTime);
	vLayout->addLayout(topLay);

	vLayout->addSpacing(10);
	vLayout->addWidget(seprateLine);
	vLayout->addSpacing(10);
	vLayout->addWidget(voteRuleWidget);
	vLayout->addSpacing(10);
	vLayout->addWidget(selectTitle);
	

	listWidget = new QListWidget(this);
	listWidget->setStyleSheet(strListStye+scrollBarStyle);
	connect(listWidget,&QListWidget::itemClicked,this,&VoteToolWidget::OnItemClicked);
#if _DEBUG
	for (int i = 0; i < 6; i++) {
		VoteItem* item = new VoteItem;
		VoteChoice choice;
		choice.choiceId = QStringLiteral("%1").arg(i).toStdString();
		choice.voteNum = i;
		QString strName = QStringLiteral("ѡ��%1").arg(i);
		choice.choiceName = strName.toStdString();
		item->SetData(choice);
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setSizeHint(item->size());
		listWidget->addItem(listItem);
		listWidget->setItemWidget(listItem, item);
	}
#endif

	listWidget->setFixedHeight(200);
	vLayout->addSpacing(10);
	vLayout->addWidget(listWidget);
	vLayout->addStretch();


	QHBoxLayout* bottomLay = new QHBoxLayout;
	bottomLay->setSpacing(0);
	bottomLay->setContentsMargins(0, 0, 0, 0);
	bottomLay->addSpacing(20);
	bottomLay->addWidget(resultTip);
	bottomLay->addStretch();

	vLayout->addSpacing(10);
	vLayout->addLayout(bottomLay);
	vLayout->addSpacing(10);
	setLayout(vLayout);
	SetVoteState(READY);
}

VoteToolWidget::~VoteToolWidget() {

}

void VoteToolWidget::SetVoteState(VoteState state) {
	if (title != nullptr)
	{
		QString strTitle;
		switch (state)
		{
		case VoteToolWidget::READY:
			strTitle = QStringLiteral("ͶƱ׼����");
			break;
		case VoteToolWidget::VOTING:
			strTitle = QStringLiteral("ͶƱ������");
			break;
		case VoteToolWidget::FINISH:
			strTitle = QStringLiteral("ͶƱ�ѽ���");
			break;
		default:
			break;
		}
		title->setText(strTitle);
	}

	if (voteTime != nullptr) {
		QString strVote;
		switch (state)
		{
		case VoteToolWidget::READY:
			strVote = QStringLiteral("���뿪ʼʱ�䣺");
			break;
		case VoteToolWidget::VOTING:
			strVote = QStringLiteral("ͶƱʣ��ʱ�䣺");
			break;
		case VoteToolWidget::FINISH:
			strVote = QStringLiteral("���뱾��ͶƱ�رգ�");
			break;
		default:
			break;
		}
		QString strTime = GetTime();

		voteTime->setText(strVote+strTime);
	}
	if (resultTip != nullptr) {
		QString strResult;
		switch (state)
		{
		case VoteToolWidget::READY:
			strResult = QStringLiteral("ͶƱ������չʾ������ע��");
			break;
		case VoteToolWidget::VOTING:
			strResult = QStringLiteral("ͶƱ������չʾ������ע��");
			break;
		case VoteToolWidget::FINISH:
			strResult = QStringLiteral("����ͶƱ������ע��14");
			break;
		default:
			break;
		}
		resultTip->setText(strResult);
	}
	if (voteRuleWidget != nullptr) {
		if (voteState == FINISH) {
			voteRuleWidget->hide();
		}
		else {
			voteRuleWidget->show();
		}
	}
}

QString VoteToolWidget::GetTime() {
	QTime time(0,0,0);
	QTime t = time.addSecs(times);
	int m = t.minute();
	int s = t.second();
	QString strTime = t.toString("mm:ss");
	return strTime;
}

void VoteToolWidget::SetFollowNum(int num) {
	followNum = num ;
}

VoteToolWidget::VoteState VoteToolWidget::GetVoteState() {
	return voteState;
}

void VoteToolWidget::paintEvent(QPaintEvent* event) {
	/*QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);*/
	QDialog::paintEvent(event);
}

bool VoteToolWidget::eventFilter(QObject* obj, QEvent* event) {
	if (obj == tip) {
		if (event->type() == QEvent::Enter) {
			qDebug() << "1";
		}
		else if (event->type() == QEvent::Leave) {
			qDebug() << "2";
		}
	}
	return QDialog::eventFilter(obj, event);
}

void VoteToolWidget::OnItemClicked(QListWidgetItem* item) {
	if (listWidget != nullptr) {
		VoteItem* vote = dynamic_cast<VoteItem*>(listWidget->itemWidget(item));
		if (vote!=nullptr) {
			VoteChoice choice = vote->GetData();
			qDebug() << "id:" << choice.choiceId.data() << ",name:" << choice.choiceName.data() << ",num:" << choice.voteNum;
		}
	}
}

VoteItem::VoteItem(QWidget* parent):
	QWidget(parent) ,
	voteName(nullptr),
	voteNum(nullptr) {
	setFixedSize(200,50);
	voteName = new QLabel(this);
	voteName->setStyleSheet("color:white;");
	voteNum = new QLabel(this);
	voteName->setFixedHeight(20);
	voteNum->setFixedHeight(20);
	voteNum->setStyleSheet("color:white;");
	QHBoxLayout* hLay = new QHBoxLayout(this);
	hLay->setSpacing(0);
	hLay->setContentsMargins(0, 0, 0, 0);
	hLay->addWidget(voteName);
	hLay->addWidget(voteNum);
	hLay->addStretch();
}

VoteItem::~VoteItem() {

}

void VoteItem::SetVoteNum(int num) {
	if (num >= voteChoice.voteNum) {
		voteChoice.voteNum = num;
		QString strText = QStringLiteral("��ǰ��%1Ʊ").arg(voteChoice.voteNum);
		voteNum->setText(strText);
	}
}

void VoteItem::SetName(const std::string & name) {
	QString strText = QString("%1").arg(name.data());
	voteName->setText(strText);
}

void VoteItem::SetData(const VoteChoice & data) {
	voteChoice = data;
	SetVoteNum(voteChoice.voteNum);
	SetName(voteChoice.choiceName);
}

VoteChoice  VoteItem::GetData() {
	return voteChoice;
}