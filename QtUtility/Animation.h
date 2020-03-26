//edit by cz
#ifndef CANIMATIONDLG_H
#define CANIMATIONDLG_H

#include <QtWidgets/QWidget>
#include <QAbstractItemModel>
#include "select_hero_def.h"
/*		
	////////动画效果框////////
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

	//开启剩余急速转圈
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
	bool m_bRunOver;//确保转完时间
};

#endif // CANIMATIONDLG_H
