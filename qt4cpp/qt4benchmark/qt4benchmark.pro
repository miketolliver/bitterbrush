# Add more folders to ship with the application, here
folder_01.source = qml/qt4benchmark
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    datastore/DataStore.cpp \


HEADERS += \
    datastore/Src/DataStore.h \
    datastore/DataStoreSchema.h \
    datastore/IDataStore.h \
    Result.h



# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick1applicationviewer/qtquick1applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    bar-descriptor.xml
