//edit by cz
#ifndef SqlDatabase_h
#define SqlDatabase_h
#include <QSqlDataBase>
#include <QStringList>
#include <QSqlIndex>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>

#define Conn_Name QStringLiteral("QXDB")
#if 0
#define RAM_ENABLED 0
#else
#if _DEBUG
#define RAM_ENABLED 1
#else
#define RAM_ENABLED 0
#endif
#endif


#define RAM_DB_NAME QStringLiteral("./db/2019.db3")
#define RAM_DB_DIR QStringLiteral("./db")

#include "select_hero_def.h"
#include "Data.h"
#define TEST_ENABLED 0
class SqlDatabase 
{
public:
	SqlDatabase();
	~SqlDatabase();
	static SqlDatabase* m_pInstance;
	static SqlDatabase* GetInstance();
	static void DeleteInstance();
	void SetDatabaseName(const QString& name);
	void SetUserName(const QString& name);
	void SetPassword(const QString& password);
	void AddDataBase(QSqlDriver* driver,const QString &connectionName);
	void AddDataBase(QString & type,const QString &connectionName);
	bool CreateTable(const QString & name);
	bool IsExistInDB(const QString & tablename);
	void InsertItem(const QString & sql);
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////hero////////////////////////////////////////////////////
	void InsertHero(const STHero & stHero);
	void UpdateHero(const STHero & stHero);
	void UpdateHeroStatus(const STHero & stHero);//可选或者不可选,0可选 1不可选
	void InsertVecItem(const QVector<STHero> & vec);
	
	void UpdateBeginSecond(const QVector<STHero> & vec);
	void UpdateHeroBeginSecond(const STHero & stHero);
	void InsertHeroBeginSecond(const STHero & stHero);

	void UpdateHeroBeginSecond(const int & BeginSecond);

	void UpdateItem(const QString & sql);
	void DeleteItem(const QString & sql);
	void DeleteItem(const STHero & stHero);
	void ClearHeroTable();
	bool IsHeroItemExist(int id);
	bool IsItemExist(const QString & sql);
	QVector<QVariant> selectHero(const QString & sql);
	/////////////////////hero///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////im////////////////////////////////////////////////////////////
	QVector<STNode> SelectNode(const QString & sql);
	void execSql(const QString & sql);
	void TestHero();
	void TestIm();
private:
	QSqlDatabase m_sqldb;
	QStringList m_tablelist;
};

#endif


