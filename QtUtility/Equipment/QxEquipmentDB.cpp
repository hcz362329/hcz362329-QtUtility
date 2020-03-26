#include "stdafx.h"
#include "QxEquipmentDB.h"
#define Local_Db_Enabled 1
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include <QApplication>
#include <QSqlError>
#include <QSqlDriver>
//#include "Log4cplusWrapper.h"
QxEquipmentDB* QxEquipmentDB::m_ptrInstance=nullptr;

QxEquipmentDB::QxEquipmentDB()
{
	m_ptrInstance = this;
	QString strDriver;
#if Local_Db_Enabled
	strDriver = "QSQLITE";
#else
	strDriver = QString("QSQLITECIPHER");
#endif
	if (QSqlDatabase::isDriverAvailable(strDriver) )
	{
		addEffectDataBase(strDriver,"EQUIPMENT_CONN");
		setEffectDataBaseName(LOCAL_DB_NAME);
		setEffectPassword("");
		if ( m_sqldb.isValid() )
		{
			bool bOpen = m_sqldb.open("","");
			if ( bOpen )
			{
				qDebug()<<"open equipment db!";
			}
			else
			{
				qDebug()<<"cannot open equipment db!";
			}
		}
	}
	else
	{
		qDebug()<<"drivers not contains:"<<strDriver;
	}
}

QxEquipmentDB::~QxEquipmentDB()
{
	exitSqlDataBase();
	m_ptrInstance = NULL;
}

QxEquipmentDB* QxEquipmentDB::getInstance()
{
	if ( m_ptrInstance == nullptr )
	{
		new QxEquipmentDB();
	}
	return m_ptrInstance;
}

void QxEquipmentDB::deleteInstance()
{
	delete m_ptrInstance;
}

void QxEquipmentDB::createTable(const QString & table)
{
	if ( m_listTables.contains(table) )
	{
		qWarning("table: %s is exists", table.toLatin1().data());
		qWarning("table: exists tables: %s",m_listTables.join(QLatin1Char(' ')).toLatin1().data());
	}
	else
	{
		if ( table.compare("EquipmentEffect") == 0 )
		{
			if ( isTableExist(table) )
			{
				QSqlQuery query(m_sqldb);
				QString strSql = QString("drop table %1;").arg(table);
				bool bDelete =query.exec(strSql);
				qDebug()<<"delete table "<<table<<":"<<bDelete;
			}
			bool bCreate = createEquipmentEffectTable();
			if ( bCreate )
			{
				m_listTables << table;
			}
			else
			{
				qInfo("table: EquipmentEffect is create failed");
			}
		}
		if ( table.compare("Legend") == 0 )
		{
			if ( isTableExist(table) )
			{
				QSqlQuery query(m_sqldb);
				QString strSql = QString("drop table %1;").arg(table);
				bool bDelete =query.exec(strSql);
				qDebug()<<"delete table "<<table<<":"<<bDelete;
			}
			bool bCreate = createLegendTable();
			if ( bCreate )
			{
				m_listTables << table;
			}
			else
			{
				qInfo("table: Legend is create failed");
			}
		}
		if ( table.compare("DevelopProp") == 0)
		{
			if ( isTableExist(table) )
			{
				QSqlQuery query(m_sqldb);
				QString strSql = QString("drop table %1;").arg(table);
				bool bDelete =query.exec(strSql);
				qDebug()<<"delete table "<<table<<":"<<bDelete;
			}
			bool bCreate =false /*createDevelopPropTable()*/;
			if ( bCreate )
			{
				m_listTables << table;
			}
			else
			{
				qInfo("table: DevelopProp is create failed");
			}
		}
	}
}

bool QxEquipmentDB::createEquipmentEffectTable()
{
	bool bCreate = false;
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		QString strCreate = QString("create table EquipmentEffect(\
			iEquipmentId int32 primary key,\
			uiItemOrder int32 ,\
			iDisplay    int32,\
			strEquipmentEffect varchar(64),\
			strEquipmentName varchar(64),\
			strEquipmentIcon varchar(64),\
			strItemName		varchar(64),\
			iEquipmentEffectCost int32);");
		if ( query.exec(strCreate) )
		{
			bCreate = true;
		}
	}
	qDebug()<<"create table EquipmentEffect"<<bCreate;
	return bCreate;
}

