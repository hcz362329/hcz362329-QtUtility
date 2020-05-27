#include "gift_flowlight_manager.h"
using namespace Mgr;
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QResizeEvent>
QlLabel::QlLabel(QWidget* parent) :QLabel(parent) {

}

QlLabel::~QlLabel() {

}

void QlLabel::resizeEvent(QResizeEvent* event) {
	if (!pixmap_.isNull()) {
		QPixmap pixmap;
		pixmap.load(pixmap_);
		pixmap = pixmap.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		setPixmap(pixmap);
	}
}

ItemWidget::ItemWidget(QWidget* parent):QWidget(parent),
	free_(true),
	user_head_(nullptr),
	user_icon_(nullptr),
	user_name_(nullptr),
	gift_num_(nullptr),
	gift_name_(nullptr),
	gift_hit_(nullptr),
	gift_icon_(nullptr),
	animation_geomtry_(nullptr),
	count_time(SHOW_TIME_COUNT),
	count_timer(0){
	resize(300,80);
	bg_ = new QLabel(this);
	bg_->setGeometry(0,0, 300, 80);
	user_head_ = new QLabel(this);
	user_head_->setFixedSize(40,40);
	user_head_->setPixmap(QPixmap(":/res/Resources/images/source_camera1.png"));
	user_head_->setStyleSheet("");
	user_icon_ = new QLabel("icon", this);
	user_icon_->setFixedSize(20, 20);
	user_icon_->setPixmap(QPixmap(":/res/Resources/images/source_camera1.png"));
	user_icon_->setStyleSheet("");
	user_name_ = new QLabel(QStringLiteral("名字最长七个字"),this);
	user_name_->setStyleSheet("color:red;");
	user_name_->setFixedSize(80, 20);

	gift_name_ = new QLabel(QStringLiteral("名字最长七个字"),this);
	gift_name_->setStyleSheet("color:blue;");
	gift_name_->setFixedSize(60, 20);
	
	gift_icon_ = new QLabel("icon", this);
	gift_icon_->setStyleSheet("color:blue;");
	gift_icon_->setFixedSize(60, 20);
	gift_num_ = new QLabel("22",this);
	gift_num_->setStyleSheet("color:blue;");
	gift_num_->setFixedSize(60, 20);
	QHBoxLayout * layout = new  QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(user_head_);
	layout->addWidget(user_icon_);
	layout->addWidget(user_name_);

	layout->addWidget(gift_name_);
	layout->addWidget(gift_icon_);
	layout->addWidget(gift_num_);
	layout->addStretch();
	setLayout(layout);
}

ItemWidget::~ItemWidget() {

}

void ItemWidget::timerEvent(QTimerEvent *e) {
	if (e->timerId() == count_timer) {
		count_time--;
		if (count_time == 0) {
			StopTimer();
			emit FlowFinish();
		}
	}
}

void ItemWidget::StartTimer() {
	if (count_timer != 0) {
		StopTimer();
	}
	count_time = SHOW_TIME_COUNT;
	count_timer = startTimer(1000);
	free_ = false;
}

void ItemWidget::StopTimer() {
	if (count_timer != 0) {
		killTimer(count_timer);
		count_timer = 0;
		count_time = SHOW_TIME_COUNT;
		free_ = true;
	}
}

int ItemWidget::GetUserId() {
	int ret = 0;
	ret = current_.user_id;
	return ret;
}

void ItemWidget::Update() {
	StartAnimation();
}

void ItemWidget::StartAnimation() {
	InitAnimation();
	if (animation_geomtry_ != nullptr  ) {
		QVariantAnimation::State sta= animation_geomtry_->state();
		if (sta == QVariantAnimation::Running)
			return;
		current_ = *hitList.begin();
		mutex_.lock();
		hitList.pop_front();
		mutex_.unlock();

		static bool b = true;
		QString strText1 = QString(":/res/Resources/images/source_camera1.png");
		QString strText2 = QString(":/res/Resources/images/mic_mute2.png");
		if (b) {
			b = false;
			gift_hit_->SetPixmap(strText1);
		}
		else {
			b = true;
			gift_hit_->SetPixmap(strText2);
		}

		animation_geomtry_->start();
		StartTimer();
	}
}

void ItemWidget::OnFinishAnimation() {
	qDebug() << "id" << current_.user_id << "state :" << (int)animation_geomtry_->state()<<",run:"<<QVariantAnimation::Running;
	if (!hitList.empty()) {
		StartAnimation();
	}
}

