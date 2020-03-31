#pragma once
#ifndef LIVETIMESET_HPP
#define LIVETIMESET_HPP
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include "LiveTimeView.h"
enum ELiveSetBtn
{
	eLiveSetBtnClose	= 1,
	eLiveSetBtnOk		= 2,
	eLiveSetBtnCancle	= 3,
	eLiveSetBtnEdit		= 4,
	eLiveSetBtnDelete	= 5,
};
struct STLiveTime
{
	std::string startTime;
	std::string endTime;
};
Q_DECLARE_METATYPE(STLiveTime)

#include "rounded_widget.h"

class LiveTimeItem : public QWidget
{
	Q_OBJECT
public:
	LiveTimeItem(QWidget * parent = 0);
	~LiveTimeItem();
	LiveTimeItem(const LiveTimeItem&) = delete;
	LiveTimeItem& operator=(const LiveTimeItem&) = delete;

	void SetIndex(int index);
	public slots:
	void OnBtnClicked(ELiveSetBtn eBtn);
signals:
	void sigEdit(const int &);
private:
	QLabel* pLabelBg;
	QLabel* pStartTime;
	QLabel* pEndTime;

	QPushButton* pBtnEdit;
	QPushButton* pBtnDelete;
	int nIndex;
};

class TimeSpecify : public QWidget
{
	Q_OBJECT
public:
	TimeSpecify(QWidget* parent = nullptr);
	~TimeSpecify();

	TimeSpecify(const TimeSpecify&) = delete;
	TimeSpecify& operator=(const TimeSpecify&) = delete;
public slots:
	void OnBtnClicked(ELiveSetBtn eBtn);
private:
	View*	pViewStart;
	View*   pViewStop;
};

class LiveTimeSet : public RoundedWidget {
	Q_OBJECT

public:
	LiveTimeSet(QWidget * parent = 0);
	~LiveTimeSet();

	void AddLiveStartEndTime(const STLiveTime& stLiveTime);
	LiveTimeSet(const LiveTimeSet&) = delete;
	LiveTimeSet& operator=(const LiveTimeSet&) = delete;
protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

	virtual bool eventFilter(QObject *watched, QEvent *event);
public slots:
	void OnTextChangeSlot(const QString &);
	void OnBtnClicked(ELiveSetBtn eBtn);
	void OnItemEditSot(const int&);
private:
	QPoint  m_relativeInit;
	bool    m_bLeftBtnPress;

	QLabel* pLablTitle;
	QPushButton* pBtnClose;

	QLineEdit* pLiveTitleEdit;
	QPushButton* pTipBtn;
	QLabel* pLabelTimeTip;

	QPushButton* pLiveTimeCount;
	QPushButton*   pLiveTimeCountTip;
	QLabel*   pLiveTimeCountTip2;

	QPushButton* pBtnNotLive;
	QPushButton* pBtnLive;
	QVBoxLayout* pLiveItemsVLayout;
	QMap<int, LiveTimeItem*> mapIndex2Item;
	int nEditItem;
	TimeSpecify* pTimeSpecify;
};

#endif // LIVETIMESET_HPP