bool QxEquipmentDB::createLegendTable()
{
	bool bCreate = false;
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		QString strCreate = QString("create table Legend(\
									iLegendId int32 primary key,\
									strLegendName varchar(64),\
									strLegendIcon varchar(64),\
									eLegendType int32,\
									iLevel int32,\
									iIsOwn int32);");
		if ( query.exec(strCreate) )
		{
			bCreate = true;
		}
	}
	qDebug()<<"create table Legend"<<bCreate;
	return bCreate;
}
#if 0
bool QxEquipmentDB::createDevelopPropTable()
{
	bool bCreate = false;
	QString strCreate;
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		STUserHeroCultivateItem;
		QSqlQuery query(m_sqldb);
		strCreate = QString("create table DevelopProp(\
							uiItemId int32 primary key,\
							strName VARCHAR(64),\
							uiSlotMask int32,\
							bIsOwned int,\
							uiDurability int32,\
							uiMaxDurability int32,\
							strDesc VARCHAR(64),\
							uiPrice int32,\
							uiItemLevel int32,\
							strItemQuality VARCHAR(64),\
							strItemIcon VARCHAR(64),\
							uiRepairCost int32);");
		if ( query.exec(strCreate) )
		{
			bCreate = true;
		}
	}
	qDebug()<<"create table DevelopProp"<<bCreate<<"strCreate:"<<strCreate;
	return bCreate;
}
#endif


void QxEquipmentDB::exitSqlDataBase()
{
	clearDB();
	if ( m_sqldb.isOpen() )
	{
		m_sqldb.close();
	}
	if ( m_sqldb.isValid() )
	{
		QSqlDatabase::removeDatabase(m_sqldb.connectionName());

#if Local_Db_Enabled
		removeLocalDB();
#endif
	}
}

void QxEquipmentDB::setEffectDataBaseName(const QString & databaseName )
{
	if ( m_sqldb.isValid() )
	{
#if Local_Db_Enabled
		m_sqldb.setDatabaseName(databaseName);
#else
		m_sqldb.setDatabaseName("");
#endif
	}
}

void QxEquipmentDB::setEffectPassword(const QString & password )
{
	if ( m_sqldb.isValid() )
	{

	}
}

QSqlDatabase QxEquipmentDB::addEffectDataBase(const QString &type,const QString &connectionName)
{
	return m_sqldb = QSqlDatabase::addDatabase(type,connectionName);
}

QSqlDatabase QxEquipmentDB::addEffectDataBase(QSqlDriver* driver,const QString &connectionName)
{
	return m_sqldb = QSqlDatabase::addDatabase(driver,connectionName);
}

