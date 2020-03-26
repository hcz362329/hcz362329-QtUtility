#ifndef EQUIPSCHEMEBTN_H
#define EQUIPSCHEMEBTN_H
#include <QPushButton>
#include <QLineEdit>
#pragma pack(push,_CRT_PACKING)

enum ESide
{
	eSideNone = 0,
	eSideLeft = 1,
	eSideRight = 2,
};

class EquipSchemeBtn : public QPushButton
{
	Q_OBJECT
public:
	explicit EquipSchemeBtn(int nSchemeNo,QWidget* parent = 0);
	~EquipSchemeBtn();
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual bool eventFilter(QObject *, QEvent *);
public:
	virtual void setText(const QString &text);
public:
	void setSide(ESide eSide);
	QString getSchemeName();
public slots:
	void OnEditBtnClicked();
	void OnTextChanged(const QString &);
private:
	//方案UI No在界面上的显示位置
	ESide m_eSide;
	//方案名称
	QString m_strSchemeName;
	//方案UI No
	QString m_strSchemeUINo;
	//编辑方案名称
	QLineEdit *m_LESchemeName;
	//编辑按钮
	QPushButton *m_pEditBtn;
	//方案UI No位置
	QRect m_rectUINo;
};
#pragma pack(pop)
#endif