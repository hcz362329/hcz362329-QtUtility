#pragma once
#include <QWidget>
class RoundedWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RoundedWidget(QWidget* parent = nullptr);
	virtual ~RoundedWidget() {};

	RoundedWidget(const RoundedWidget&) = delete;
	RoundedWidget& operator=(const RoundedWidget&) = delete;
	void SetPixmap(const QString & strPixmap);
	void SetRoundedColor(int w, int h, int border_radius, int r, int g, int b, int a=255);
protected:
	virtual void paintEvent(QPaintEvent* event);
private:
	QPixmap pixmap;
	int nRadius;
};