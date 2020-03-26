#include "SqlDatabase.h"
#include <QDebug>
#include <QDir>

SqlDatabase* SqlDatabase::m_pInstance=nullptr;

SqlDatabase::SqlDatabase()
{
	m_pInstance = this;
	QString strDriver("QSQLITE");
	if ( QSqlDatabase::isDriverAvailable(strDriver) )
	{
		AddDataBase(strDriver,Conn_Name);
		SetDatabaseName(RAM_DB_NAME);
		SetUserName("");
		SetPassword("");
		if ( m_sqldb.isValid() )
		{
			bool bOpen = m_sqldb.open("","");
			if ( bOpen )
			{
				qDebug()<<"open equipment db!";
				if ( CreateTable("hero") )
				{
					qDebug()<<"create table hero!";
				}
#if TEST_ENABLED
				Test();
#endif
			}
			else
			{
				qDebug()<<"cannot open equipment db!";
				qDebug()<<m_sqldb.lastError();
			}
		}
	}
	else
	{
		qDebug()<<"drivers not contains:"<<strDriver;
	}
}

SqlDatabase::~SqlDatabase()
{
	m_pInstance = nullptr;
}

SqlDatabase* SqlDatabase::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		new SqlDatabase;
	}
	return m_pInstance;
}

void SqlDatabase::DeleteInstance()
{
	delete m_pInstance;
}

void SqlDatabase::SetDatabaseName(const QString& name)
{
#if RAM_ENABLED
	QDir dbdir;
	bool bMake = dbdir.mkpath(RAM_DB_DIR);
	m_sqldb.setDatabaseName(name);
#else
	m_sqldb.setDatabaseName("");
#endif
}

void SqlDatabase::SetUserName(const QString& name)
{
	m_sqldb.setUserName(name);
}

void SqlDatabase::SetPassword(const QString& password)
{
	m_sqldb.setPassword(password);
}

void SqlDatabase::AddDataBase(QSqlDriver* driver,const QString &connectionName)
{
	m_sqldb = QSqlDatabase::addDatabase(driver,connectionName);
}

void SqlDatabase::AddDataBase(QString & type,const QString &connectionName)
{
	m_sqldb = QSqlDatabase::addDatabase(type,connectionName);
}

bool SqlDatabase::CreateTable(const QString & name)
{
	bool bCreate = false;
	if ( m_tablelist.contains(name) )
	{
		qDebug()<<"exist table:"<<name;
	}
	else
	{
		bool bExistInDb = IsExistInDB(name);
		if ( !bExistInDb )
		{
			QString sqlCreate;
			if ( name.compare("hero")==0 )
			{
				sqlCreate = QString("CREATE TABLE hero ( \
									nHeroId int primary key not null,\
									nHeroType int,\
									nHeroCamp int,\
									ulBeginSecond int,\
									nStatus int,\
									strHeroName varchar(32));");
			}

			if ( name.compare("im")==0 )
			{
				sqlCreate = QString("CREATE TABLE im ( \
									node_id int primary key not null,\
									group_id int,\
									IsGroup bool,\
									total int,\
									online int,\
									state int,\
									strPathName varchar(128),\
									strGroupName varchar(32),\
									strName varchar(32));");
			}
			
			if ( m_sqldb.isValid() && m_sqldb.isOpen() )
			{
				QSqlQuery query(m_sqldb);
				QString strName = m_sqldb.databaseName();
				if ( !query.exec(sqlCreate) )
				{
					QString error =query.lastError().text();
					qDebug()<<"error:"<<query.lastError();
					qDebug()<<"create table hero failed:"<<sqlCreate;
				}
				bCreate = true;
				m_tablelist << name;
			}
		}
	}
	return bCreate;
}

bool SqlDatabase::IsExistInDB(const QString & tablename)
{
	bool bExist = false;
	QString sql = QString("select count(*) from sqlite_master where type='table' and name='%1';").arg(tablename);
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"select table exist false:"<<query.lastError()<<",sql:"<<sql;
		}
		else
		{
			while (query.next())
			{
				bExist = query.value(0).toInt() == 0 ? false : true; 
			}
		}
	}
	return bExist;
}

void SqlDatabase::InsertItem(const QString & sql)
{
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"insert failed:"<<sql;
			QString error =query.lastError().text();
			qDebug()<<"error:"<<query.lastError();
		}
	}
}

