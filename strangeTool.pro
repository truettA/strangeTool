QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

unix {
# message("unxi")
}

macx{
#set opencv
#U_OPENCV_INCLUDE_DIR = /usr/local/Cellar/opencv/4.5.4_3/include/opencv4
#U_OPENCV_LIBRARY_DIR = /usr/local/Cellar/opencv/4.5.4_3/lib
#INCLUDEPATH += $${U_OPENCV_INCLUDE_DIR}
#PKG_CONFIG_PATH += /usr/local/Cellar/opencv/4.5.4_3/lib/pkgconfig
#QT_CONFIG -= no-pkg-config
#PKG_CONFIG_PATH = /usr/local/Cellar/opencv/4.5.4_3/lib/pkgconfig

PKG_CONFIG = /usr/local/bin/pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv4
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainWidget.cpp \
    rwfile.cpp \
    yolodetect.cpp \
    yolotool.cpp

HEADERS += \
    mainWidget.h \
    rwfile.h \
    yolodetect.h \
    yolotool.h

FORMS += \
    mainWidget.ui \
    yolotool.ui

TRANSLATIONS += \
    strangeTool_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
