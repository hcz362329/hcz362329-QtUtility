#include "CTreeModel.h"  
#include <QtGui>  

CTreeModel::CTreeModel(QObject *parent)
	: QAbstractItemModel(parent)  
	, m_pRootItem(nullptr)
{  
	
}  

CTreeModel::~CTreeModel()  
{  
	delete m_pRootItem;  
	m_pRootItem=NULL;
}

QVariant CTreeModel::data(const QModelIndex &index, int role) const  
{  
	if (!index.isValid())  
		return QVariant();    
	if(role==Qt::DisplayRole) 
	{
#if MULTI_COLUMN
		TreeItem *item=static_cast<TreeItem*>(index.internalPointer()); 
		return item->data(index.column());  
#else
		QVariant v;
		TreeItem *item=static_cast<TreeItem*>(index.internalPointer()); 
		v.setValue(item->GetNodeData());
		return v;
#endif
	}

	return QVariant();  
}  

Qt::ItemFlags CTreeModel::flags(const QModelIndex &index) const  
{  
	if(!index.isValid())  
		return 0;  

	return Qt::ItemIsEnabled|Qt::ItemIsSelectable;  
}  

QVariant CTreeModel::headerData(int section, Qt::Orientation orientation,int role) const  
{  
	if ( m_pRootItem )
	{
		if(orientation==Qt::Horizontal&&role==Qt::DisplayRole)  
			return m_pRootItem->data(section);  
	}
	return QVariant();  
}  

QModelIndex CTreeModel::index(int row, int column,const QModelIndex &parent) const  
{  
	if(!hasIndex(row,column,parent))  
		return QModelIndex();  
	if ( m_pRootItem == NULL )
		return QModelIndex();
	TreeItem *parentItem;  
	if(!parent.isValid())  
	{  
		parentItem=m_pRootItem;  
	}else  
	{  
		parentItem=static_cast<TreeItem*>(parent.internalPointer());  
	}
	TreeItem *childItem=parentItem->child(row);  
	if(childItem)  
		return createIndex(row,column,childItem); // 展开树形,为子节点建立索引,挂载自定义节点对象  
	else  
		return QModelIndex();  
}  

QModelIndex CTreeModel::parent(const QModelIndex &index) const  
{  
	if(!index.isValid())  
		return QModelIndex();  
	if ( m_pRootItem == NULL )
		return QModelIndex();

	TreeItem *childItem=static_cast<TreeItem*>(index.internalPointer());  
	TreeItem *parentItem=childItem->parent();  

	// 顶层节点,直接返回空索引  
	if(parentItem==m_pRootItem)  
		return QModelIndex();  

	// 为父结点建立索引  
	return createIndex(parentItem->row(),0,parentItem);  
}  

int CTreeModel::rowCount(const QModelIndex &parent) const  
{  
	if ( m_pRootItem == NULL )
		return 0;
	TreeItem *parentItem;  

	if(!parent.isValid())  
		parentItem=m_pRootItem;  
	else  
		parentItem=static_cast<TreeItem*>(parent.internalPointer());  

	return parentItem->childCount(); // 返回父结点下子结点数目  
}  

int CTreeModel::columnCount(const QModelIndex &parent ) const  
{  
	if ( m_pRootItem == NULL )
		return 0;
#if MULTI_COLUMN
	int nColumn = 1;
	if (parent.isValid())
	{
		TreeItem* item = static_cast<TreeItem*>(parent.internalPointer());
		nColumn = item->columnCount();
	}
	else
	{
		nColumn = m_pRootItem->columnCount();
	}
	return nColumn;
#else
	return m_pRootItem->columnCount();
#endif
}

void CTreeModel::updateAll(QVector<QVariant> & vectorVariant)
{
	if ( vectorVariant.size() <=0)
	{
		return;
	}
	if(m_pRootItem)  
	{  
		delete m_pRootItem;  
		m_pRootItem=NULL;  
	}  

	if ( m_pRootItem == NULL )
	{
		m_pRootItem = new TreeItem;
	}
	if ( m_pRootItem != NULL )
	{
		for ( size_t i = 0 ; i < vectorVariant.size() ; ++i )
		{
			QList<QVariant> item_data;
			item_data.push_back(vectorVariant[i]);
			TreeItem * item = new TreeItem(item_data,m_pRootItem);
		}
	}
	// 刷新模型  
	beginResetModel();
	endResetModel();
}

void CTreeModel::UpdateAll(QVector<STNode>& vec)
{
	if ( vec.size() <=0)  

	{
		return;
	}
	if(m_pRootItem)  
	{  
		delete m_pRootItem;  
		m_pRootItem=NULL;  
	}  

	if ( m_pRootItem == NULL )
	{
		STNode stNode;
		m_pRootItem = new TreeItem(stNode);
	}
	if ( m_pRootItem != NULL )
	{
		for ( size_t i = 0 ; i < vec.size() ; ++i )
		{
			//判断vec[i]是否为组节点
			if (vec[i].IsGroup )
			{
				//判断组节点是否存在,不存在则创建
				if ( !m_pRootItem->IsGroupExist(vec[i].group_id) )
				{
					STNode stNode = vec[i];
					stNode.IsGroup = true;
					TreeItem * item = new TreeItem(stNode,m_pRootItem);
				}
			}
			else
			{
				//当前节点为非组节点
				//查询分组是否存在
				TreeItem* tree_group = nullptr;
				if ( !m_pRootItem->IsGroupExist(vec[i].group_id) )
				{
					//节点不存在,生成节点数据
					STNode stNode = vec[i];
					stNode.IsGroup = true;
					tree_group = new TreeItem(stNode,m_pRootItem);
				}
				else
				{
					tree_group = m_pRootItem->GetGroupTreeNode(vec[i].group_id);
				}
				if ( tree_group != nullptr )
				{
					//创建分支节点
					if (!tree_group->IsNodeExist(vec[i].node_id))
					{
						TreeItem * item = new TreeItem(vec[i],tree_group);
					}
				}
			}
		}
	}
	// 刷新模型  
	ResetModel();
}