bool QxEquipmentDB::isTableExist(const QString & table)
{
	bool isExist = false;
	if ( m_sqldb.isValid() )
	{
		QSqlQuery query(m_sqldb);
		if (query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1';").arg(table)))
		{
			while(query.next())
			{
				isExist = query.value(0).toInt() == 0 ? false : true;
			}
		}
	}
	return isExist;
}

bool QxEquipmentDB::isEquipmentExist(int iEquipmentId)
{
	bool bExist = false;

	QSqlQuery query(m_sqldb);
	QString sql = QString("select count(*) from EquipmentEffect where iEquipmentId = %1 ").arg(iEquipmentId);
	if (query.exec(sql))
	{
		while(query.next())
		{
			bExist = query.value(0).toInt() == 0 ? false : true;
		}
	}
	else
	{
		qDebug() << query.lastError();
	}
	return bExist;
}

bool QxEquipmentDB::isLegendExist(int iLegendId)
{
	bool bExist = false;

	QSqlQuery query(m_sqldb);
	QString sql = QString("select count(*) from Legend where iLegendId = %1 ").arg(iLegendId);
	if (query.exec(sql))
	{
		while(query.next())
		{
			bExist = query.value(0).toInt() == 0 ? false : true;
		}
	}
	else
	{
		qDebug() << query.lastError();
	}
	return bExist;
}

bool QxEquipmentDB::isDevelopPropExist(int uiId)
{
	bool bExist = false;

	QSqlQuery query(m_sqldb);
	QString sql = QString("select count(*) from DevelopProp where uiItemId = %1 ;").arg(uiId);
	if (query.exec(sql))
	{
		while(query.next())
		{
			bExist = query.value(0).toInt() == 0 ? false : true;
		}
	}
	else
	{
		qDebug() << query.lastError();
	}
	return bExist;
}

bool QxEquipmentDB::isItemExist(const QVariant & var, EEquipmentEffect eType)
{
	return false;
}

QVector<QVariant> QxEquipmentDB::selectSTEquipmentTable(const QString & sql)
{
	//LOG_FUN("");
	QVector<QVariant> vecVar;
	if ( m_sqldb.isValid() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug() << query.lastError();
		}
		else
		{
			while ( query.next() )
			{
				STEquipment stEquipment;
				stEquipment.iEquipmentId		= query.value("iEquipmentId").toInt();
				stEquipment.iItemOrder			= query.value("uiItemOrder").toInt();
				stEquipment.iDisplay			= query.value("iDisplay").toInt();
				strcpy(stEquipment.strEquipmentEffect,query.value("strEquipmentEffect").toString().toLocal8Bit());
				strcpy(stEquipment.strEquipmentName,query.value("strEquipmentName").toString().toLocal8Bit());
				strcpy(stEquipment.strEquipmentIcon,query.value("strEquipmentIcon").toString().toLocal8Bit());
				strcpy(stEquipment.strItemName,query.value("strItemName").toString().toLocal8Bit());
				stEquipment.iEquipmentEffectCost= query.value("iEquipmentEffectCost").toInt();
				QVariant var;
				var.setValue(stEquipment);
				if ( stEquipment.iDisplay )
				{
					vecVar.push_back(var);
				}
			}
		}
	}
	////LOG_INFO("查询道具结果总数:"<<vecVar.size());
	return vecVar;
}

QVector<QVariant> QxEquipmentDB::selectSTLegendTable(const QString & sql)
{
	QVector<QVariant> vecVar;
	if ( m_sqldb.isValid() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug() << query.lastError();
		}
		else
		{
			while ( query.next() )
			{
				STEquipmentLegend stEquipmentLegend;
				stEquipmentLegend.iLegendId		= query.value("iLegendId").toInt();
				strcpy(stEquipmentLegend.strLegendName,query.value("strLegendName").toString().toLocal8Bit());
				strcpy(stEquipmentLegend.strLegendIcon,query.value("strLegendIcon").toString().toLocal8Bit());
				stEquipmentLegend.eLegendType	= (ELegendType)query.value("eLegendType").toInt();
				stEquipmentLegend.iLevel = query.value("iLevel").toInt();
				stEquipmentLegend.eHeroStatusFlag = (EHeroStatusFlag)query.value("iIsOwn").toInt();
				QVariant var;
				var.setValue(stEquipmentLegend);
				vecVar.push_back(var);
			}
		}
	}
	return vecVar;
}
#if 0
QVector<QVariant> QxEquipmentDB::selectDevelopPropTable(const QString & sql)
{
	QVector<QVariant> vecVar;
	if ( m_sqldb.isValid() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug() << query.lastError();
		}
		else
		{
			while ( query.next() )
			{
				STUserHeroCultivateItem stUserHeroCultivateItem;
				stUserHeroCultivateItem.uiItemId			= query.value("uiItemId").toUInt();
				stUserHeroCultivateItem.strName	= query.value("strName").toString().toStdWString();
				stUserHeroCultivateItem.uiSlotMask	= query.value("uiSlotMask").toUInt();
				stUserHeroCultivateItem.bIsOwned = query.value("bIsOwned").toBool();
				stUserHeroCultivateItem.uiDurability = query.value("uiDurability").toUInt();
				stUserHeroCultivateItem.uiMaxDurability = query.value("uiMaxDurability").toUInt();
				stUserHeroCultivateItem.strDesc = query.value("strDesc").toString().toStdWString();
				stUserHeroCultivateItem.uiPrice = query.value("uiPrice").toUInt();
				stUserHeroCultivateItem.uiItemLevel = query.value("uiItemLevel").toUInt();
				stUserHeroCultivateItem.strItemQuality = query.value("uiPrice").toString().toStdWString();
				stUserHeroCultivateItem.strItemIcon = query.value("strItemIcon").toString().toStdWString();
				stUserHeroCultivateItem.uiRepairCost = query.value("uiRepairCost").toUInt();
				QVariant var;
				var.setValue(stUserHeroCultivateItem);
				vecVar.push_back(var);
			}
		}
	}
	return vecVar;
}
#endif


