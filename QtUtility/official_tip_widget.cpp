#include "official_tip_widget.h"
#include "gift_flowlight_manager.h"
#include <QTimerEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#define WIDTH 212
#define HEIGHT 120
#define ANIMATION_WIDTH 212
#define ANIMATION_HEIGHT 78
OfficialTipWidget::OfficialTipWidget(QWidget* parent):
	QDialog(parent),
	time_count_(0),
	timer_(0),
	type_(TYPE_OPEN),
	animation_widget_(nullptr),
	title_(nullptr),
	content_(nullptr),
	time_display_(nullptr),
	animation_in_(nullptr),
	animation_out_(nullptr)
{
	setWindowFlags(Qt::WindowMinMaxButtonsHint |Qt::WindowCloseButtonHint);
	resize(WIDTH, HEIGHT);
	QLabel* pLabel = new QLabel(this);
	pLabel->setGeometry(0, 0, WIDTH, HEIGHT);
	pLabel->setStyleSheet("background:transparent;");
	animation_widget_ = new QWidget(this);
	animation_widget_->setGeometry(0, -ANIMATION_HEIGHT, ANIMATION_WIDTH, ANIMATION_HEIGHT);
	QLabel* label = new QLabel(animation_widget_);
	label->setGeometry(0, 0, ANIMATION_WIDTH, ANIMATION_HEIGHT);
	label->setStyleSheet("background:rgba(0,0,0,178);border-radius:4px;");

	title_ = new QLabel(QStringLiteral("即将开始轮麦"),animation_widget_);
	title_->setFixedHeight(20);
	title_->setStyleSheet("background:transparent;font-size:14px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgb(255,255,255);line-height:20px;");
	title_->setAlignment(Qt::AlignLeft);
	content_ = new QLabel(animation_widget_);
	QString strFormat = QString("<span style='font-size:11px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgba(255, 255, 255,128);line-height:16px; '>%1</span>");
	strFormat = strFormat.arg(QStringLiteral("轮麦时间:"));
	QString strFormat2 = QString("<span style='font-size:11px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:16px; '>%1</span>");
	strFormat2 = strFormat2.arg(QStringLiteral("22:00-22:15"));
	content_->setText(strFormat+ strFormat2);
	content_->setFixedHeight(20);
	content_->setAlignment(Qt::AlignLeft);
	content_->setStyleSheet("background:transparent;");

	QLabel* line = new QLabel(animation_widget_);
	line->setFixedSize(1, ANIMATION_HEIGHT);
	line->setStyleSheet("background:rgba(255,255,255,25);");
	time_display_ = new QLabel(animation_widget_);
	time_display_->setFixedWidth(60);
	time_display_->setAlignment(Qt::AlignCenter);
	time_display_->setStyleSheet("background:transparent;font-size:24px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgb(255, 43, 107);line-height:33px;");
	QHBoxLayout* hlayout = new QHBoxLayout;
	hlayout->setContentsMargins(0, 0, 0, 0);
	QVBoxLayout* vlayout = new QVBoxLayout;
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->addSpacing(12);
	vlayout->addWidget(title_);
	vlayout->addSpacing(4);
	vlayout->addWidget(content_);
	vlayout->addSpacing(12);

	hlayout->addSpacing(12);
	hlayout->addLayout(vlayout);
	hlayout->addStretch();
	hlayout->addWidget(line);
	hlayout->addWidget(time_display_);
	//hlayout->addStretch();
	animation_widget_->setLayout(hlayout);

	QVariantList list;
	list << QVariant(QPoint(0, -ANIMATION_HEIGHT)) << QVariant(QPoint(0, HEIGHT - ANIMATION_HEIGHT));
	QVariantAnimation::KeyValues key2value;
	animation_in_ = Mgr::GetPropertyAnimation(animation_widget_,this,Mgr::TYPE_POS, list, key2value,200);
	QVariantList list2;
	list2 << QVariant(QPoint(0, HEIGHT-ANIMATION_HEIGHT)) << QVariant(QPoint(0, - ANIMATION_HEIGHT));
	animation_out_= Mgr::GetPropertyAnimation(animation_widget_, this, Mgr::TYPE_POS, list2, key2value, 200);
#if 1
	QPushButton* btn = new QPushButton("test", this);
	btn->setGeometry(0, HEIGHT, 100, 20);
	static int n = 1;
	auto TypeSlot = [&]() {
		n = n % 2;
		OfficialTipWidget::TipType type = (OfficialTipWidget::TipType)n;
		n++;
		SetTipType(type);
	};
	QObject::connect(btn, &QPushButton::clicked, TypeSlot);
#endif
}

OfficialTipWidget::~OfficialTipWidget() {

}

void OfficialTipWidget::timerEvent(QTimerEvent* event) {
	if (event->timerId() == timer_) {
		if (time_count_ == 0) {
			StopTimer();
			StartAnimationOut();
			return;
		}
		time_count_--;
		time_display_->setText(QString::number(time_count_)+QString("s"));
	}
}

void OfficialTipWidget::StartTimer() {
	if (timer_ != 0) {
		StopTimer();
	}
	timer_ = startTimer(1000);
}

void OfficialTipWidget::StopTimer() {
	if (timer_ != 0) {
		killTimer(timer_);
		timer_ = 0;
	}
}

void OfficialTipWidget::StartAnimationIn() {
	if (animation_in_ != nullptr) {
		animation_in_->start();
	}
}

void OfficialTipWidget::StartAnimationOut() {
	if (animation_out_ != nullptr) {
		animation_out_->start();
	}
}

void OfficialTipWidget::SetTipType(TipType type){
	type_ = type;
	
	if (type == TYPE_OPEN) {
		time_count_ = 15;
		title_->setText(QStringLiteral("即将开始轮麦"));
		QString strFormat = QString("<span style='font-size:11px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgba(255, 255, 255,128);line-height:16px; '>%1</span>");
		strFormat = strFormat.arg(QStringLiteral("轮麦时间:"));
		QString strFormat2 = QString("<span style='font-size:11px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgb(255, 255, 255);line-height:16px; '>%1</span>");
		strFormat2 = strFormat2.arg(QStringLiteral("22:00-22:15"));
		content_->setText(strFormat + strFormat2);
		time_display_->setText(QString::number(time_count_) + QString("s"));
	}
	else {
		time_count_ = 30;
		title_->setText(QStringLiteral("即将结束轮麦"));
		QString strFormat = QString("<span style='font-size:11px;font-family:PingFangSC-Regular, PingFang SC;font-weight:400;color:rgba(255, 255, 255,128);line-height:16px; '>%1</span>");
		strFormat = strFormat.arg(QStringLiteral("可以引导观众点点关注哟"));
		content_->setText(strFormat);
		time_display_->setText(QString::number(time_count_) + QString("s"));
	}
	StartTimer();
	StartAnimationIn();
	show();
	raise();
}

void OfficialTipWidget::showEvent(QShowEvent* event) {
	bool isMin = isMinimized();
	QDialog::showEvent(event);
	isMin = isMinimized();
	
	qDebug() << "showEvent isMin:" << isMin;
}

void OfficialTipWidget::showMinimized() {

}

void OfficialTipWidget::hideEvent(QHideEvent* event) {
	bool isMin = isMinimized();
	QDialog::hideEvent(event);
	isMin = isMinimized();
	qDebug() << "hideEvent isMin:" << isMin;
}

