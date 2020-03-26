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
		return createIndex(row,column,childItem); // չ������,Ϊ�ӽڵ㽨������,�����Զ���ڵ����  
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

	// ����ڵ�,ֱ�ӷ��ؿ�����  
	if(parentItem==m_pRootItem)  
		return QModelIndex();  

	// Ϊ����㽨������  
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

	return parentItem->childCount(); // ���ظ�������ӽ����Ŀ  
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
	// ˢ��ģ��  
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
			//�ж�vec[i]�Ƿ�Ϊ��ڵ�
			if (vec[i].IsGroup )
			{
				//�ж���ڵ��Ƿ����,�������򴴽�
				if ( !m_pRootItem->IsGroupExist(vec[i].group_id) )
				{
					STNode stNode = vec[i];
					stNode.IsGroup = true;
					TreeItem * item = new TreeItem(stNode,m_pRootItem);
				}
			}
			else
			{
				//��ǰ�ڵ�Ϊ����ڵ�
				//��ѯ�����Ƿ����
				TreeItem* tree_group = nullptr;
				if ( !m_pRootItem->IsGroupExist(vec[i].group_id) )
				{
					//�ڵ㲻����,���ɽڵ�����
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
					//������֧�ڵ�
					if (!tree_group->IsNodeExist(vec[i].node_id))
					{
						TreeItem * item = new TreeItem(vec[i],tree_group);
					}
				}
			}
		}
	}
	// ˢ��ģ��  
	ResetModel();
}

void CTreeModel::AddNode(STNode& stNode,bool AddInDefault)
{
	if(m_pRootItem)
	{
		//��Ը��дһ�д���ҲҪ��������
		//�жϸ��ڵ��е������ӽڵ��Ƿ���ڸ�����
		if (m_pRootItem->CheckIsExistInAll2NdNode(stNode) && !AddInDefault)
		{
			MessageBoxA(0,"Node exist",0,0);
			return;
		}
		//�ж�stNode�Ƿ�Ϊ��ڵ�
		if (stNode.IsGroup )
		{
			//�ж���ڵ��Ƿ����,�������򴴽�
			if ( !m_pRootItem->IsGroupExist(stNode.group_id) )
			{
				STNode stNode_Root = stNode;
				stNode_Root.IsGroup = true;
				TreeItem * item = new TreeItem(stNode_Root,m_pRootItem);
			}
		}
		else
		{
			//��ǰ�ڵ�Ϊ����ڵ�
			//��ѯ�����Ƿ����
			TreeItem* tree_group = nullptr;
			if ( !m_pRootItem->IsGroupExist(stNode.group_id) )
			{
				//�ڵ㲻����,���ɽڵ�����
				stNode.IsGroup = true;
				tree_group = new TreeItem(stNode,m_pRootItem);
				stNode.IsGroup = false;//����Ϊfalse,�ڵ�������Ϣ
			}
			else
			{
				tree_group = m_pRootItem->GetGroupTreeNode(stNode.group_id);
			}
			if ( tree_group != nullptr )
			{
				//������֧�ڵ�
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
		//�ж�m_pRootItem��֧�ڵ����Ƿ���ڸýڵ�
		if (m_pRootItem->CheckIsExistInAll2NdNode(stNode))
		{
			STNode node = m_pRootItem->GetNodeDataByNodeId(stNode.node_id);
			if (node.node_id==-1)
			{
				//�������ò�����Լ��
				return;
			}
			//��ȡ����
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
					//ֱ���޸�tree����
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
		//��ȡ����
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
		//��ȡ����
		TreeItem* tree_group = nullptr;
		if ( m_pRootItem->IsGroupExist(node.group_id) )
		{
			//��ȡ���з���Ľڵ���Ϣ
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
		//��ȡ����
		TreeItem* tree_group = nullptr;
		if ( m_pRootItem->IsGroupExist(stNode.group_id) )
		{
			//ɾ��ǰ������Ĭ�Ϸ���

			TreeItem* treeGroup = m_pRootItem->GetGroupTreeNode(stNode.group_id);
			if (treeGroup)
			{
				QList<TreeItem*> list_ = treeGroup->GetChildren();
				for ( size_t j = 0 ; j < list_.size() ; ++j )
				{ 
					STNode stNode = list_[j]->GetNodeData();
					stNode.group_id = 0;
					stNode.strGroupName = L"Ĭ�Ϸ���";
					AddNode(stNode,true);
				}
			}

			//��ȡ���з���Ľڵ���Ϣ
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