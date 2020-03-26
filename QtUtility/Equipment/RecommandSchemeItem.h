#ifndef RECOMMANDSCHEMEITEM_H
#define RECOMMANDSCHEMEITEM_H
#include "EquipmentBase.h"
#include "BaseDataDef.h"
#include "EquipmentTip.h"
#include <QPushButton>
class RecommandSchemeItem : public EquipmentBase
{
	Q_OBJECT
public:
	explicit RecommandSchemeItem(QWidget* parent = NULL);
	~RecommandSchemeItem();
	void setSchemeId(int nRank = 0);
	//初始化装备槽位信息和位置
	void initCtrls();
	void setEquipmentMapInfo(const QMap<UINT,STEquipmentSet> & mapInfo);
	void recommandEquipmentPressed(QMouseEvent *);
	//装备提示信息加载
	void LoadEquipmentInfoTip(QMouseEvent *event);
	//设置推荐方案名称
	void SetSchemeName(std::wstring strName);
signals:
	void recomandEquipment(const STEquipmentSet & stEquipmentSet);
	void recomandEquipmentApply(const QMap<UINT,STEquipmentSet> & stEquipmentSetMap);
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void hideEvent(QHideEvent *);
	public slots:
		//应用推荐方案点击槽
		void OnApplySchemeBtnClicked();
private:
	QPixmap m_pixBG;
	QPixmap m_pixRankBG;
	//应用按钮
	QPushButton* m_pApplySchemeBtn;
	////当前操作的方案数据 QMap<槽位,装备>
	QMap<UINT,STEquipmentSet> m_mapSTEquipmentSet;
	//装备边框
	QPixmap m_pixBorder;
	//装备槽位底图
	QPixmap m_pixEquipmentSlotBG;
	//装备
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	QPoint m_pointDrag;
	//用户拖拽点击的装备
	STEquipmentSet m_stEquipmentSet;
	//选中标识
	QPixmap m_pixSelect;
	//排名
	int m_nRank;
	QString m_strSchemeName;
};
#endif