#include "LiveTimeView.h"
#include <QScrollBar>
#include <QMouseEvent>
#include <qDebug>
#include <QPainter>
View::View(QWidget* parent/* = NULL*/)
	: QListView(parent)
	, m_pModel(NULL)
	, m_pDelegate(NULL)
	, nStep(0)
	, maxStep(0)
{
	resize(60,66);
	initView();
}

View::~View()
{

}

void View::initView()
{
	setStyleSheet("border:none;background-color:rgba(255,255,255,0);");
	setSelectionBehavior(QAbstractItemView::SelectItems);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);			// 禁用H方向滚动条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	setFocusPolicy(Qt::NoFocus);
	verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

	initModelDelagate();
}

void View::initModelDelagate()
{
	if (m_pModel == NULL)
	{
		m_pModel = new Model(this);
		setModel(m_pModel);
	}
	if (m_pDelegate == NULL)
	{
		m_pDelegate = new Delegate(this);
		setItemDelegate(m_pDelegate);
	}
}

void View::updateAll(QVector<int>& vecInt)
{
	m_pModel->updateAll(vecInt);
}

void View::SetMaxStep(int step)
{
	maxStep = step;
}

void View::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QModelIndex index = indexAt(event->pos());
		if (index.isValid())
		{
			
		}
	}
	return QListView::mousePressEvent(event);
}

void View::wheelEvent(QWheelEvent* event)
{
#if 1
	double numDegrees = -event->delta() / 8.0;
	double numSteps = numDegrees / 15.0;
	nStep += numSteps;
	if (nStep<=0)
	{
		nStep = 0;
	}
	if (nStep>= maxStep)
	{
		nStep = maxStep;
	}
	verticalScrollBar()->setValue(nStep);
	if (m_pDelegate!=nullptr)
	{
		m_pDelegate->SetStep(nStep);
		int value = nStep + 1;
		emit sigSelect(value);
	}
	update();
#else
	return QListView::wheelEvent(event);
#endif
}

Model::Model(QObject* parent /*= NULL*/)
	: QAbstractListModel(parent)
{

}

Model::~Model()
{
	vecInt.clear();
}

int Model::rowCount(const QModelIndex & parent /*= QModelIndex()*/) const
{
	Q_UNUSED(parent);
	return vecInt.size();
}

QVariant Model::data(const QModelIndex & index, int role /* = Qt::DisplayRole */) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	if (role == Qt::DisplayRole)
	{
		QVariant v;
		int nIndex = index.row();
		if (nIndex>=0 && nIndex<vecInt.size())
		{
			v.setValue(vecInt[nIndex]);
		}
		return v;
	}
	return QVariant();
}

void Model::clearModel()
{
	if (vecInt.size() == 0)
	{
		beginRemoveRows(QModelIndex(), 0, vecInt.size());
	}
	else
	{
		beginRemoveRows(QModelIndex(), 0, vecInt.size() - 1);
	}
	vecInt.clear();
	endRemoveRows();
}

void Model::updateAll(const QVector<int>& vec)
{
	clearModel();
	vecInt << vec;
	if (vecInt.size() > 0)
	{
		beginInsertRows(QModelIndex(), 0, vecInt.size() - 1);
		endInsertRows();
	}
}


Delegate::Delegate(QObject* parent /*= NULL*/)
	: QStyledItemDelegate(parent)
	, nStep(0)
{
	font.setPixelSize(11);
	pen.setColor(QColor(255,255,255,153));

	pixmap.load(":/res/Resources/images/livetime_0.png");
	pixmap_select.load(":/res/Resources/images/livetime_1.png");
}

void Delegate::SetStep(int step_)
{
	nStep = step_;
}

Delegate::~Delegate()
{

}

QSize Delegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);
	return QSize(160, 30);
}

void Delegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	painter->save();
	if (index.isValid())
	{
		int nData = qvariant_cast<int>(index.data(Qt::DisplayRole));
		QRect rectItem = option.rect;
		QColor color;
		QBrush brush;
		
		int value = nStep + 1;
		if (value == nData)
		{
			painter->setPen(QColor(255,255,255,255));
			painter->drawPixmap(rectItem,pixmap_select);
		}
		else
		{
			painter->setPen(QColor(255, 255, 255, 153));
			painter->drawPixmap(rectItem, pixmap);
		}

		painter->setFont(font);
		
		painter->drawText(rectItem, Qt::AlignCenter,QString::number(nData));
	}
	painter->restore();
}

