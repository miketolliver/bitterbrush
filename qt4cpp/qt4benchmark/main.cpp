#include "qtquick1applicationviewer.h"
#include "benchdataio.h"

#include <QApplication>
#include <QDeclarativeContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BenchDataIO *lBench = new BenchDataIO();
    QtQuick1ApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);

    viewer.rootContext()->setContextProperty("benchData", lBench);
    lBench->Initialize();

    viewer.setMainQmlFile(QLatin1String("qml/qt4benchmark/main.qml"));
    viewer.showExpanded();


    return app.exec();
}
