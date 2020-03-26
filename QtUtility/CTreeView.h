#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QTreeView>
#include "CTreeModel.h"
#include "CTreeDelegate.h"
class TreeView : public QTreeView
{
	Q_OBJECT
public:
	explicit TreeView(QWidget* parent = nullptr);
	~TreeView();
public:
	//����View����ʽ
	void InitTreeView();
	//����Model��Delegate
	void loadModelDelegate();
	//���´������������
	void updateAll(QVector<QVariant> & vectorVariant);
	void updateAll(QVector<STNode>& vec);
	void AddNode(STNode & stNode);
	void UpdateNode(STNode & stNode);
	void DeleteNode(const STNode & node);
	void DeleteGroup(const STNode & node);
	void DeleteGroupNodeButSaveChildItem(const STNode& stNode);
protected:
	virtual void mousePressEvent(QMouseEvent * event);
private:
	CTreeDelegate * m_pDelegate;
	CTreeModel * m_pModel;
};
#endif