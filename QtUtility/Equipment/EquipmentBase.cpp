#include "EquipmentBase.h"

EquipmentBase::EquipmentBase(QWidget* parent /*= NULL*/)
	: QWidget(parent)
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint );
	//setAttribute(Qt::WA_TranslucentBackground);
}

EquipmentBase::~EquipmentBase()
{

}