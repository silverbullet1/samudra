#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T20:42:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SamudraGUIofficial
TEMPLATE = app


SOURCES += main.cpp\
            mainwindow.cpp \
            mat_and_qimage.cpp \
            trackbars.cpp \
    globals.cpp

HEADERS  += mainwindow.h \
            mat_and_qimage.hpp \
            trackbars.h \
    globals.h

FORMS       += mainwindow.ui \
            trackbars.ui

INCLUDEPATH += /usr/local/include/opencv

CONFIG += c++11

LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
  #-lboost_thread
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree

