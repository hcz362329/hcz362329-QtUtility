#ifndef AnimationResize_h
#define AnimationResize_h
#include <QDialog>
#include <QPropertyAnimation>
#include <QLabel>
class AnimationResize : public QDialog
{
	Q_OBJECT
public:
	AnimationResize(QWidget* parent=0);
	~AnimationResize();
private:
	QPropertyAnimation* m_pAnimation;
	QLabel* m_pExample;
};
#endif