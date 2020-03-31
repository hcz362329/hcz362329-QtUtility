#ifndef EXAMBOOST_JxListView_H
#define EXAMBOOST_JxListView_H
#include "HyTableDef.h"
#include "JxModel.h"
#include "JxDelegate.h"
#include <QListView>

class JxListView : public QListView
{
	Q_OBJECT
public:
	explicit JxListView(QWidget* parent = NULL );
	~JxListView();
public:
	void initView();
	void initModelDelagate();
	//½«ÐÇ
	void updateAll(QVector<STJX>&);
	//ÊÞ»ê
	void updateAll(QVector<STSH>& vecSTSH);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
signals:
	void OnJXSelectSignal(const STJX&);
	void OnSHSelectSignal(const STSH&);
	void sigItemCount(const int &);
private:
	JxModel*		m_pModel;
	JxDelegate*	m_pDelegate;
public:
	void setListViewShowType(EListViewShowType eListViewShowType);
	EListViewShowType getListViewShowType();
	EListViewShowType m_eShowType;
};

#endif