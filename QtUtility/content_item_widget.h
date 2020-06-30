#ifndef CONTENT_ITEM_WIDGET_H
#define CONTENT_ITEM_WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVariant>
#include <QListWidgetItem>
#ifndef GET_SET_DEFINE
#define GET_SET_DEFINE(ArgName, Type, Alias) \
const Type Get##Alias() const { return this->##ArgName; }; \
void Set##Alias(const Type& value) { this->##ArgName = value; };
#endif // !GET_SET_DEFINE

struct MsgContent {
	std::string content;
};
Q_DECLARE_METATYPE(MsgContent)

class ContentItemWidget : public QWidget {
	Q_OBJECT
public:
	enum ItemType {
		Date,
		BeFriend,
		MsgLeft,
		MsgRight,
		ReSend,
	};
	ContentItemWidget(QWidget* parent, ItemType type, QListWidgetItem* item, const QVariant& var = QVariant());
	~ContentItemWidget();
	GET_SET_DEFINE(itemType, ItemType, ItemType);
	void HideStatus();
protected:
	virtual void resizeEvent(QResizeEvent* event);
private:
	ItemType itemType;
	QLabel* pBeFriend;
	QLabel* pDate;
	QLabel* pHead;
	QLabel* pStatus;
	QLabel* pContentLabel;
	QLabel* reSend;
	QTextEdit* pContent;
	QPixmap pixDefault;
	QPixmap pixSending;
	QPixmap pixSendFail;
	QHBoxLayout* lMainLayer;
	QVBoxLayout* vMsgLayer;
	QListWidgetItem* item;
};

#endif // !content_item_widget_h
