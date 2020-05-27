#ifndef CHATLISTWIDGET_H
#define CHATLISTWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
class ChatListWidget : public QWidget {
	Q_OBJECT
public:
	ChatListWidget(QWidget* parent = 0);
	~ChatListWidget();

	void Init();

	ChatListWidget(ChatListWidget& widget) = delete;
	ChatListWidget& operator=(const ChatListWidget &) = delete;
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
private:
	QVBoxLayout* vLayer;
	QLabel* pListCount;
};
#endif // !ChatListWidget_h
