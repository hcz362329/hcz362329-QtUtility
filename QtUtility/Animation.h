//edit by cz
#ifndef CANIMATIONDLG_H
#define CANIMATIONDLG_H

#include <QtWidgets/QWidget>
#include <QAbstractItemModel>
#include "select_hero_def.h"
/*		
	////////����Ч����////////
*/
class CAnimation : public QWidget
{
	Q_OBJECT

public:
	CAnimation(QWidget *parent = NULL);
	~CAnimation();

	void startAnimation(int nMsec = 20);
	void SetHero(const STHero &);
	void SetSeconds(int nsecs);
	STHero GetHero();
	bool IsRunOver();

	//����ʣ�༱��תȦ
	void StartQuickAnimation();
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *);
signals:
	void stopAnimation(const STHero &);
	void heroInfoSignal(const STHero &);
private:
	QImage *m_imgIcon;

	int m_iTimerId;
	int m_iIndex;
	STHero m_stHero;
	bool m_bRunOver;//ȷ��ת��ʱ��
};

#endif // CANIMATIONDLG_H
