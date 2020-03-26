#ifndef ExcelOperate_h
#define ExcelOperate_h
#include <QWidget>
#include <QAxObject>
class ExcelOperate : public QWidget
{
	Q_OBJECT
public:
	explicit ExcelOperate(QWidget* parent = 0);
	~ExcelOperate();
};
#endif