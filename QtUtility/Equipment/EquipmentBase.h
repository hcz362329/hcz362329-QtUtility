#ifndef EQUIPMENTBASE_H
#define EQUIPMENTBASE_H
#include <QWidget>
class EquipmentBase : public QWidget
{
	Q_OBJECT
public:
	EquipmentBase(QWidget* parent = NULL);
	~EquipmentBase();
};
#endif