bool SqlDatabase::IsHeroItemExist(int id)
{
	bool bExist = false;

	QSqlQuery query(m_sqldb);
	QString sql = QString("select count(*) from hero where nHeroId = %1 ;").arg(id);
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

bool SqlDatabase::IsItemExist(const QString & sql)
{
	bool bExist = false;
	QSqlQuery query(m_sqldb);
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

void SqlDatabase::InsertHero(const STHero & stHero)
{
	QString sqlFormat = QString("insert into hero values(%1,%2,%3,%4,%5,'%6');");
	QString sql = sqlFormat.arg(stHero.nHeroId).arg(stHero.nHeroType).arg(stHero.nHeroCamp).arg(stHero.ulBeginSecond).arg(stHero.nStatus).arg(QString::fromWCharArray(stHero.strHeroName));
	InsertItem(sql);
}

void SqlDatabase::InsertVecItem(const QVector<STHero> & vec)
{
	//事务插入数据
	if ( IsExistInDB("hero") )
	{
		if ( m_sqldb.transaction() )
		{
			for ( int nIndex = 0 ; nIndex < vec.size() ; ++nIndex )
			{
				STHero stHero;
				stHero= vec[nIndex];
				if ( !IsHeroItemExist(stHero.nHeroId) )
				{
					InsertHero(stHero);
				}
				else
				{
					UpdateHero(stHero);
				}
			}
			if ( !m_sqldb.commit() )
			{
				qDebug()<<m_sqldb.lastError();
				if ( !m_sqldb.rollback() )
				{
					qDebug()<<m_sqldb.lastError();
				}
			}
		}
	}
}

void SqlDatabase::UpdateBeginSecond(const QVector<STHero> & vec)
{
	//事务插入数据
	if ( IsExistInDB("hero") )
	{
		if ( m_sqldb.transaction() )
		{
			for ( int nIndex = 0 ; nIndex < vec.size() ; ++nIndex )
			{
				STHero stHero;
				stHero= vec[nIndex];
				if ( IsHeroItemExist(stHero.nHeroId) )
				{
					UpdateHeroBeginSecond(stHero);
				}
				/*else
				{
					InsertHeroBeginSecond(stHero);
				}*/
			}
			if ( !m_sqldb.commit() )
			{
				qDebug()<<m_sqldb.lastError();
				if ( !m_sqldb.rollback() )
				{
					qDebug()<<m_sqldb.lastError();
				}
			}
		}
	}
}

void SqlDatabase::UpdateHeroBeginSecond(const STHero & stHero)
{
	QString sqlFormat = QString("update hero set ulBeginSecond=%1 where nHeroId = %2;");
	QString sqlUpdate= sqlFormat.arg(stHero.ulBeginSecond).arg(stHero.nHeroId);
	UpdateItem(sqlUpdate);
}

void SqlDatabase::UpdateHeroBeginSecond(const int & BeginSecond)
{
	////LOG_FUN("");
	QString sqlUpdate;
	if ( BeginSecond == 0 )
	{
		sqlUpdate = QString("update hero set ulBeginSecond=0 ;");
	}
	else
	{
		sqlUpdate = QString("update hero set ulBeginSecond=0 where ulBeginSecond = %1;").arg(BeginSecond);
	}
	////LOG_INFO("update begin second"<<sqlUpdate.toLocal8Bit().data());
	UpdateItem(sqlUpdate);
}

void SqlDatabase::UpdateHero(const STHero & stHero )
{
	QString sqlFormat = QString("update hero set nHeroType=%1,strHeroName='%2',nHeroCamp=%4 ,ulBeginSecond=%5,nStatus=%6 where nHeroId = %3;");
	QString sqlUpdate= sqlFormat.arg(stHero.nHeroType).arg(QString::fromWCharArray(stHero.strHeroName)).arg(stHero.nHeroId).arg(stHero.nHeroCamp).arg(stHero.ulBeginSecond).arg(stHero.nStatus);
	UpdateItem(sqlUpdate);
}

void SqlDatabase::UpdateHeroStatus(const STHero & stHero)
{
	QString sqlUpdate= QString("update hero set nStatus=%1 where nHeroId=%2;").arg(stHero.nStatus).arg(stHero.nHeroId);
	UpdateItem(sqlUpdate);
}

void SqlDatabase::InsertHeroBeginSecond(const STHero & stHero)
{
	QString sqlFormat = QString("insert into hero values(%1,%2,%3,%4,%5,'%6');");
	QString sql = sqlFormat.arg(stHero.nHeroId).arg(stHero.nHeroType).arg(stHero.nHeroCamp).arg(stHero.ulBeginSecond).arg(stHero.nStatus).arg(QString::fromWCharArray(stHero.strHeroName));
	InsertItem(sql);
}

void SqlDatabase::UpdateItem(const QString & sql)
{
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"update failed:"<<sql;
			QString error =query.lastError().text();
			qDebug()<<"error:"<<query.lastError();
		}
	}
}

