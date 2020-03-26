#ifndef QXEQUIPMENTDB_H
#define QXEQUIPMENTDB_H
#include <QObject>
#include <QSqlDatabase>
#include "BaseDataDef.h"
#define LOCAL_DB_NAME QStringLiteral("./db/EQuipmentEx.db3")
#define EquipmentEffect QStringLiteral("EquipmentEffect");
class QxEquipmentDB 
{
public:
	explicit QxEquipmentDB();
	~QxEquipmentDB();
	static QxEquipmentDB* getInstance();
	static void deleteInstance();

public:
	void createTable(const QString & table);
	void exitSqlDataBase();
	void setEffectDataBaseName(const QString & databaseName );
	void setEffectPassword(const QString & password );
	QSqlDatabase addEffectDataBase(const QString &type,const QString &connectionName);
	QSqlDatabase addEffectDataBase(QSqlDriver* driver,const QString &connectionName);
	//判断存在
	bool isTableExist(const QString & table);
	bool isEquipmentExist(int iEquipmentId);
	bool isLegendExist(int iLegendId);
	bool isDevelopPropExist(int uiId);
	//此查询只针对首列为INT类型
	bool isItemExist(const QVariant & var, EEquipmentEffect eType);
	//查询
	QVector<QVariant> selectSTEquipmentTable(const QString & sql);
	QVector<QVariant> selectSTLegendTable(const QString & sql);
#if 0
	QVector<QVariant> selectDevelopPropTable(const QString & sql);
#endif
	
	//查询Item
	QVariant selectItem(DWORD nPrimaryKey,ETable eTable);
	QVariant selectEffectItem(const QString & sql);
	//导入Vec
	void insertItem(const QVariant & var,ETable eTable);
	//导入Item
	void insertSTTable(const QVector<QVariant> & vecVariant,ETable eTable);
	//导入数据列表进入装备表
	bool insertSTEquipmentTable(const QVector<STEquipment> & vecEquipment);
	bool updateSTEquipmentTable(STEquipment stEquipment);
	bool insertSTEquipmentTable(STEquipment stEquipment);
	//导入数据列表进入英雄表
	bool insertSTLegendTable(const QVector<STEquipmentLegend> & vecEquipment);
	bool updateSTLegendTable(STEquipmentLegend stEquipmentLegend);
	bool insertSTLegendTable(STEquipmentLegend stEquipmentLegend);
#if 0
	//导入数据列表进入养成道具表
	bool insertSTUserHeroCultivateItem(const TSTUserHeroCultivateItemVector & tSTUserHeroCultivateItemVector);
	bool updateSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool insertSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool updateRepairHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool updateSTCultivateItemChange(const STCultivateItemChangeNotify& stCultivateItemChangeNotify);
	//更新修复成本
	int GetRepairCost(int uiItemId);
	bool updateRepairCost(int uiItemId,int uiRepairCost);
	//更新购买信息
	bool updateBuyHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
#endif
	

	
	//更新Item
	void updateItem(const QVariant & var,ETable eTable);
	void dropTable(const QString & table);
	//创建装备表
	bool createEquipmentEffectTable();
	//创建英雄表
	bool createLegendTable();
	//创建养成道具表
#if 0
	bool createDevelopPropTable();
#endif
	
	//清空
	void clearDB();
	void clearLegendTable();
	void removeLocalDB();
private:
	QSqlDatabase m_sqldb;
	QStringList  m_listTables;
	static QxEquipmentDB* m_ptrInstance;
};
#endif