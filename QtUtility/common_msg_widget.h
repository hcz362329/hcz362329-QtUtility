#ifndef COMMON_MSG_WIDGET_H
#define COMMON_MSG_WIDGET_H
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QPaintEvent>

enum EMsgType
{
	eMsgKnow			= 1,
	eMsgCancleOk		= 2,
};

const QString strBtnStyle = QString("QPushButton{background:rgba(255,255,255,0);border-image:url(%1);}QPushButton::hover{background:rgba(255,255,255,0);border-image:url(%2);}QPushButton::pressed{background:rgba(255,255,255,0);border-image:url(%3);}");
class   CommonMsgWidget : public QDialog
{
	Q_OBJECT
public:
	CommonMsgWidget(QString strText, EMsgType eType,QWidget* parent = nullptr);
	~CommonMsgWidget();

	static int information(QWidget* parent, QString strText, EMsgType eType);
	void CreateBg();
protected:
	virtual void paintEvent(QPaintEvent* event);
private:
	QLabel* pLabeText;
	QPushButton* pBtnOk;
	QPushButton* pBtnCancle;
	QPushButton* pBtnClose;
	QPixmap pixmap;
};

#endif 
