QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../gifLib/src/gifimage/qtgifimage.pri)

SOURCES += \
    ../back/s21_parser.cc \
    ../controller/s21_controller.cc \
    main.cc \
    mainwindow.cc \
    modelviewer.cc \
    simpleobject3d.cc

HEADERS += \
    ../back/s21_parser.h \
    ../controller/s21_controller.h \
    mainwindow.h \
    modelviewer.h \
    simpleobject3d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    shaders.qrc
