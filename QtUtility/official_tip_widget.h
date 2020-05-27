#ifndef OFFICIAL_TIP_WIDGET_H
#define OFFICIAL_TIP_WIDGET_H
#include <QDialog>
#include <QLabel>
class QPropertyAnimation;
class OfficialTipWidget : public QDialog {
	Q_OBJECT
public:
	enum TipType {
		TYPE_OPEN = 0,
		TYPE_CLOSE
	};
	OfficialTipWidget(QWidget* parent=0);
	~OfficialTipWidget();

	void StartTimer();
	void StopTimer();
	void SetTipType(TipType type);
	void StartAnimationIn();
	void StartAnimationOut();
protected:
	void timerEvent(QTimerEvent* event);
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
public:
	void showMinimized();
private:
	int time_count_;
	int timer_;
	TipType type_;
	QWidget* animation_widget_;
	QLabel* title_;
	QLabel* content_;
	QLabel* time_display_;
	QPropertyAnimation* animation_in_;
	QPropertyAnimation* animation_out_;
};

#endif // !1