void ItemWidget::InitAnimation() {
	if (gift_hit_==nullptr) {
		gift_hit_ = new QlLabel(this);
		int x = gift_num_->pos().rx()+ gift_num_->width()+5;
		int y = gift_num_->pos().ry();
		gift_hit_->setGeometry(x,y,20,20);

		gift_hit_->SetPixmap(":/res/Resources/images/source_camera1.png");
		gift_hit_->setPixmap(gift_hit_->GetPixmap());
		gift_hit_->show();
	}
	if (animation_geomtry_ != nullptr) {
		QVariantAnimation::State sta = animation_geomtry_->state();
		if (sta == QVariantAnimation::Running)
			return;
		else {
			disconnect(animation_geomtry_, SIGNAL(finished()), this, SLOT(OnFinishAnimation()));
			animation_geomtry_->deleteLater();
			animation_geomtry_ = nullptr;
		}
	}
	if (animation_geomtry_ == nullptr && gift_hit_ != nullptr) {
		QVariantList list;
		QVariantAnimation::KeyValues key2Value;
		int x = gift_hit_->pos().rx();
		int y = gift_hit_->pos().ry();
		int w = gift_hit_->width();
		int h = gift_hit_->height();
		QPair<qreal, QRect> pair1 = qMakePair<qreal, QRect>(0, QRect(x,y,w,h));
		QPair<qreal, QRect> pair2 = qMakePair<qreal, QRect>(0.5, QRect(x, y, w+20, h+20));
		QPair<qreal, QRect> pair3 = qMakePair<qreal, QRect>(1, QRect(x, y, w, h));
		key2Value << pair1 << pair2 << pair3;
		animation_geomtry_ = GetPropertyAnimation(gift_hit_, this, TYPE_GEOMETRY, list, key2Value, 1000, true);
		connect(animation_geomtry_, SIGNAL(finished()), this, SLOT(OnFinishAnimation()));
	}
}

void ItemWidget::InsertFlowLignt(const FlowLight& light){
	mutex_.lock();
	hitList.push_back(light);
	mutex_.unlock();
	StartAnimation();
}

GiftFlowLight::GiftFlowLight(QWidget* parent) :QDialog(parent),
	up_item_(nullptr),
	under_item_(nullptr){
	resize(500,200);
	Init();
}

GiftFlowLight::~GiftFlowLight() {

}

void GiftFlowLight::Init() {
	test = new QPushButton("press", this);
	test->setGeometry(0, 0, 60, 20);
	connect(test, SIGNAL(clicked()), this, SLOT(OnTestClick()));

	up_item_ = new ItemWidget(this);
	under_item_ = new ItemWidget(this);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(test, 1);
	layout->addWidget(up_item_,1);
	layout->addWidget(under_item_,1);
	setLayout(layout);
	connect(up_item_,&ItemWidget::FlowFinish,this,&GiftFlowLight::OnFinish,Qt::UniqueConnection);
	connect(under_item_, &ItemWidget::FlowFinish, this, &GiftFlowLight::OnFinish, Qt::UniqueConnection);
}

void GiftFlowLight::OnTestClick() {
	static int i = 1;
	i++;
	FlowLight f;
	f.user_id = i%3+1;
	
	ItemWidget* item = GetUserItem(f.user_id);
	if (item != nullptr) {
		item->InsertFlowLignt(f);
	}
	else {
		AddGift(f);
		qDebug() << "list:" << f.user_id;
	}
	Start();
}

ItemWidget * GiftFlowLight::GetFreeItem() {
	if (up_item_ != nullptr && under_item_ != nullptr) {
		if (under_item_->GetFree()) {
			return under_item_;
		}
		else if (up_item_->GetFree()) {
			return up_item_;
		}
	}
	return nullptr;
}

ItemWidget * GiftFlowLight::GetUserItem(int id) {
	if (up_item_ != nullptr && under_item_ != nullptr) {
		if (under_item_->GetUserId()==id) {
			qDebug() << "under:" << id;
			return under_item_;
		}
		else if (up_item_->GetUserId() == id) {
			qDebug() << "up:" << id;
			return up_item_;
		}
	}
	return nullptr;
}

void GiftFlowLight::AddGift(FlowLight& light) {
	std::lock_guard<std::mutex> lock(mutex_);
	flowlights_.push_back(light);
}

void GiftFlowLight::Start() {
	ItemWidget * item = GetFreeItem();
	if (item != nullptr && !flowlights_.empty()) {
		item->InsertFlowLignt(*flowlights_.begin());
		std::lock_guard<std::mutex> lock(mutex_);
		flowlights_.pop_front();
	}
}

void GiftFlowLight::OnFinish() {
	Start();
}