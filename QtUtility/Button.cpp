#include "Button.h"
#include <QPainter>
#include "Helper/QtHelper.hpp"
Button::Button(const QString & name,QWidget* parent)
	: QPushButton(parent)
{
	bool bLoad = m_image.load(name);
	if (bLoad)
	{
		m_imageNormal=QtHelper::GetImageByHSL(m_image,0,0,0,0);
		m_imageHorver=QtHelper::GetImageByHSL(m_image,0,0,10,35);
		m_imagePress=QtHelper::GetImageByHSL(m_image,0,100,10,35);
		m_imageDisable=QtHelper::GrayScale(m_image,33);
		m_image = m_imageNormal;
	}
}

Button::~Button()
{

}

void Button::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0,0,m_image);
}

void Button::enterEvent(QEvent *)
{
	m_image = m_imageHorver;
	update();
}

void Button::leaveEvent(QEvent *)
{
	m_image = m_imageNormal;
	update();
}

void Button::mousePressEvent(QMouseEvent *e)
{
	m_image = m_imagePress;
	update();
}

void Button::mouseReleaseEvent(QMouseEvent *e)
{
	m_image = m_imageNormal;
	update();
}