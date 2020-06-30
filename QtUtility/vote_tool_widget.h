#ifndef VOTE_TOOL_WIDGET_H
#define VOTE_TOOL_WIDGET_H
#include <QDialog>
#include <QLabel>
#include <QListWidget>

struct VoteChoice {
	int voteNum;
	std::string choiceId;
	std::string choiceName;
	VoteChoice() {
		voteNum = 0;
	}
};

class VoteToolWidget : public QDialog {
	Q_OBJECT
public:
	enum VoteState {
		READY = 0,
		VOTING = 1,
		FINISH = 2
	};
	explicit VoteToolWidget(QWidget* parent=0);
	~VoteToolWidget();

	void SetVoteState(VoteState state);
	VoteState GetVoteState();
	QString GetTime();
	void SetFollowNum(int num);
public slots:
	void OnItemClicked(QListWidgetItem* item);
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual bool eventFilter(QObject* obj, QEvent* event);
private:
	int followNum;
	int			times;
	VoteState	voteState;
	QLabel*		title;
	QLabel*		tip;
	QLabel*		voteTime;
	QLabel*		seprateLine;

	QWidget*	voteRuleWidget;
	QLabel*		voteRule;
	QLabel*		voteTotalNum;
	QLabel*		voteMaxNum;

	QLabel*		selectTitle;
	QListWidget* listWidget;
	QLabel*		resultTip;
};

class VoteItem : public QWidget {
	Q_OBJECT
public:
	VoteItem(QWidget* parent=0);
	~VoteItem();
	void SetData(const VoteChoice & data);
	VoteChoice GetData();
	void SetVoteNum(int num);
	void SetName(const std::string & name);
private:
	QLabel* voteName;
	QLabel* voteNum;
	VoteChoice voteChoice;
};

#endif // !vote_tool_widget_h
