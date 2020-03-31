#include "move_widget.hpp"

MoveWidget::MoveWidget(QWidget * parent) : QWidget(parent) {
	m_bSize=true;
	m_bMove = true;
	m_bSizeOrMove = true;
}

MoveWidget::~MoveWidget() {
	
}

void MoveWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button()==Qt::LeftButton)
	{

	}
	QWidget::mousePressEvent(event);
}
