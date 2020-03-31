#ifndef BASEMOVEDLG_H
#define BASEMOVEDLG_H
#include <QDialog>

enum EScaleType
{
	eScaleTypeNone   = 0,
	eScaleTypeLeft   = 1,
	eScaleTypeTop	 = 2,
	eScaleTypeRight	 = 3,
	eScaleTypeBottom = 4,
};

class BaseMoveDlg : public QWidget
{
	Q_OBJECT
public:
	explicit BaseMoveDlg(QWidget *parent = NULL);
	~BaseMoveDlg();

public:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void resizeEvent(QResizeEvent *event);
	void AdjustSize(EScaleType eScaleType,int scale_w,int scale_h);
	void Move(EScaleType eScaleType, int scale_w, int scale_h, QMouseEvent *e);
private:
	QPoint  m_relativeInit;
	bool    m_bLeftBtnPress;
	bool	m_bResize;

	int		m_nMinWidth;
	int		m_nMinHeight;
	int		m_nMaxWidth;
	int		m_nMaxHeight;
	EScaleType m_eScaleType;
};
#endif