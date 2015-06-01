#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QDeclarativeContext>
#include "WipeLogic.h"

using namespace mblsft;
using namespace mblsft::wipe;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if defined(Q_OS_QNX)

#elif defined(Q_OS_ANDROID)

#endif


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
