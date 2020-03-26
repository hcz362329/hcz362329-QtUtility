#ifndef COMMON_MSG_WIDGET_H
#define COMMON_MSG_WIDGET_H
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QPaintEvent>
const QString strBtnStyle = QString("QPushButton{border-image:url(%1);}QPushButton::hover{border-image:url(%2);}QPushButton::pressed{border-image:url(%3);}");
class  CommonMsgWidget : public QDialog
{
	Q_OBJECT
public:
	CommonMsgWidget(QString strText,QWidget* parent = nullptr);
	~CommonMsgWidget();

	static int information(QWidget* parent, QString strText);
	void CreateBg();
protected:
	virtual void paintEvent(QPaintEvent* event);
private:
	QLabel* pLabeText;
	QPushButton* pBtnOk;
	QPushButton* pBtnClose;
	QPixmap pixmap;
};

#endif 
