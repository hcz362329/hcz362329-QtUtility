#ifndef QtApp
#define QtApp
#include <windows.h>
#include <QObject>
#include <QApplication>

class QtUtilityApp : public QApplication {
	Q_OBJECT
public:
	QtUtilityApp(int argc, char* argv[]);
	~QtUtilityApp() noexcept;
protected:
	virtual bool notify(QObject* reciever, QEvent* event) Q_DECL_OVERRIDE;
};

#endif // !QtApp