void SqlDatabase::DeleteItem(const QString & sql)
{
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"delete failed:"<<sql;
			QString error =query.lastError().text();
			qDebug()<<"error:"<<query.lastError();
		}
	}
}

void SqlDatabase::ClearHeroTable()
{
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		if ( IsExistInDB("hero") )
		{
			QString sql = QString("delete  from hero;");
			QSqlQuery query(m_sqldb);
			if ( !query.exec(sql) )
			{
				qDebug()<<"delete failed:"<<sql;
				QString error =query.lastError().text();
				qDebug()<<"error:"<<query.lastError();
			}
		}
		
	}
}

void SqlDatabase::execSql(const QString & sql)
{
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"execSql failed:"<<sql;
			QString error =query.lastError().text();
			qDebug()<<"error:"<<query.lastError();
		}
	}
}

void SqlDatabase::DeleteItem(const STHero & stHero)
{
	QString strFormat = QString("delete from qw where id = %1;");
	QString sql = strFormat.arg(stHero.nHeroId);
	DeleteItem(sql);
}

QVector<QVariant> SqlDatabase::selectHero(const QString & sql)
{
	////LOG_FUN("sql:"<<sql.toStdWString());
	QVector<QVariant> vec;
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"select failed:"<<sql;
			qDebug()<<"LASTERROR:"<<query.lastError();
		}
		else
		{
			while(query.next())
			{
				QVariant v;
				STHero stHero;
				stHero.nHeroId  = query.value("nHeroId").toInt();
				stHero.nHeroType  = query.value("nHeroType").toInt();
				stHero.nHeroCamp = query.value("nHeroCamp").toInt();
				stHero.ulBeginSecond = query.value("ulBeginSecond").toInt();
				stHero.nStatus = query.value("nStatus").toInt();
				wcscpy_s(stHero.strHeroName , query.value("strHeroName").toString().toStdWString().c_str());
				////LOG_INFO("hero id:"<<stHero.nHeroId<<",ulBeginSecond:"<<stHero.ulBeginSecond);
				v.setValue(stHero);
				vec.push_back(v);
			}
		}
	}
	return vec;
}

QVector<STNode> SqlDatabase::SelectNode(const QString & sql)
{
	QVector<STNode> vec;
	if ( m_sqldb.isValid() && m_sqldb.isOpen() )
	{
		QSqlQuery query(m_sqldb);
		if ( !query.exec(sql) )
		{
			qDebug()<<"select failed:"<<sql;
			qDebug()<<"LASTERROR:"<<query.lastError();
		}
		else
		{
			while(query.next())
			{
				int group_id;
				bool IsGroup;
				int node_id;
				std::wstring strGroupName;
				std::wstring strName;
				std::wstring strPath;
				int total;
				int online;

				STNode stNode;
				stNode.group_id  = query.value("group_id").toInt();
				stNode.node_id  = query.value("node_id").toInt();
				stNode.IsGroup = query.value("IsGroup").toBool();
				stNode.total = query.value("total").toInt();
				stNode.online = query.value("online").toInt();
				stNode.strPath = query.value("strPath").toString().toStdWString();
				stNode.strGroupName = query.value("strGroupName").toString().toStdWString();
				stNode.strName = query.value("strName").toString().toStdWString();
				vec.push_back(stNode);
			}
		}
	}
	return vec;
}

void SqlDatabase::TestHero()
{
	if ( IsExistInDB("hero") )
	{
		QVector<STHero> vecHero;
		for ( int i = 0 ; i < 44 ; ++i )
		{
			STHero stHero;
			stHero.nHeroId = 10001+i;
			stHero.nHeroType = i%6+1;
			stHero.nHeroCamp = i%3+1;
			wcscpy(stHero.strHeroName,L"英雄英雄");
			vecHero.push_back(stHero);
		}

		InsertVecItem(vecHero);

		//名称区分以便过滤条件
		QString sql = QString("update hero set strHeroName= case  when nHeroId < 10010 then 'hero' when nHeroId < 10020 and nHeroId > 10010 then 'hero10020'  else 'hero10030' end;");
		execSql(sql);
	}
}

void SqlDatabase::TestIm()
{
	if ( IsExistInDB("Im") )
	{

	}
}