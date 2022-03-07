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
OPENCV_INCLUDE_DIR = F:/OpenCV/build_minGW/install/include

OPENCV_LIBRARY_LIB_DIR = F:/OpenCV/build_minGW/install/x64/mingw/bin
OPENCV_LIBRARY_LIB = $${OPENCV_LIBRARY_LIB_DIR}/libopencv_core455.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_dnn455.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_highgui455.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_imgproc455.dll\
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_video455.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_videoio455.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_photo455.dll \

OPENCV_LIBRARY_LIB_d = $${OPENCV_LIBRARY_LIB_DIR}/libopencv_core455d.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_dnn455d.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_highgui455d.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_imgproc455d.dll\
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_video455d.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_videoio455d.dll \
                     $${OPENCV_LIBRARY_LIB_DIR}/libopencv_photo455d.dll \


INCLUDEPATH += $${OPENCV_INCLUDE_DIR}

CONFIG(debug,debug|release):LIBS          += $${OPENCV_LIBRARY_LIB_d}
CONFIG(release,debug|release):LIBS        += $${OPENCV_LIBRARY_LIB}
}

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
