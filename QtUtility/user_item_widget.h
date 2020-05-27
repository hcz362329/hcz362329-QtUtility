#ifndef user_item_widget_h
#define user_item_widget_h
#include <QLabel>
class UserItemWidget : public QWidget {
	Q_OBJECT
public:
	UserItemWidget(QWidget* parent = nullptr);
	~UserItemWidget();
	void Init();
	UserItemWidget(UserItemWidget&) = delete;
	UserItemWidget& operator=(UserItemWidget&) = delete;
private:
	QLabel* pHead;
	QLabel* pName;
	QLabel* pUnKnown;
	QLabel* pWhisper;
	QLabel* pWeekDay;
	QLabel* pSign;
	QLabel* redDot;
};
#endif // !user_item_widget_h
