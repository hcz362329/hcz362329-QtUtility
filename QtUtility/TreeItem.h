/** 
 * @brief 通用树形结构类 
 */  
#ifndef TreeItem_h
#define TreeItem_h
#include "Data.h"
#include <QList>
#include <QVariant>
class TreeItem  
{  
public:  
	TreeItem(TreeItem *parent=0);
	TreeItem(STNode & node,TreeItem *parent=0 ); 
	TreeItem(const QList<QVariant> &data,TreeItem *parent=0 );  
	~TreeItem();  

	void appendChild(TreeItem *child);  
	TreeItem *child(int row);  
	int childCount() const;  
	int columnCount() const;  
	QVariant data(int column) const;  
	int row() const;  
	TreeItem *parent();  
	bool IsGroupExist(int group_id);
	bool IsNodeExist(const int & node_id);
	bool CheckIsExistInAll2NdNode(const STNode & node);
	STNode GetNodeDataByNodeId(int node_id);
	STNode & GetNodeData(){return m_stNode;}
	void SetNodeData(const STNode & node);
	void ChangeNodeDataInTreeGroup(const STNode & node);
	TreeItem * GetGroupTreeNode(int group_id);
	bool DeleteItemNode(const STNode& stNode);
	//删除组节点但不保存
	bool DeleteGroupNode(const STNode& stNode);
	//删除组节点但保存子节点
	bool DeleteGroupNodeButSaveChildItem(const STNode& stNode);
	QList<TreeItem*> & GetChildren(){return m_childItems;};
	void UpdateOnLineNum();
private:  
	TreeItem *m_parentItem;  // 父结点  
	QList<TreeItem*> m_childItems; // 子结点列表  
	QList<QVariant> m_itemDatas; // 子节点对应数据 ,存在多列时使用
	STNode m_stNode;//单列时使用
}; 

#endif