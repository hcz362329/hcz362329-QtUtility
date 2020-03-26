#include "ExcelOperate.h"
#include <QAxObject>
#include <QDir>
#include<QSqlDatabase>
#include <QStandardPaths>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>
#include <Windows.h>
#include <QDebug>
ExcelOperate::ExcelOperate(QWidget* parent )
	:QWidget(parent)
{
#if 1
	QString strFile = QFileDialog::getOpenFileName(NULL,QString::fromWCharArray(L"选择Excel配置文件"),".",tr("Exel file(*.xls *.xlsx)"));
	QAxObject *excel = NULL;    //本例中，excel设定为Excel文件的操作对象
	QAxObject *workbooks = NULL;
	QAxObject *workbook = NULL;  //Excel操作对象
	excel = new QAxObject("Excel.Application");
	excel->dynamicCall("SetVisible(bool)", true); //true 表示操作文件时可见，false表示为不可见
	workbooks = excel->querySubObject("WorkBooks");


	//————————————————按文件路径打开文件————————————————————
	workbook = workbooks->querySubObject("Open(QString&)", strFile);
	// 获取打开的excel文件中所有的工作sheet
	QAxObject * worksheets = workbook->querySubObject("WorkSheets");


	//—————————————————Excel文件中表的个数:——————————————————
	int iWorkSheet = worksheets->property("Count").toInt();
	qDebug() << QString("Excel文件中表的个数: %1").arg(QString::number(iWorkSheet));


	// ————————————————获取第n个工作表 querySubObject("Item(int)", n);——————————
	QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//本例获取第一个，最后参数填1


	//—————————获取该sheet的数据范围（可以理解为有数据的矩形区域）————
	QAxObject * usedrange = worksheet->querySubObject("UsedRange");

	//———————————————————获取行数———————————————
	QAxObject * rows = usedrange->querySubObject("Rows");
	int iRows = rows->property("Count").toInt();
	qDebug() << QString("行数为: %1").arg(QString::number(iRows));

	//————————————获取列数—————————
	QAxObject * columns = usedrange->querySubObject("Columns");
	int iColumns = columns->property("Count").toInt();
	qDebug() << QString("列数为: %1").arg(QString::number(iColumns));

	//————————数据的起始行———
	int iStartRow = rows->property("Row").toInt();
	qDebug() << QString("起始行为: %1").arg(QString::number(iStartRow));

	//————————数据的起始列————————————
	int iColumn = columns->property("Column").toInt();
	qDebug() << QString("起始列为: %1").arg(QString::number(iColumn));


	//——————————————读出数据—————————————
	//获取第i行第j列的数据
	//假如是第6行，第6列 对应表中F列6行，即F6
	QAxObject *range1 = worksheet->querySubObject("Range(QString)", "F6");
	QString strRow6Col6 = "";
	strRow6Col6 = range1->property("Value").toString();
	qDebug() << "第6行，第6列的数据为：" + strRow6Col6;

#else

	QString strFile1 = QFileDialog::getExistingDirectory(NULL,QString::fromWCharArray(L"选择文件保存的路径"));
	QString strFile = QFileDialog::getOpenFileName(NULL,QString::fromWCharArray(L"选择Excel配置文件"),".",tr("Exel file(*.xls *.xlsx)"));
	if (strFile.isEmpty())
	{
		QMessageBox::about(this, QString::fromWCharArray(L"提示"), QString::fromWCharArray(L"获取配置文件失败，请重试"));
		return;
	}    
	//使用ODBC获取
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelexport");
	if(!db.isValid())
	{
		QMessageBox::about(this, QString::fromWCharArray(L"提示"), QString::fromWCharArray(L"获取数据库失败，请重试\nerror:"));
		return;
	}
	QString dsn="Driver={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};Readonly=TRUE;DBQ="+strFile+ ";";
	db.setDatabaseName(dsn);
	if(!db.open())
	{
		QString strInfo = db.lastError().text();
		QMessageBox::about(this,QString::fromWCharArray(L"提示"), QString::fromWCharArray(L"数据库打开失败，请重试\nerror:")+strInfo);
		return;
	}

	QSqlQuery query(db);
	query.exec("select * from [Sheet1$]");
	while (query.next())
	{
		int index = query.value(0).toInt();//这里的0指的是在表格中的第一列
	}

	db.close();
#endif
}

ExcelOperate::~ExcelOperate()
{

}