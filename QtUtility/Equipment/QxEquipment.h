#ifndef QXEQUIPMENT_H
#define QXEQUIPMENT_H
/************************************************************************/
/* װ������                                                             */
/************************************************************************/
#include <QPushButton>
#include <QScrollArea>
#include <QButtonGroup>
#include "BaseActions.h"
#include "EquipmentEffectModule.h"
#include "QxEquipmentTableView.h"
#include "EquipmentSetModule.h"
#include "RecommandModule.h"
#include "EquipmentTip.h"

enum EEquipmentBtnType
{
	eEquipmentBtnTypeSimplify = 1,
	eEquipmentBtnTypeAll = 2,
};

class QxEquipment : public QWidget , public BaseActions
{
	Q_OBJECT
public:
	explicit QxEquipment(QWidget* parent = NULL);
	~QxEquipment();
	static QxEquipment * m_pQxEquipmentObj;
	static QxEquipment * getInstance();
	static void DeleteInstance();
protected:
	//�źŲ�����
	virtual void InitConnections() ;
	//��ʼ��һ�Ż������ʽ��
	virtual void InitStyleSheets() ;
	//���ع��ʻ�����
	virtual void LoadTranslator()  ;
	//ģ�黯���ã�UIģ������
	virtual void InitModules() ;
	//����ͼƬ��Դ
	virtual void InitPixmap() ;
	//�ؼ���ʼ��
	virtual void InitCtrls() ;
	//��ʼ����������
	virtual void InitWindowFlags() ;

	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void showEvent(QShowEvent *);
	virtual void hideEvent(QHideEvent *);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	
public:
	//����ɸѡģ��ɼ�
	void setEffectModuleVisible(bool visable);
	void updateEquipmentTable(QString sql = "");
	//����ģʽ�����е���ģʽ�ı�װ�����ĸ߶�
	void resizeEquipmentTableHeight(QRect rect);
	//��ʾ����������ʾ��
	void showEquipmentTip(QPoint pos,STEquipment stEquipment ,bool bShow = false);
	void hideEquipmentTip();
	//��ѯ��ǰ�����������Ǵ��ڵ�����
	bool IsEquipmentTypeExist(int nType);
	//����Ӣ��Id
	void setLegendId(DWORD dwLegendId);

	public slots:
		//װ�����Ը�ѡ���źŲ�
		void OnCheckBoxTypeClicked(const QVector<int> & vecType);
		//����ģʽ��ť,���е��߰�ť�ۺ���
		void OnEquipmentSimplifyBtnClicked();
		void OnEquipmentAllBtnClicked();
		//����ť�����е��߰�ť
		void OnEquipmentBtnTypeClicked(int);
private:
	//�������ػ��ڴ����ݿ�
	void consctuctData();
	QString getSqlStringByEffectType(EEquipmentEffect);
	//ͬ����ѡ��enable״̬
	void syncEquipmentEffectCheckBoxState();
	//ͬ����ѡ��enable״̬
	void syncEquipmentEffectRadioBoxState();
private:
	//��ѡ��
	EquipmentEffectModule* m_pEquipmentEffectModule;
	//���������ʾ
	QxEquipmentTableView* m_pEquipmentTable;
	//����ģʽ��ť
	QButtonGroup* m_pEquipmentGroup;
	QPushButton* m_pEquipmentSimplify;
	//���е��߰�ť
	QPushButton* m_pEquipmentAll;
	//���ֶ�ʹ���뾫��ģʽ�����е��ߵ��л�
	QVector<int> m_vecCheckType;
	//װ������
	EquipmentSetModule* m_pEquipmentSetModule;
	//�Ƽ���װģ��
	RecommandModule* m_pRecommandModule;
	//�Ƽ���װģ�������
	QScrollArea* m_pRecommandScrollBar;
	//ѡ�е�װ����������,������ߺ����е���
	EEquipmentBtnType m_eEquipmentBtnType;
	//װ����ʾ
	EquipmentTip* m_pEquipmentTip;
};
#endif