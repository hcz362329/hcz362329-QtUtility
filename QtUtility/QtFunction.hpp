#ifndef QtFunction_h
#define QtFunction_h
#include <QFile>
#include <Windows.h>
namespace QtFunction
{
	static QString GetStyleSheetFromFile(const QString & file_name)
	{
		QString strStyleSheet=QString("default string");
		QFile file(file_name);
		if ( file.open(QIODevice::ReadOnly | QIODevice::Text ) )
		{
			strStyleSheet = file.readAll();
		}
		else
		{
			char szTip[MAX_PATH]={0};
			sprintf(szTip,"%s",file_name.toLocal8Bit());
			MessageBoxA(0,szTip,"file read",0);
		}
		return strStyleSheet;
	}
};

#endif