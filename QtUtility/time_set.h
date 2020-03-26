#pragma once

#include <QWidget>
#include "ui_TimeSet.h"

class TimeSet : public QWidget
{
	Q_OBJECT

public:
	TimeSet(QWidget *parent = Q_NULLPTR);
	~TimeSet();

private:
	Ui::TimeSet ui;
};
