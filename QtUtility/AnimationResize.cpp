#include "AnimationResize.h"
#include <QPushButton>
#include <QTimer>
#include <QPair>
#include "gift_flowlight_manager.h"
AnimationResize::AnimationResize(QWidget* parent)
	:QDialog(parent)
	, m_pAnimation(nullptr)
{
	setGeometry(400,330,800,800);

	btn = new QPushButton(this);
	btn->setGeometry(250, 235, 100, 30);
	btn2 = new QPushButton(this);
	btn2->setGeometry(250, 235, 100, 30);
	QTimer::singleShot(2000, [&]() {
		Test();
	});
}

void AnimationResize::Test()
{
	QVariantList var;
	QVariantAnimation::KeyValues key2Value;
	QPair<qreal, QRect> pair1 = qMakePair<qreal, QRect>(0, QRect(250, 235, 100, 30));
	QPair<qreal, QRect> pair2 = qMakePair<qreal, QRect>(0.5, QRect(200, 220, 200, 60));
	QPair<qreal, QRect> pair3 = qMakePair<qreal, QRect>(1, QRect(250, 235, 100, 30));
	key2Value << pair1<< pair2<< pair3;
	m_pAnimation = Mgr::GetPropertyAnimation(btn, this, Mgr::TYPE_GEOMETRY,var, key2Value, 1000, true);

	
	
	m_pAnimation->start();
	auto OnFinish{ [&]() {
		m_pAnimation->deleteLater();
		m_pAnimation = nullptr;
	} };
	connect(m_pAnimation, &QPropertyAnimation::finished,OnFinish);

	var.push_back(QRect(250, 235, 100, 30));
	var.push_back(QRect(250, 400, 100, 30));
	m_pAnimation2 = Mgr::GetPropertyAnimation(btn2, this, Mgr::TYPE_GEOMETRY, var, key2Value, 1000, false);
	

	m_pAnimation2->start();
	auto OnFinish2{ [&]() {
		m_pAnimation2->deleteLater();
		m_pAnimation2 = nullptr;
	} };
	connect(m_pAnimation2, &QPropertyAnimation::finished, OnFinish2);
}

AnimationResize::~AnimationResize()
{
	if (m_pAnimation != nullptr){

	}
}