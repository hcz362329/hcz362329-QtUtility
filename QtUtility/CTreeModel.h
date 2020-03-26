#ifndef TagTreeModel_h
#define TagTreeModel_h
#define MULTI_COLUMN 0
#include "TreeItem.h"

#include <QAbstractItemModel>

class CTreeModel : public QAbstractItemModel  
{  
	Q_OBJECT  

public:  
	CTreeModel(QObject *parent = 0);  
	~CTreeModel();  

	QVariant data(const QModelIndex &index, int role) const;  
	Qt::ItemFlags flags(const QModelIndex &index) const;  
	QVariant headerData(int section, Qt::Orientation orientation,  
		int role = Qt::DisplayRole) const;  
	QModelIndex index(int row, int column,  
		const QModelIndex &parent = QModelIndex()) const;  
	QModelIndex parent(const QModelIndex &index) const;  
	int rowCount(const QModelIndex &parent = QModelIndex()) const;  
	int columnCount(const QModelIndex &parent = QModelIndex()) const; 

	void updateAll(QVector<QVariant> & vectorVariant);
	void UpdateAll(QVector<STNode>& vec);
	void AddNode(STNode& stNode,bool AddInDefault = false);
	void UpdateNode(STNode & stNode);
	void DeleteNode(const STNode& stNode );
	void DeleteGroup(const STNode & node);
	void DeleteGroupNodeButSaveChildItem(const STNode& stNode);
	void ResetModel();
private:  
	TreeItem *m_pRootItem; // 最顶层顶根节点(一个无效的QModelIndex)  
};  

#endif

