#ifndef LiveTimeView_h
#define LiveTimeView_h
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QListView>
#include <QFont>
#include <QPen>
class Delegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit Delegate(QObject* parent = NULL);
	~Delegate();

	void SetStep(int step_);
public:
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
private:
	QFont	font;
	QPen	pen;
	int nStep;
	QPixmap pixmap;
	QPixmap pixmap_select;
};

class Model : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit Model(QObject* parent = NULL);
	~Model();
protected:
	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
	void clearModel();
	void updateAll(const QVector<int>&);
private:
	QVector<int> vecInt;
};


class View : public QListView
{
	Q_OBJECT
public:
	explicit View(QWidget* parent = NULL);
	~View();
public:
	void initView();
	void initModelDelagate();
	//½«ÐÇ
	void updateAll(QVector<int>&);
	void SetMaxStep(int step);
signals:
	void sigSelect(const int &);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent* event);
signals:
private:
	Model*		m_pModel;
	Delegate*	m_pDelegate;
	int nStep;
	int maxStep;
};

#endif
