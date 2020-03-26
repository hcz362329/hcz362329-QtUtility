

#include <QWidget>
#include "BaseAction.h"
class Font : public QWidget , public BaseAction
{
	Q_OBJECT
public:
	Font(QWidget* parent = 0);
	~Font();

public:
	//next functions are base actions 

	virtual void InitConnections() ;
	
	virtual void InitStyleSheets() ;
	
	virtual void LoadTranslator()  ;
	
	virtual void InitModules();
	
	virtual void InitPixmap() ;
	
	virtual void InitCtrls() ;
	
	virtual void InitWindowFlags() ;
public:
	void LoadStyleSheet(const QString & file_name);
};