QVariant QxEquipmentDB::selectItem(DWORD nPrimaryKey,ETable eTable)
{
	QVariant var;
	return var;
}

QVariant QxEquipmentDB::selectEffectItem(const QString & sql)
{
	QVariant var;
	return var;
}

void QxEquipmentDB::insertItem(const QVariant & var,ETable eTable)
{

}

void QxEquipmentDB::insertSTTable(const QVector<QVariant> & vecVariant,ETable eTable)
{

}

void QxEquipmentDB::updateItem(const QVariant & var,ETable eTable)
{

}

bool QxEquipmentDB::insertSTEquipmentTable(const QVector<STEquipment> & vecEquipment)
{
	//LOG_FUN("");
	//使用事务
	if ( isTableExist("EquipmentEffect") )
	{
		if ( m_sqldb.transaction() )//transaction()中会判断m_sqldb.driver()->hasFeature(QSqlDriver::Transactions)
		{
			////LOG_INFO("Prepare Insert vecEquipment Begin");
			for ( int nIndex = 0; nIndex < vecEquipment.size();++nIndex )
			{
#if 1
				if ( isEquipmentExist(vecEquipment[nIndex].iEquipmentId) )
				{
					updateSTEquipmentTable(vecEquipment[nIndex]);
				}
				else
				{
					insertSTEquipmentTable(vecEquipment[nIndex]);
				}
#else
				insertSTEquipmentTable(vecEquipment[nIndex]);
#endif
				
			}
			////LOG_INFO("Prepare Insert vecEquipment End");
			if ( m_sqldb.isOpen() )
			{
				if(!m_sqldb.commit())
				{
					qDebug() << m_sqldb.lastError(); //提交
					if(!m_sqldb.rollback())
						qDebug() << m_sqldb.lastError(); //回滚
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool QxEquipmentDB::insertSTLegendTable(const QVector<STEquipmentLegend> & vecEquipmentLegend)
{
	//使用事务
	if ( isTableExist("Legend") )
	{
		if ( m_sqldb.transaction() )//transaction()中会判断m_sqldb.driver()->hasFeature(QSqlDriver::Transactions)
		{
			for ( int nIndex = 0; nIndex < vecEquipmentLegend.size();++nIndex )
			{
				if ( isLegendExist(vecEquipmentLegend[nIndex].iLegendId) )
				{
					updateSTLegendTable(vecEquipmentLegend[nIndex]);
				}
				else
				{
					insertSTLegendTable(vecEquipmentLegend[nIndex]);
				}
			}
			if(!m_sqldb.commit())
			{
				qDebug() << m_sqldb.lastError(); //提交
				if(!m_sqldb.rollback())
					qDebug() << m_sqldb.lastError(); //回滚
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

bool QxEquipmentDB::updateSTLegendTable(STEquipmentLegend stEquipmentLegend)
{
	QSqlQuery query(m_sqldb);
	QString sql = QString("update Legend set  \
						  strLegendName = :strLegendName,\
						  strLegendIcon = :strLegendIcon,\
						  eLegendType = :eLegendType ,\
						  iLevel = :iLevel,\
						  iIsOwn = :iIsOwn  where iLegendId = %1").arg(stEquipmentLegend.iLegendId);
	query.prepare(sql);
	query.bindValue(":strLegendName", QString::fromLocal8Bit(stEquipmentLegend.strLegendName));
	query.bindValue(":strLegendIcon", QString::fromLocal8Bit(stEquipmentLegend.strLegendIcon));
	query.bindValue(":eLegendType", stEquipmentLegend.eLegendType);
	query.bindValue(":iLevel", stEquipmentLegend.iLevel);
	query.bindValue(":iIsOwn", (int)stEquipmentLegend.eHeroStatusFlag);
	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}

bool QxEquipmentDB::insertSTLegendTable(STEquipmentLegend stEquipmentLegend)
{
	QSqlQuery query(m_sqldb);
	query.prepare(QString("insert into Legend values (?,?,?,?,?,?);"));
	query.addBindValue(stEquipmentLegend.iLegendId);
	query.addBindValue(QString::fromLocal8Bit(stEquipmentLegend.strLegendName));
	query.addBindValue(QString::fromLocal8Bit(stEquipmentLegend.strLegendIcon));
	query.addBindValue(stEquipmentLegend.eLegendType);
	query.addBindValue(stEquipmentLegend.iLevel);
	query.addBindValue((int)stEquipmentLegend.eHeroStatusFlag);
	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}
#if 0

bool QxEquipmentDB::insertSTUserHeroCultivateItem(const TSTUserHeroCultivateItemVector & tSTUserHeroCultivateItemVector)
{
	//使用事务
	if ( isTableExist("Legend") )
	{
		if ( m_sqldb.transaction() )//transaction()中会判断m_sqldb.driver()->hasFeature(QSqlDriver::Transactions)
		{
			for ( int nIndex = 0; nIndex < tSTUserHeroCultivateItemVector.size();++nIndex )
			{
				if ( isDevelopPropExist(tSTUserHeroCultivateItemVector[nIndex].uiItemId) )
				{
					updateSTUserHeroCultivateItem(tSTUserHeroCultivateItemVector[nIndex]);
				}
				else
				{
					insertSTUserHeroCultivateItem(tSTUserHeroCultivateItemVector[nIndex]);
				}
			}
			if(!m_sqldb.commit())
			{
				qDebug() << m_sqldb.lastError(); //提交
				if(!m_sqldb.rollback())
					qDebug() << m_sqldb.lastError(); //回滚
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

bool QxEquipmentDB::updateSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem)
{
	/*
	int uiItemId;
	///装备名
	std::wstring strName;
	///描述
	std::wstring strDesc;
	///适用槽位的位掩码，1-16位分别对应1·16槽位是否适用
	int uiSlotMask;
	///属性数组
	TSTCultivateItemPropVector vecProperty;
	int uiDurabiliby;
	///物品分类
	ECultivateItemType eCultivateItemType; 
	///价格
	int uiPrice;
	int uiWeight;
	///修复成本
	int uiRepairCost;

	*/
	QSqlQuery query(m_sqldb);
	QString sql = QString("update DevelopProp set  \
						  strName = :strName,\
						  uiSlotMask = :uiSlotMask,\
						  bIsOwned = :bIsOwned,\
						  uiDurability = :uiDurability,\
						  uiMaxDurability = :uiMaxDurability ,\
						  strDesc = :strDesc ,\
						  uiPrice = :uiPrice ,\
						  uiItemLevel =:uiItemLevel,\
						  strItemQuality =:strItemQuality ,\
						  strItemIcon =:strItemIcon ,\
						  uiRepairCost=:uiRepairCost where uiItemId = %1").arg(stUserHeroCultivateItem.uiItemId);
	query.prepare(sql);
	query.bindValue(":strName",QString::fromStdWString(stUserHeroCultivateItem.strName));
	query.bindValue(":uiSlotMask",stUserHeroCultivateItem.uiSlotMask);
	query.bindValue(":bIsOwned",stUserHeroCultivateItem.bIsOwned);
	query.bindValue(":uiDurability",stUserHeroCultivateItem.uiDurability);
	query.bindValue(":uiMaxDurability",stUserHeroCultivateItem.uiMaxDurability);
	query.bindValue(":strDesc",QString::fromStdWString(stUserHeroCultivateItem.strDesc));
	query.bindValue(":uiPrice",stUserHeroCultivateItem.uiPrice);
	query.bindValue(":uiItemLevel",stUserHeroCultivateItem.uiItemLevel);
	query.bindValue(":strItemQuality",QString::fromStdWString(stUserHeroCultivateItem.strItemQuality));
	query.bindValue(":strItemIcon",QString::fromStdWString(stUserHeroCultivateItem.strItemIcon));
	query.bindValue(":uiRepairCost",stUserHeroCultivateItem.uiRepairCost);
	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}

bool QxEquipmentDB::updateRepairHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem)
{
	QSqlQuery query(m_sqldb);
	QString sql;
	if ( stUserHeroCultivateItem.uiItemId == 0 )
	{
		sql = QString("update DevelopProp set  \
					  uiDurability = uiMaxDurability,uiRepairCost = 0 where bIsOwned = 1;");
	}
	else
	{
		sql = QString("update DevelopProp set  \
					  uiDurability = uiMaxDurability,uiRepairCost = 0 where uiItemId = %1").arg(stUserHeroCultivateItem.uiItemId);
		
	}
	query.prepare(sql);

	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}

bool QxEquipmentDB::updateSTCultivateItemChange(const STCultivateItemChangeNotify& stCultivateItemChangeNotify)
{
	//LOG_FUN("");
	
	int uiItemId = stCultivateItemChangeNotify.uiItemId;
	///耐久度增量变化值，耐久加减值， +/-, 这里只告诉事件，客户端注意0和最大值得问题,只处理减法,修复的时候可以拿取当前值
	INT32 iDurability= stCultivateItemChangeNotify.iDurability; 
	//LOG_INFO("uiItemId:"<<uiItemId<<",iDurability:"<<iDurability);
	//只做减法
	if ( iDurability < 0 )
	{
		iDurability = qAbs(iDurability);
	}
	else
	{
		return false;
	}
	QSqlQuery query(m_sqldb);
	QString sql = QString("update DevelopProp set  uiDurability = uiDurability- %1 where uiItemId = %2 and uiDurability >= %1;").arg(iDurability).arg(uiItemId);
	query.prepare(sql);

	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	else
	{
		//更新修复成本
		updateRepairCost(uiItemId,GetRepairCost(uiItemId));
	}
	return true;
}

bool QxEquipmentDB::updateBuyHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem)
{
	QSqlQuery query(m_sqldb);
	QString sql = QString("update DevelopProp set  \
						  bIsOwned = 1 , uiDurability = uiMaxDurability where uiItemId = %1;").arg(stUserHeroCultivateItem.uiItemId);
	query.prepare(sql);

	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}

#endif


bool QxEquipmentDB::updateSTEquipmentTable(STEquipment stEquipment)
{
	QSqlQuery query(m_sqldb);
	QString sql = QString("update EquipmentEffect set  \
						  uiItemOrder = :uiItemOrder,\
						  iDisplay = :iDisplay,\
						  strEquipmentEffect = :strEquipmentEffect,\
						  strEquipmentName = :strEquipmentName,\
						  strEquipmentIcon = :strEquipmentIcon,\
						  strItemName = :strItemName,\
						 iEquipmentEffectCost = :iEquipmentEffectCost  where iEquipmentId = %1").arg(stEquipment.iEquipmentId);
	query.prepare(sql);
	query.bindValue(":uiItemOrder",stEquipment.iItemOrder);
	query.bindValue(":iDisplay",stEquipment.iDisplay);
	query.bindValue(":strEquipmentEffect", QString::fromLocal8Bit(stEquipment.strEquipmentEffect));
	query.bindValue(":strEquipmentName", QString::fromLocal8Bit(stEquipment.strEquipmentName));
	query.bindValue(":strEquipmentIcon", QString::fromLocal8Bit(stEquipment.strEquipmentIcon));
	query.bindValue(":strItemName", QString::fromLocal8Bit(stEquipment.strItemName));
	query.bindValue(":iEquipmentEffectCost", stEquipment.iEquipmentEffectCost);

	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}



bool QxEquipmentDB::insertSTEquipmentTable(STEquipment stEquipment)
{
	QSqlQuery query(m_sqldb);
	query.prepare(QString("insert into EquipmentEffect values (?,?,?,?,?,?,?,?);"));
	query.addBindValue(stEquipment.iEquipmentId);
	query.addBindValue(stEquipment.iItemOrder);
	query.addBindValue(stEquipment.iDisplay);
	query.addBindValue(QString::fromLocal8Bit(stEquipment.strEquipmentEffect));
	query.addBindValue(QString::fromLocal8Bit(stEquipment.strEquipmentName));
	query.addBindValue(QString::fromLocal8Bit(stEquipment.strEquipmentIcon));
	query.addBindValue(QString::fromLocal8Bit(stEquipment.strItemName));
	query.addBindValue(stEquipment.iEquipmentEffectCost);
	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}

#if 0
bool QxEquipmentDB::insertSTUserHeroCultivateItem(const STUserHeroCultivateItem & stUserHeroCultivateItem)
{
	QSqlQuery query(m_sqldb);
	query.prepare(QString("insert into DevelopProp values (?,?,?,?,?,?,?,?,?,?,?,?);"));
	query.addBindValue(stUserHeroCultivateItem.uiItemId);
	query.addBindValue(QString::fromStdWString(stUserHeroCultivateItem.strName));
	query.addBindValue(stUserHeroCultivateItem.uiSlotMask);
	query.addBindValue(stUserHeroCultivateItem.bIsOwned);
	query.addBindValue(stUserHeroCultivateItem.uiDurability);
	query.addBindValue(stUserHeroCultivateItem.uiMaxDurability);
	query.addBindValue(QString::fromStdWString(stUserHeroCultivateItem.strDesc));
	query.addBindValue(stUserHeroCultivateItem.uiPrice);
	query.addBindValue(stUserHeroCultivateItem.uiItemLevel);
	query.addBindValue(QString::fromStdWString(stUserHeroCultivateItem.strItemQuality));
	query.addBindValue(QString::fromStdWString(stUserHeroCultivateItem.strItemIcon));
	query.addBindValue(stUserHeroCultivateItem.uiRepairCost);
	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	else
	{
		//qDebug() << "insert into DevelopProp success";
	}
	return true;
}
#endif


void QxEquipmentDB::clearDB()
{
	if ( !m_listTables.isEmpty() )
	{
		for ( int nIndex = 0 ; nIndex < m_listTables.size() ; ++ nIndex )
		{
			dropTable(m_listTables[nIndex]);
		}
	}
	m_listTables.clear();
}

void QxEquipmentDB::clearLegendTable()
{
	QString sql = QString("delete  from  Legend");
	QSqlQuery query(m_sqldb);
	if ( !query.exec(sql) )
	{
		qWarning("table:clear legend failed!");
	}
}

void QxEquipmentDB::removeLocalDB()
{
	QDir dbDir(QApplication::instance()->applicationDirPath() + QString("/db"));
	if ( dbDir.exists() )
	{
		qDebug()<<"dir exists!";
		if ( dbDir.exists("EQuipmentEx.db3") )
		{
			qDebug()<<"EQuipmentEx.db3exist.";
			bool bRemove = dbDir.remove("EQuipmentEx.db3");
			qDebug()<<"remove EQuipmentEx.db3result :"<<bRemove;
		}
		else
		{
			qDebug()<<"EQuipmentEx.db3not exist.";
		}
	}
	else
	{
		qDebug()<<"dir not exists!";
	}
}

void QxEquipmentDB::dropTable(const QString & table)
{
	if ( isTableExist(table) )
	{
		if ( m_sqldb.isValid() )
		{
			QSqlQuery query(m_sqldb);
			if ( !query.exec(QString("drop table %1").arg(table)) )
			{
				qWarning("table:drop failed!");
			}
		}
	}
}
#if 0
int QxEquipmentDB::GetRepairCost(int uiItemId)
{
	int nCost = 1;
	QString sql = QString("select * from developprop where uiItemId = %1;").arg(uiItemId);
	QVector<QVariant> vec = selectDevelopPropTable(sql);
	if ( vec.size() > 0 )
	{
		STUserHeroCultivateItem stUserHeroCultivateItem = qvariant_cast<STUserHeroCultivateItem>(vec[0]);
		int uiPrice = stUserHeroCultivateItem.uiPrice;
		int uiMaxDurability = stUserHeroCultivateItem.uiMaxDurability;
		int uiCurDurability = stUserHeroCultivateItem.uiDurability;
		int nBroken = uiMaxDurability - uiCurDurability;
		if ( nBroken > 0 && uiMaxDurability > 0 )
		{
			nCost = (int)(uiPrice*(float)nBroken/(float)uiMaxDurability);
			nCost = qMax<int>(1,nCost);
		}
	}
	return nCost;
}

bool QxEquipmentDB::updateRepairCost(int uiItemId,int uiRepairCost)
{
	//LOG_FUN("");

	////LOG_INFO("uiItemId:"<<uiItemId<<",uiRepairCost:"<<uiRepairCost);

	QSqlQuery query(m_sqldb);
	QString sql = QString("update DevelopProp set  uiRepairCost = %1 where uiItemId = %2 ;").arg(uiRepairCost).arg(uiItemId);
	query.prepare(sql);

	if(!query.exec())
	{
		qDebug() << query.lastError();
	}
	return true;
}
#endif