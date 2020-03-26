#include "AnimationResize.h"
#include <QPushButton>
#include <QTimer>
AnimationResize::AnimationResize(QWidget* parent)
	:QDialog(parent)
{
	setGeometry(400,330,800,800);
	
	QLabel* pWidget = new QLabel(this);
	pWidget->setGeometry(400,0,100,100);
	pWidget->setText("aaaaaaa");
	m_pAnimation = new QPropertyAnimation(pWidget);

	QTimer::singleShot(2000,this,[=]{
		m_pAnimation->setPropertyName("geometry");
		
		QRect startRect = rect();
		startRect.moveTo(pos());
		QRect stopRect = QRect(startRect.center(), QSize(0, 0));
		
		m_pAnimation->setStartValue(startRect);
		m_pAnimation->setEndValue(stopRect);
		m_pAnimation->start();
	});
	
}

AnimationResize::~AnimationResize()
{

}