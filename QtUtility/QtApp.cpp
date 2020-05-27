#include "QtApp.h"

#include <QDebug>
#include <QFontDatabase>
QtUtilityApp::QtUtilityApp(int argc, char* argv[])
	:QApplication(argc, argv) {
	/*QFontDatabase fontDB;
	int n3 = fontDB.addApplicationFont(":/fonts/Resources/font/EmojiOneColor-SVGinOT.ttf");
	QStringList strList3 = QFontDatabase::applicationFontFamilies(n3);
	setFont(QFont("EmojiOne Color"));
	fontDB.addApplicationFont(":/res/Resources/font/seguisym.ttf");*/
	
}

QtUtilityApp::~QtUtilityApp() {

}

bool QtUtilityApp::notify(QObject* reciever, QEvent* event) {
	if (!event->type() == QEvent::MouseMove && 
		event->type() == QEvent::Enter && 
		event->type() == QEvent::Leave) {
		QEvent::Type t = event->type();
	}
	QEvent::Type t = event->type();
	Qt::ApplicationState st = this->applicationState();
	/*qDebug() << "T:" << t;*/
	return QApplication::notify(reciever, event);
}