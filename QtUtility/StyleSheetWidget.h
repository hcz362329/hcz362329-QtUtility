#ifndef StyleSheetWidget_h
#define StyleSheetWidget_h
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
class StyleSheetWidget : public QWidget {
	Q_OBJECT
public:
	StyleSheetWidget(QWidget* parent);
	~StyleSheetWidget();
public slots:
	void btn2clicked();
private:
	QTextEdit* pText;
	QPushButton* pBtn1;
	QLabel* pBtn2;
	QProgressBar* progress;
};
#endif // !StyleSheetWidget_h

