# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    source/main.cpp \
    source/WipeLogic.cpp

RESOURCES += qml.qrc

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick1applicationviewer/qtquick1applicationviewer.pri)

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/main.qml \
    qml/Drawer.qml \
    qml/RemoteSettings.qml \
    qml/WipeDevice.qml \
    qml/WipeRemote.qml \
    qml/WipeDeviceConfirm.qml \
    qml/PlainButton.qml \
    qml/PlainIconTextButton.qml \
    qml/PlainIconButton.qml




android {
     ANDROID_PACKAGE_SOURCE_DIR = $$PWD/androidFiles

    OTHER_FILES += \
        $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml
}

HEADERS += \
    source/WipeLogic.h
