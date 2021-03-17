#include <QApplication>
#include <QScreen>

#include "screenshot.h"
#include "options.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Options options;
    //options.show();

    Screenshot screenshot;
    screenshot.setOptions(&options);
    //screenshot.move(screenshot.screen()->availableGeometry().topLeft() + QPoint(20, 20));
    //screenshot.showFullScreen();
    //screenshot.hide();
    
   
    auto hotkey = new QHotkey(QKeySequence("ctrl+shift+L"), true, &app);//The hotkey will be automatically registered
	qDebug() << "Hotkey is Registered: " << hotkey->isRegistered();

	QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
		//qDebug() << "Hotkey Activated - the application will quit now";
		//qApp->quit();
		//Screenshot* screenshot = new Screenshot();
		screenshot.takeNewScreenshot();
	});

    return app.exec();
}
