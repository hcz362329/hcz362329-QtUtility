#ifndef EQUIPMENTSCHEMEMODULE_H
#define EQUIPMENTSCHEMEMODULE_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "EquipSchemeBtn.h"

#include <QButtonGroup>
#include <QPushButton>
#include "EquipmentTip.h"
class EquipmentSchemeModule : public EquipmentBase
{
	Q_OBJECT
public:
	explicit EquipmentSchemeModule(QWidget* parent = NULL);
	~EquipmentSchemeModule();
	void setLegendScheme(int iLegendId);
	//初始化装备槽位信息和位置
	void initBaseData();
	//检验已装备
	bool isEquiped(const STEquipment & stEquipment);
	//设置第一个未装备区域的信息
	bool setFirstEmptyEquipmentInfo(const STEquipment & stEquipment);
	//选中区域位置移动
	void moveSelectEquipment();
	//加载装备方案按钮
	void loadSchemeBtn();
	//绑定逻辑模块信号
	void connectLogicalSignals();
	//设置装备的名称
	void setSchemeName(int nSchemeBtnPos,QString strName);
	//保存装备方案
	void ChangeEquipmentScheme();
	//判断方案信息是否发生变化
	bool isEquipmentSchemeInfoChanged();
	//装备提示信息加载
	void LoadEquipmentInfoTip(QMouseEvent *event);
	//装备方案Map信息用UnSaveMap替换
	void ChangeEquipmentSchemeMapToUnSaveMap();
	//设置是否由该模块发出获取英雄装备方案的请求
	void SetSendGetHeroSchemeReq(bool bSend);
	//获取是否由该模块发送的获取英雄装备信息请求
	bool GetSendGetHeroSchemeReq();
	//判断获取英雄方案的操作是否正确
	bool GetHeroSchemeRspValid(int uiHeroId);

	//设置拖动请求
	void SetDragReq(bool bDrag);
	bool GetDragReq();
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void hideEvent(QHideEvent *);
	virtual bool eventFilter(QObject *, QEvent *);
	//设置当前点击所在槽位的装备
	void setPressedSTEquipmentSet(QMouseEvent *event);
	///卸载装备
	void UnLoadSTEquipmentSet(QMouseEvent *event);
	//拖拽
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	//加载从道具表格和推荐装备中的拖拽装备
	void LoadDragEquipment(QDropEvent *event);
	//加载当前方案中内部拖拽的数据
	void LoadInnerDratEquipment(STEquipmentSet stEquipmentSet,QDropEvent *event);
	//获取方案Id,通过按钮点击位置:m_nSchemeBtnPos
	int getSchemIdBySchemeBtnPos(int nBtnPos);
	//获取装备信息,通过方案id
	QMap<UINT,STEquipmentSet> getEquipmentSetBySchemeId(int uiSchemeId);
	//获取上一次该方案中点击槽位状态的信息,通过方案按钮位置获取
	STEquipmentSet getSchemePressedEquipmentSetInfoBySchemePos(int nSchemePos);
	//获取方案名称,方案Id：1,2,3，可以跳过通过方案UIId获取方案ID
	QString getSchemeNameBySchemeId(int nScheme);
	//打印当前装备方案装备信息
	void OutputSchemeInfo();
	void updateEquipmentMapSet(QMap<UINT,STEquipmentSet> mapSTEquipmentSet);
	//设置装备方案名称编辑text
	void SetEditSchemeNameText();
public slots:
	void OnSchemeBtnClicked(int);
	void OnSaveSetBtnClicked();
	void OnRestClicked();
	//右键点击装备表格响应
	void OnEquipmentTableClicled(const STEquipment & stEquipment);
	//响应推荐装备模块点击信号
	void OnRecomandEquipment(const STEquipmentSet & stEquipmentSet);
	//响应推荐装备应用点击信号
	void OnRecomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
	//获取英雄选择结果
	void OnSelectLegend(const STEquipmentLegend & stEquipmentLegend);
	//获取英雄对应的方案信息和推荐方案信息
	void OnSTGetUserHeroConfigRsp(const STGetUserHeroConfigRsp&);
	//更改用户英雄配置信息响应信号
	void OnSTChangeUserHeroConfigRsp(const STChangeUserHeroConfigRsp&);

	void OnTextChanged(const QString &);
	void OnEditingFinished();
	//设置,获取UI界面发生变化
	void SetUIChanged(bool bChange);
	bool GetUIChanged();
private:
	QPixmap m_pixSchemeBG;
	//装备方案按钮,方案1,方案2,方案3,方案数量固定,但名称可改,用1,2,3标识
	QButtonGroup* m_pSchemeGroup;
	
	QPushButton* m_pSchemeBtn1;
	QPushButton* m_pSchemeBtn2;
	QPushButton* m_pSchemeBtn3;
	QMap<int,QPushButton*> m_mapSchemeBtn;

	/*EquipSchemeBtn* m_pSchemeBtn1;
	EquipSchemeBtn* m_pSchemeBtn2;
	EquipSchemeBtn* m_pSchemeBtn3;*/

	QPushButton* m_pSaveSetBtn;
	QPushButton* m_pRestBtn;
	//当前方案按钮对应的方案Id
	QMap<INT,int> m_mapBtnToScheme;
	//方案未报存的信息
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapUnSaveSTEquipmentScheme;
	//当前英雄的方案QMap<方案Id,装备方案>
	QMap<int,QMap<UINT,STEquipmentSet>> m_mapSTEquipmentScheme;
	//当前操作的方案数据 QMap<槽位,装备>
	QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
	//当前点击所在槽位的装备
	STEquipmentSet m_stEquipmentSet;
	//当前方案个数中保存上一次点击所在槽位的装备信息
	QMap<INT,STEquipmentSet> m_mapPressedEquipmentSet;
	//拖拽过来的装备数据保存
	STEquipment m_stDragEquipment;
	//当前点击方案按钮字段标识 从1开始标识,由此标识获取 方案Id,由方案id 获取具体装备信息
	int m_nSchemeBtnPos;
	//装备
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	//装备边框
	QPixmap m_pixBorder;
	//选中标识
	QPixmap m_pixSelect;
	//当前方案是否发生变化
	bool m_bChangeSchemeInfo;//UI变化信息 
	bool m_bSaveInfoChanged;//未经服务器保存的变化信息
	int m_uiLegendId;
	//拖拽位置的起始点
	QPoint m_pDragPoint;
	//方案名称
	QMap<int,std::wstring> m_mapIdToName;
	//设置是否由该模块发出获取英雄装备方案的请求
	bool m_bSendGetHeroSchemeReq;
	QLineEdit * m_pSchemeNameEdit;
	bool m_bDragReq;
	QMap<int, std::wstring> m_mapIdToEdit;
};

#endif