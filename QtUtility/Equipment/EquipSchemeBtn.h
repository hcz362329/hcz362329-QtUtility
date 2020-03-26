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
	//����UI No�ڽ����ϵ���ʾλ��
	ESide m_eSide;
	//��������
	QString m_strSchemeName;
	//����UI No
	QString m_strSchemeUINo;
	//�༭��������
	QLineEdit *m_LESchemeName;
	//�༭��ť
	QPushButton *m_pEditBtn;
	//����UI Noλ��
	QRect m_rectUINo;
};
#pragma pack(pop)
#endif