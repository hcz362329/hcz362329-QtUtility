#ifndef MUSIC_H
#define MUSIC_H

#include <QtWidgets/QWidget>

class music : public QWidget
{
	Q_OBJECT

public:
	music(QWidget *parent = 0);
	~music();
public slots:
	void OnTypeActivated(int index);
	void OnTypeHighLighted(int index);
private:
	
};

#endif // MYCLASS_H
