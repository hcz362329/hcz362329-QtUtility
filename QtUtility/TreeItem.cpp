#include "TreeItem.h"
#include <Windows.h>
/*
TreeItem *m_parentItem;  // 父结点  
QList<TreeItem*> m_childItems; // 子结点列表  
QList<QVariant> m_itemDatas; // 子节点对应数据  
*/

TreeItem::TreeItem(TreeItem *parent)
	:  m_parentItem(parent)
{
	m_childItems.clear();
	m_itemDatas.clear();
}

TreeItem::TreeItem(STNode & node,TreeItem *parent )
	: m_parentItem(parent)
	, m_stNode(node)
{
	m_childItems.clear();
	m_itemDatas.clear();
	if ( m_parentItem != NULL )
	{
		m_parentItem->appendChild(this);
	}
}

TreeItem::TreeItem(const QList<QVariant> &data,TreeItem *parent)
	: m_parentItem(parent)
{
	m_childItems.clear();
	m_itemDatas.clear();
	m_itemDatas = data;
}

TreeItem::~TreeItem()
{
	m_itemDatas.clear();
	for ( int i = 0 ; i < m_childItems.size() ; ++i )
	{
		if ( m_childItems[i]!= NULL )
		{
			delete m_childItems[i];
			m_childItems[i]=NULL;
		}
	}
	m_childItems.clear();
}

void TreeItem::appendChild(TreeItem *child)
{
	m_childItems.append(child);
	UpdateOnLineNum();
}

TreeItem * TreeItem::child(int row)
{
	TreeItem * item_=NULL;
	if (row>=0 && row < m_childItems.size() )
	{
		item_ = m_childItems[row];
	}
	return item_;
}

int TreeItem::childCount() const
{
	return m_childItems.size();
}

int TreeItem::columnCount() const
{
#if MULTI_COLUMN
	return m_itemDatas.size();
#else
	
	return 1;
#endif
}

QVariant TreeItem::data(int column) const
{
	QVariant v;
	if ( column >= 0 && column < m_itemDatas.size() )
	{
		v.setValue(m_itemDatas[column]);
	}
	return v;
}

int TreeItem::row() const
{
	return m_childItems.size();
}

TreeItem *TreeItem::parent()
{
	return m_parentItem;
}

bool TreeItem::IsGroupExist(int group_id)
{
	bool IsExist = false;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		if (node.IsGroup && node.group_id == group_id )
		{
			IsExist = true;
			break;
		}
	}
	return IsExist;
}

bool TreeItem::IsNodeExist(const int & node_id)
{
	bool IsExist = false;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		if (!node.IsGroup && node.node_id == node_id )
		{
			IsExist = true;
			break;
		}
	}
	return IsExist;
}

bool TreeItem::CheckIsExistInAll2NdNode(const STNode & node)
{
	bool bExist = false;
	if ( m_parentItem != NULL )
	{
		MessageBoxA(0,"Function Use Error",0,0);
		return true;
	}
	//只在总节点中判断所有分支节点中是否存在该节点,该树为2级树,只搜索2遍
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		TreeItem* pGroupTree = m_childItems[i];
		QList<TreeItem*> list_ = pGroupTree->GetChildren();
		for (size_t j = 0 ; j < list_.size() ; ++j )
		{
			STNode & stNode = list_[j]->GetNodeData();
			if ( stNode.node_id == node.node_id )
			{
				bExist = true;
				break;
			}
		}
	}
	return bExist;
}

STNode TreeItem::GetNodeDataByNodeId(int node_id)
{
	STNode node;
	if ( m_parentItem != NULL )
	{
		MessageBoxA(0,"Function Use Error",0,0);
		node.node_id = -1;
		return node;
	}
	//只在总节点中判断所有分支节点中是否存在该节点,该树为2级树,只搜索2遍
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		TreeItem* pGroupTree = m_childItems[i];
		QList<TreeItem*> list_ = pGroupTree->GetChildren();
		for (size_t j = 0 ; j < list_.size() ; ++j )
		{
			STNode & stNode = list_[j]->GetNodeData();
			if ( stNode.node_id == node_id )
			{
				node = stNode;
				break;
			}
		}
	}
	return node;
}

TreeItem * TreeItem::GetGroupTreeNode(int group_id)
{
	TreeItem * item_ = nullptr;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		if (node.IsGroup && node.group_id == group_id )
		{
			item_ = m_childItems[i];
			break;
		}
	}
	return item_;
}

void TreeItem::SetNodeData(const STNode & node)
{
	if ( node.node_id ==m_stNode.node_id && node.group_id == m_stNode.group_id )
	{
		m_stNode = node;
	}
}

void TreeItem::ChangeNodeDataInTreeGroup(const STNode & node)
{
	for ( size_t j = 0 ; j < m_childItems.size() ; ++j )
	{
		STNode& stNode = m_childItems[j]->GetNodeData();
		if ( node.node_id ==stNode.node_id && node.group_id == stNode.group_id )
		{
			m_childItems[j]->SetNodeData(node);
			break;
		}
	}
	UpdateOnLineNum();
}

void TreeItem::UpdateOnLineNum()
{
	m_stNode.total = 0;
	m_stNode.online = 0;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		m_stNode.total++;
		if ( node.state > 0  )
		{
			m_stNode.online ++;
		}
	}
}

bool TreeItem::DeleteItemNode(const STNode& stNode )
{
	bool bDel = false;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		if (stNode.node_id == node.node_id && stNode.group_id == node.group_id)
		{
			TreeItem* item = m_childItems[i];
			delete item; 
			item = NULL;
			m_childItems.removeAt(i);
			bDel = true;
			break;
		}
	}
	if (bDel)
	{
		UpdateOnLineNum();
	}
	return bDel;
}

bool TreeItem::DeleteGroupNode(const STNode& stNode)
{
	bool bDel = false;
	for (size_t i = 0 ; i < m_childItems.size() ; ++i )
	{
		STNode & node = m_childItems[i]->GetNodeData();
		if ( stNode.group_id == node.group_id )
		{
			TreeItem* item = m_childItems[i];
			delete item; 
			item = NULL;
			m_childItems.removeAt(i);
			bDel = true;
			break;
		}
	}
	return bDel;
}