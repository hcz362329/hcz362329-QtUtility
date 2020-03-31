#pragma once 

#include <QString>

const QString toolBtnStyle = QString(
							"QToolTip{ "
							"border:1px solid rgb(118, 118, 118);"
							"background-color: #ffffff;"
							"color:#484848;"
							"font-size:12px;"
							"}"
							"QPushButton{"
							"border-image: url(%0);"
							"}"
							"QPushButton::hover{"
							"border-image: url(%1);"
							"}"
							"QPushButton::!enabled{"
							"border-image: url(%3);}");

const QString customBtnStyle =  QString(
								"QToolTip{ "
								"border:1px solid rgb(118, 118, 118);"
								"background-color: #ffffff;"
								"color:#484848;"
								"font-size:12px;"
								"}"
								"QPushButton{ "
								"  background: #151515;"
								"  border-radius: 20px;"
								"  color:#ffffff;"
								"}"
								"QPushButton:pressed {"
								"  background: #FF1C75;"
								"}"
								"QPushButton:hover {"
								"  background: #FF1C75;"
								"}");

const QString strStyleButtonSet = QString("QPushButton{border-image:url(%1);}QPushButton::hover{border-image:url(%2);}QPushButton::pressed{border-image:url(%3);}");