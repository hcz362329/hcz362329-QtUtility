#include "CTreeView.h"
#include <QMouseEvent>
TreeView::TreeView(QWidget* parent /* = nullptr */)
	: QTreeView(parent)
	, m_pDelegate(nullptr)
	, m_pModel(nullptr)
{
	InitTreeView();
}

TreeView::~TreeView()
{

}

void TreeView::InitTreeView()
{
	loadModelDelegate();
	setFrameShape(QFrame::NoFrame);
	//设置header隐藏
	setHeaderHidden(true);
	//设置张开属性
	setItemsExpandable(true);
	//设置缩进像素
	setIndentation(10);
}

void TreeView::loadModelDelegate()
{
	m_pModel = new CTreeModel(this);
	m_pDelegate = new CTreeDelegate(this);
	setModel(m_pModel);
	setItemDelegate(m_pDelegate);
}

void TreeView::mousePressEvent(QMouseEvent * event)
{
	if ( event->button() == Qt::LeftButton )
	{
		QModelIndex index = indexAt(event->pos());
		if (index.isValid())
		{
			STNode & stNode = qvariant_cast<STNode>(index.data(Qt::DisplayRole));
			if (stNode.IsGroup )
			{
				bool isExp = isExpanded(index);
				setExpanded(index,!isExpanded(index));
			}
		}
	}
	QTreeView::mousePressEvent(event);
}

void TreeView::updateAll(QVector<QVariant> & vectorVariant)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->updateAll(vectorVariant);
	}
	expandAll();
}

void TreeView::updateAll(QVector<STNode>& vec)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->UpdateAll(vec);
	}
}

void TreeView::AddNode(STNode & stNode)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->AddNode(stNode);
	}
	expandAll();
}

void TreeView::UpdateNode(STNode & stNode)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->UpdateNode(stNode);
	}
	expandAll();
}

void TreeView::DeleteNode(const STNode & node)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->DeleteNode(node);
	}
	expandAll();
}

void TreeView::DeleteGroup(const STNode & node)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->DeleteGroup(node);
	}
	expandAll();
}

void TreeView::DeleteGroupNodeButSaveChildItem(const STNode& stNode)
{
	if ( m_pModel != nullptr )
	{
		m_pModel->DeleteGroupNodeButSaveChildItem(stNode);
	}
	expandAll();
}