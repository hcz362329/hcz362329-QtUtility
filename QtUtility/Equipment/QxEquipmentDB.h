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
	//�жϴ���
	bool isTableExist(const QString & table);
	bool isEquipmentExist(int iEquipmentId);
	bool isLegendExist(int iLegendId);
	bool isDevelopPropExist(int uiId);
	//�˲�ѯֻ�������ΪINT����
	bool isItemExist(const QVariant & var, EEquipmentEffect eType);
	//��ѯ
	QVector<QVariant> selectSTEquipmentTable(const QString & sql);
	QVector<QVariant> selectSTLegendTable(const QString & sql);
#if 0
	QVector<QVariant> selectDevelopPropTable(const QString & sql);
#endif
	
	//��ѯItem
	QVariant selectItem(DWORD nPrimaryKey,ETable eTable);
	QVariant selectEffectItem(const QString & sql);
	//����Vec
	void insertItem(const QVariant & var,ETable eTable);
	//����Item
	void insertSTTable(const QVector<QVariant> & vecVariant,ETable eTable);
	//���������б����װ����
	bool insertSTEquipmentTable(const QVector<STEquipment> & vecEquipment);
	bool updateSTEquipmentTable(STEquipment stEquipment);
	bool insertSTEquipmentTable(STEquipment stEquipment);
	//���������б����Ӣ�۱�
	bool insertSTLegendTable(const QVector<STEquipmentLegend> & vecEquipment);
	bool updateSTLegendTable(STEquipmentLegend stEquipmentLegend);
	bool insertSTLegendTable(STEquipmentLegend stEquipmentLegend);
#if 0
	//���������б�������ɵ��߱�
	bool insertSTUserHeroCultivateItem(const TSTUserHeroCultivateItemVector & tSTUserHeroCultivateItemVector);
	bool updateSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool insertSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool updateRepairHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
	bool updateSTCultivateItemChange(const STCultivateItemChangeNotify& stCultivateItemChangeNotify);
	//�����޸��ɱ�
	int GetRepairCost(int uiItemId);
	bool updateRepairCost(int uiItemId,int uiRepairCost);
	//���¹�����Ϣ
	bool updateBuyHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem);
#endif
	

	
	//����Item
	void updateItem(const QVariant & var,ETable eTable);
	void dropTable(const QString & table);
	//����װ����
	bool createEquipmentEffectTable();
	//����Ӣ�۱�
	bool createLegendTable();
	//�������ɵ��߱�
#if 0
	bool createDevelopPropTable();
#endif
	
	//���
	void clearDB();
	void clearLegendTable();
	void removeLocalDB();
private:
	QSqlDatabase m_sqldb;
	QStringList  m_listTables;
	static QxEquipmentDB* m_ptrInstance;
};
#endif