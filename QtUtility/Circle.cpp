#include "Circle.h"
#include <QPainter>
#include <QTimerEvent>
#include <QDebug>
Circle::Circle(QWidget* parent) : QWidget(parent){
	resize(90,90);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("QWidget{background:rgba(255,255,255,0);}");
	count = 0;
	totalCount = 360;
	angle = 1;
	time = 0;
	perMinuteAngle = 0;
}

void Circle::SetTime(int time) {
	this->time = time;
	perMinuteAngle = totalCount / time;
	int timeSpecies = 1000 / perMinuteAngle;
	timer = startTimer(timeSpecies);
}

Circle::~Circle() {

}

void Circle::paintEvent(QPaintEvent *event) {
	if (time > 0) {
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
		painter.save();
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(223, 191, 161)));
		painter.drawEllipse(0, 0, width(), height());
		painter.restore();
		painter.save();
		QRectF rectangle(0, 0, width(), height());//设定扇形所在的矩形，扇形画在矩形内部
		int startAngle = 90 * 16;//起始角度，角度可以为负值，如-30*16
		int spanAngle = -angle* count * 16;//覆盖的角度，绘制方向为逆时针方向
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(193, 77, 82)));
		int min = time - count / perMinuteAngle;
		if (min<=0) {
			spanAngle = -360 * 16;
		}
		painter.drawPie(rectangle, startAngle, spanAngle);
		painter.restore();

		painter.save();
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(212, 90, 95)));
		painter.drawEllipse(5, 5, width()-10, height()-10);
		painter.restore();

		painter.save();
		QFont font;
		font.setBold(true);
		font.setPixelSize(28);
		font.setFamily("PingFangSC-Semibold,PingFang SC;");
		painter.setFont(font);
		painter.setPen(QColor(255, 245, 234));
		
		if (min < 0) {
			min = 0;
		}
		painter.drawText(rectangle, Qt::AlignCenter,QString::number(min));
		painter.restore();
	}
}

void Circle::timerEvent(QTimerEvent *event) {
	if (event->timerId() == timer) {
		update();
		count++;
		int min = time - count / perMinuteAngle;
		if (min <= 0) {
			qDebug() << "1";
			count = 0;
		}
	}
}