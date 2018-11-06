#-------------------------------------------------
#
# Project created by QtCreator 2018-10-23T19:43:06
#
#-------------------------------------------------

QT       += core gui websockets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LCARS_Remote_Control
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        lcars_button.cpp \
    lcars_line.cpp \
    lcars_roundededgeconnector.cpp \
    process_data.cpp

HEADERS += \
        mainwindow.h \
    lcars_button.h \
    lcars_line.h \
    lcars_roundededgeconnector.h \
    process_data.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lcars_button.json \
    lcars_line.json \
    LCARS_EXTRA_GLYPHS.ttf \
    DroidSansMono.ttf \
    Helvetica_Ultra_Compressed.ttf \
    webdings.ttf \
    android-sources/AndroidManifest.xml \
    ../qt-lcars_widgets/LCARS_RoundedEdgeConnector/lcars_roundededgeconnector.json \
    lcars_roundededgeconnector.json

RESOURCES += \
    resources.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources


