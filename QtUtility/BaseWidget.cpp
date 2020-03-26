#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget * parent)
	: QWidget(parent)
{
	//setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

BaseWidget::~BaseWidget()
{

}