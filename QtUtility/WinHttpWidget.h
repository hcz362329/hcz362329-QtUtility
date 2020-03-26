#ifndef WinHttpWidget_h
#define WinHttpWidget_h
#include <QWidget>
class WinHttpWidget : public QWidget
{
	Q_OBJECT
public:
	WinHttpWidget(QWidget* parent=0);
	~WinHttpWidget();
};

#endif