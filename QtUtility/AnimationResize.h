#ifndef AnimationResize_h
#define AnimationResize_h
#include <QDialog>
#include <QPropertyAnimation>
#include <QLabel>
class QPushButton;
class AnimationResize : public QDialog
{
	Q_OBJECT
public:
	AnimationResize(QWidget* parent=0);
	~AnimationResize();
public slots:
void Test();
private:
	QPropertyAnimation* m_pAnimation;
	QPropertyAnimation* m_pAnimation2;
	QLabel* m_pExample;
	QPushButton* btn;
	QPushButton* btn2;
};
#endif