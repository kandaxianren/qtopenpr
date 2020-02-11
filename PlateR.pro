#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T14:17:19
#
#-------------------------------------------------

QT       += core gui \
          multimedia \
          multimediawidgets \
          sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlateR
TEMPLATE = app
#CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        dialog.cpp \
    thirdparty/LBP/helper.cpp \
    thirdparty/LBP/lbp.cpp \
    thirdparty/mser/mser2.cpp \
    thirdparty/textDetect/erfilter.cpp \
    thirdparty/xmlParser/xmlParser.cpp \
    chars_identify.cpp \
    chars_recognise.cpp \
    chars_segment.cpp \
    core_func.cpp \
    feature.cpp \
    kv.cpp \
    params.cpp \
    plate_detect.cpp \
    plate_judge.cpp \
    plate_locate.cpp \
    plate_recognize.cpp \
    util.cpp

HEADERS  += dialog.h \
    easypr/core/character.hpp \
    easypr/core/chars_identify.h \
    easypr/core/chars_recognise.h \
    easypr/core/chars_segment.h \
    easypr/core/core_func.h \
    easypr/core/feature.h \
    easypr/core/params.h \
    easypr/core/plate.hpp \
    easypr/core/plate_detect.h \
    easypr/core/plate_judge.h \
    easypr/core/plate_locate.h \
    easypr/core/plate_recognize.h \
    easypr/util/kv.h \
    easypr/util/program_options.h \
    easypr/util/switch.hpp \
    easypr/util/util.h \
    easypr/api.hpp \
    easypr/config.h \
    easypr/version.h \
    thirdparty/LBP/helper.hpp \
    thirdparty/LBP/lbp.hpp \
    thirdparty/mser/mser2.hpp \
    thirdparty/textDetect/erfilter.hpp \
    thirdparty/xmlParser/xmlParser.h \
    config.hpp \
    easypr.h

FORMS    += dialog.ui
#INCLUDEPATH += /usr/local/include \
#                /usr/local/include/opencv \
#               /usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_highgui.so.3.4 \
        /usr/local/lib/libopencv_core.so.3.4    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so.3.4 \
        /usr/local/lib/libopencv_ml.so.3.4 \
        /usr/local/lib/libopencv_objdetect.so.3.4 \
        /usr/local/lib/libopencv_calib3d.so.3.4 \
        /usr/local/lib/libopencv_dnn.so.3.4 \
        /usr/local/lib/libopencv_features2d.so.3.4 \
        /usr/local/lib/libopencv_flann.so.3.4 \
        /usr/local/lib/libopencv_photo.so.3.4 \
        /usr/local/lib/libopencv_shape.so.3.4 \
        /usr/local/lib/libopencv_stitching.so.3.4 \
        /usr/local/lib/libopencv_superres.so.3.4 \
        /usr/local/lib/libopencv_videoio.so.3.4 \
        /usr/local/lib/libopencv_video.so.3.4 \
        /usr/local/lib/libopencv_videostab.so.3.4

