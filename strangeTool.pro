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

win32{
OPENCV_INCLUDE_DIR = I:/opencv/build/include
OPENCV_LIBRARY_LIB = I:/OpenCV/opencv/build/x64/vc15/bin/opencv_world455.dll
OPENCV_LIBRARY_LIB_d = I:/opencv/opencv-build/bin/libopencv_calib3d430.dll \
                       I:/opencv/opencv-build/bin/libopencv_core430.dll \
                       I:/opencv/opencv-build/bin/libopencv_highgui430.dll \
                       I:/opencv/opencv-build/bin/libopencv_imgcodecs430.dll \
                       I:/opencv/opencv-build/bin/libopencv_imgproc430.dll \
                       I:/opencv/opencv-build/bin/libopencv_objdetect430.dll

INCLUDEPATH += $${OPENCV_INCLUDE_DIR}

CONFIG(debug,debug|release):LIBS        += $${OPENCV_LIBRARY_LIB_d}
CONFIG(release,debug|release):LIBS        += $${OPENCV_LIBRARY_LIB}
}
message($${LIBS})
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawimg.cpp \
    main.cpp \
    mainWidget.cpp \
    rwfile.cpp \
    updataui.cpp \
    yolodetect.cpp \
    yolotool.cpp

HEADERS += \
    drawimg.h \
    mainWidget.h \
    rwfile.h \
    updataui.h \
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
