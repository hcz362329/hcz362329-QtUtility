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
	QString strFile = QFileDialog::getOpenFileName(NULL,QString::fromWCharArray(L"ѡ��Excel�����ļ�"),".",tr("Exel file(*.xls *.xlsx)"));
	QAxObject *excel = NULL;    //�����У�excel�趨ΪExcel�ļ��Ĳ�������
	QAxObject *workbooks = NULL;
	QAxObject *workbook = NULL;  //Excel��������
	excel = new QAxObject("Excel.Application");
	excel->dynamicCall("SetVisible(bool)", true); //true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
	workbooks = excel->querySubObject("WorkBooks");


	//�����������������������������������ļ�·�����ļ�����������������������������������������
	workbook = workbooks->querySubObject("Open(QString&)", strFile);
	// ��ȡ�򿪵�excel�ļ������еĹ���sheet
	QAxObject * worksheets = workbook->querySubObject("WorkSheets");


	//����������������������������������Excel�ļ��б�ĸ���:������������������������������������
	int iWorkSheet = worksheets->property("Count").toInt();
	qDebug() << QString("Excel�ļ��б�ĸ���: %1").arg(QString::number(iWorkSheet));


	// ����������������������������������ȡ��n�������� querySubObject("Item(int)", n);��������������������
	QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//������ȡ��һ������������1


	//��������������������ȡ��sheet�����ݷ�Χ���������Ϊ�����ݵľ������򣩡�������
	QAxObject * usedrange = worksheet->querySubObject("UsedRange");

	//����������������������������������������ȡ����������������������������������
	QAxObject * rows = usedrange->querySubObject("Rows");
	int iRows = rows->property("Count").toInt();
	qDebug() << QString("����Ϊ: %1").arg(QString::number(iRows));

	//��������������������������ȡ����������������������
	QAxObject * columns = usedrange->querySubObject("Columns");
	int iColumns = columns->property("Count").toInt();
	qDebug() << QString("����Ϊ: %1").arg(QString::number(iColumns));

	//�������������������ݵ���ʼ�С�����
	int iStartRow = rows->property("Row").toInt();
	qDebug() << QString("��ʼ��Ϊ: %1").arg(QString::number(iStartRow));

	//�������������������ݵ���ʼ�С�����������������������
	int iColumn = columns->property("Column").toInt();
	qDebug() << QString("��ʼ��Ϊ: %1").arg(QString::number(iColumn));


	//�����������������������������������ݡ�������������������������
	//��ȡ��i�е�j�е�����
	//�����ǵ�6�У���6�� ��Ӧ����F��6�У���F6
	QAxObject *range1 = worksheet->querySubObject("Range(QString)", "F6");
	QString strRow6Col6 = "";
	strRow6Col6 = range1->property("Value").toString();
	qDebug() << "��6�У���6�е�����Ϊ��" + strRow6Col6;

#else

	QString strFile1 = QFileDialog::getExistingDirectory(NULL,QString::fromWCharArray(L"ѡ���ļ������·��"));
	QString strFile = QFileDialog::getOpenFileName(NULL,QString::fromWCharArray(L"ѡ��Excel�����ļ�"),".",tr("Exel file(*.xls *.xlsx)"));
	if (strFile.isEmpty())
	{
		QMessageBox::about(this, QString::fromWCharArray(L"��ʾ"), QString::fromWCharArray(L"��ȡ�����ļ�ʧ�ܣ�������"));
		return;
	}    
	//ʹ��ODBC��ȡ
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelexport");
	if(!db.isValid())
	{
		QMessageBox::about(this, QString::fromWCharArray(L"��ʾ"), QString::fromWCharArray(L"��ȡ���ݿ�ʧ�ܣ�������\nerror:"));
		return;
	}
	QString dsn="Driver={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};Readonly=TRUE;DBQ="+strFile+ ";";
	db.setDatabaseName(dsn);
	if(!db.open())
	{
		QString strInfo = db.lastError().text();
		QMessageBox::about(this,QString::fromWCharArray(L"��ʾ"), QString::fromWCharArray(L"���ݿ��ʧ�ܣ�������\nerror:")+strInfo);
		return;
	}

	QSqlQuery query(db);
	query.exec("select * from [Sheet1$]");
	while (query.next())
	{
		int index = query.value(0).toInt();//�����0ָ�����ڱ���еĵ�һ��
	}

	db.close();
#endif
}

ExcelOperate::~ExcelOperate()
{

}