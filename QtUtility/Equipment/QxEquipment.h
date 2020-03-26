#ifndef QXEQUIPMENT_H
#define QXEQUIPMENT_H
/************************************************************************/
/* 装备主体                                                             */
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
	//信号槽连接
	virtual void InitConnections() ;
	//初始化一张或多张样式表
	virtual void InitStyleSheets() ;
	//加载国际化语言
	virtual void LoadTranslator()  ;
	//模块化设置：UI模块设置
	virtual void InitModules() ;
	//加载图片资源
	virtual void InitPixmap() ;
	//控件初始化
	virtual void InitCtrls() ;
	//初始化窗口设置
	virtual void InitWindowFlags() ;

	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void showEvent(QShowEvent *);
	virtual void hideEvent(QHideEvent *);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	
public:
	//设置筛选模块可见
	void setEffectModuleVisible(bool visable);
	void updateEquipmentTable(QString sql = "");
	//精简模式和所有道具模式改变装备表格的高度
	void resizeEquipmentTableHeight(QRect rect);
	//显示或者隐藏提示框
	void showEquipmentTip(QPoint pos,STEquipment stEquipment ,bool bShow = false);
	void hideEquipmentTip();
	//查询当前搜索条件中是存在的类型
	bool IsEquipmentTypeExist(int nType);
	//设置英雄Id
	void setLegendId(DWORD dwLegendId);

	public slots:
		//装备属性复选框信号槽
		void OnCheckBoxTypeClicked(const QVector<int> & vecType);
		//精简模式按钮,所有道具按钮槽函数
		void OnEquipmentSimplifyBtnClicked();
		void OnEquipmentAllBtnClicked();
		//精简按钮和所有道具按钮
		void OnEquipmentBtnTypeClicked(int);
private:
	//创建本地或内存数据库
	void consctuctData();
	QString getSqlStringByEffectType(EEquipmentEffect);
	//同步复选框enable状态
	void syncEquipmentEffectCheckBoxState();
	//同步单选框enable状态
	void syncEquipmentEffectRadioBoxState();
private:
	//复选框
	EquipmentEffectModule* m_pEquipmentEffectModule;
	//方案表格显示
	QxEquipmentTableView* m_pEquipmentTable;
	//精简模式按钮
	QButtonGroup* m_pEquipmentGroup;
	QPushButton* m_pEquipmentSimplify;
	//所有道具按钮
	QPushButton* m_pEquipmentAll;
	//该字段使用与精简模式和所有道具的切换
	QVector<int> m_vecCheckType;
	//装备配置
	EquipmentSetModule* m_pEquipmentSetModule;
	//推荐出装模块
	RecommandModule* m_pRecommandModule;
	//推荐出装模块滚动条
	QScrollArea* m_pRecommandScrollBar;
	//选中的装备区分类型,精简道具和所有道具
	EEquipmentBtnType m_eEquipmentBtnType;
	//装备提示
	EquipmentTip* m_pEquipmentTip;
};
#endif