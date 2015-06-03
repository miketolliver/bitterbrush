#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QDeclarativeContext>
#include <QFontDatabase>
#include "WipeLogic.h"

using namespace mblsft;
using namespace mblsft::wipe;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if defined(Q_OS_QNX)

#elif defined(Q_OS_ANDROID)

#endif

    QFontDatabase fontDatabase;
    int id = fontDatabase.addApplicationFont(":/fonts/SlatePro.ttf");
    id = fontDatabase.addApplicationFont(":/fonts/SlatePro-Bold.ttf");
    if( id >= 0 ){
        QStringList fontList = fontDatabase.applicationFontFamilies( id );
        QFont lTheFont( fontList.at(0) );
        lTheFont.setStyleStrategy( QFont::PreferAntialias );
        QGuiApplication::setFont(lTheFont);
        qDebug("Successfully loaded SlatePro font.");
    }else{
        qDebug("Unable to load SlatePro font.");
        //font couldn't be loaded, just keep the defaults
    }


    WipeLogic* mWL = new WipeLogic();

    QtQuick1ApplicationViewer viewer;

    QDeclarativeContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("wipeLogic", mWL);
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:/qml/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
