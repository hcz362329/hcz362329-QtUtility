#ifndef CIRCLE_H
#define CIRCLE_H
#include <QWidget>
class Circle : public QWidget {
	Q_OBJECT
public:
	Circle(QWidget* parent=nullptr);
	~Circle();
	void SetTime(int time);
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
private:
	int timer;
	int count;
	int totalCount;
	int angle;
	int time;
	int perMinuteAngle;
};
#endif // !CIRCLE_H