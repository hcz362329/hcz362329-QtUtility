#ifndef IMWIDGET_H
#define IMWIDGET_H
#include <QDialog>
#include <QVBoxLayout>;
#include <QHBoxLayout>;
#include <QLabel>
#include <QPushButton>
#include <QStackedLayout>
class ChatListWidget;
class ChatContentWidget;
class IMWidget : public QDialog {
	Q_OBJECT
public:
	IMWidget(QWidget* parent = 0);
	~IMWidget();

	IMWidget(IMWidget& widget) = delete;
	IMWidget& operator=(const IMWidget &) = delete;

	void Init();
	void InitConnect();
protected:
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
public slots:
	void OnCloseBtn();
private:
	//layer
	QVBoxLayout* vMainLayer;
	QHBoxLayout* lTopLayer;
	QLabel* pTopBg;
	QLabel* pTitle;
	QPushButton* pCloseBtn;
	QHBoxLayout* lChatLayer;
	QStackedLayout* contentLayout;

	ChatListWidget* pChatList;
	ChatContentWidget* pChatContent;

	QPoint		m_pressPoint;
	QPoint		m_movePoint;
	bool		m_pressed;
};

#endif // !IMWIDGET_H
