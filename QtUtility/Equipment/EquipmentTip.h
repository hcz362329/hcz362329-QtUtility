#ifndef EQUIPMENTTIP_H
#define EQUIPMENTTIP_H
#include "BaseDataDef.h"
#include "EquipmentBase.h"
#include <QLabel>
#include <QTextEdit>
class EquipmentTip : public QWidget
{
	Q_OBJECT
public:
		explicit EquipmentTip(QWidget* parent = 0);
		~EquipmentTip();
		void setEquipmentInfo(const STEquipment& stEquipment);
		void stringToHtml(QString &str);
protected:
	virtual void paintEvent(QPaintEvent* event);
	STEquipment m_stEquipment;
	QPixmap m_pixBG;
	QVariant m_stItem;
	QPixmap m_pixIcon;
	QPixmap m_pixCost;
	QTextEdit * m_pItemDesc;
};
#endif