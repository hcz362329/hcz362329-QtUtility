#pragma once
#include <QWidget>
#include <QMouseEvent>
class MoveWidget : public QWidget {
	Q_OBJECT

public:
	MoveWidget(QWidget * parent = Q_NULLPTR);
	~MoveWidget();

	virtual void mousePressEvent(QMouseEvent* event);
private:
	bool m_bSize;
	bool m_bMove;
	bool m_bSizeOrMove;
};
