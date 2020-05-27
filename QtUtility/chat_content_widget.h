#ifndef chat_content_widget_h
#define chat_content_widget_h
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
class ChatContentWidget : public QWidget {
	Q_OBJECT
public:
	ChatContentWidget(QWidget* parent = 0);
	~ChatContentWidget();

	ChatContentWidget(ChatContentWidget&) = delete;
	ChatContentWidget& operator=(ChatContentWidget&) = delete;
	void Init();
	public slots:
	void OnSendBtnClicked();
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
	QVBoxLayout* vMainLayer;
	QHBoxLayout* lTopLayer;
	QHBoxLayout* sendLayer;
	QHBoxLayout* listLayout;

	QLabel* pNameLabel;
	QLabel* pStatusLabel;
	QPushButton* optionBtn;
	QScrollArea* scrollArea;
	QListWidget* listWidget;
	QTextEdit* contentEdit;
	QPushButton* sendBtn;
};

#endif // !chat_content_widget_h