void CTreeModel::AddNode(STNode& stNode,bool AddInDefault)
{
	if(m_pRootItem)
	{
		//宁愿多写一行代码也要代码清晰
		//判断根节点中的所有子节点是否存在该数据
		if (m_pRootItem->CheckIsExistInAll2NdNode(stNode) && !AddInDefault)
		{
			MessageBoxA(0,"Node exist",0,0);
			return;
		}
		//判断stNode是否为组节点
		if (stNode.IsGroup )
		{
			//判断组节点是否存在,不存在则创建
			if ( !m_pRootItem->IsGroupExist(stNode.group_id) )
			{
				STNode stNode_Root = stNode;
				stNode_Root.IsGroup = true;
				TreeItem * item = new TreeItem(stNode_Root,m_pRootItem);
			}
		}
		else
		{
			//当前节点为非组节点
			//查询分组是否存在
			TreeItem* tree_group = nullptr;
			if ( !m_pRootItem->IsGroupExist(stNode.group_id) )
			{
				//节点不存在,生成节点数据
				stNode.IsGroup = true;
				tree_group = new TreeItem(stNode,m_pRootItem);
				stNode.IsGroup = false;//重置为false,节点数据信息
			}
			else
			{
				tree_group = m_pRootItem->GetGroupTreeNode(stNode.group_id);
			}
			if ( tree_group != nullptr )
			{
				//创建分支节点
				if (!tree_group->IsNodeExist(stNode.node_id))
				{
					TreeItem * item = new TreeItem(stNode,tree_group);
					ResetModel();
				}
			}
		}
	}
}

void CTreeModel::UpdateNode(STNode & stNode)
{
	if(m_pRootItem)
	{
		//判断m_pRootItem分支节点中是否存在该节点
		if (m_pRootItem->CheckIsExistInAll2NdNode(stNode))
		{
			STNode node = m_pRootItem->GetNodeDataByNodeId(stNode.node_id);
			if (node.node_id==-1)
			{
				//函数调用不符合约定
				return;
			}
			//获取分组
			TreeItem* tree_group = nullptr;
			if ( stNode.group_id != node.group_id )
			{
				DeleteNode(node);
				AddNode(stNode);
			}
			else
			{
				tree_group = m_pRootItem->GetGroupTreeNode(stNode.group_id);
				if (tree_group)
				{
					//直接修改tree数据
					tree_group->ChangeNodeDataInTreeGroup(stNode);
				}
			}
		}
		else
		{
			AddNode(stNode);
		}
	}
	ResetModel();
}

void CTreeModel::DeleteNode(const STNode& stNode )
{
	if(m_pRootItem)
	{
		//获取分组
		TreeItem* tree_group = nullptr;
		if ( m_pRootItem->IsGroupExist(stNode.group_id) )
		{
			tree_group = m_pRootItem->GetGroupTreeNode(stNode.group_id);
			if (tree_group)
			{
				bool bDel = tree_group->DeleteItemNode(stNode);
				if (bDel)
				{
					ResetModel();
				}
			}
		}
	}
}

void CTreeModel::DeleteGroup(const STNode & node)
{
	if(m_pRootItem)
	{
		//获取分组
		TreeItem* tree_group = nullptr;
		if ( m_pRootItem->IsGroupExist(node.group_id) )
		{
			//获取所有分组的节点信息
			bool bDel = m_pRootItem->DeleteGroupNode(node);
			if ( bDel )
			{
				ResetModel();
			}
		}
	}
}

void CTreeModel::DeleteGroupNodeButSaveChildItem(const STNode& stNode)
{
	if(m_pRootItem)
	{
		//获取分组
		TreeItem* tree_group = nullptr;
		if ( m_pRootItem->IsGroupExist(stNode.group_id) )
		{
			//删除前保存至默认分组

			TreeItem* treeGroup = m_pRootItem->GetGroupTreeNode(stNode.group_id);
			if (treeGroup)
			{
				QList<TreeItem*> list_ = treeGroup->GetChildren();
				for ( size_t j = 0 ; j < list_.size() ; ++j )
				{ 
					STNode stNode = list_[j]->GetNodeData();
					stNode.group_id = 0;
					stNode.strGroupName = L"默认分组";
					AddNode(stNode,true);
				}
			}

			//获取所有分组的节点信息
			bool bDel = m_pRootItem->DeleteGroupNode(stNode);
			if ( bDel )
			{
				ResetModel();
			}
		}
	}
}

void CTreeModel::ResetModel()
{
	beginResetModel();
	endResetModel();
}