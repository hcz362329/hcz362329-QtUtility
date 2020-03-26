#ifndef UNLOCKTIP_H
#define UNLOCKTIP_H
#include <QWidget>

class UnLockTip : public QWidget
{
	Q_OBJECT
public:
	explicit UnLockTip(QWidget* parent =0);
	~UnLockTip();
	static UnLockTip * GetInstance();
	static void DeleteInstance();
	static UnLockTip * g_instance;

	void UpdateInfo(QString strTitle,QString strContent,QString strLockState);
	void SetSlotId(int uiSlotId);
	int GetSlotId();
	void SetLockState(QString strLockState);
protected:
	void paintEvent(QPaintEvent *);
private:
	QString m_strTitle;
	QString m_strContent;
	QString m_strLockState;
	int  m_uiSlotId ;
};
#endif