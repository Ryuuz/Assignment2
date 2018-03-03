#-------------------------------------------------
#
# Project created by QtCreator 2018-02-22T18:23:09
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Assignment2
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    renderwindow.cpp \
    shader.cpp \
    sceneobject.cpp \
    vertex.cpp \
    axis.cpp \
    objectinstance.cpp \
    camera.cpp \
    plane.cpp \
    sphere.cpp \
    physicsobject.cpp \
    boundingvolume.cpp \
    collision.cpp \
    cube.cpp \
    triggervolume.cpp \
    transform.cpp \
    texture.cpp

HEADERS += \
        mainwindow.h \
    renderwindow.h \
    shader.h \
    sceneobject.h \
    vertex.h \
    axis.h \
    objectinstance.h \
    camera.h \
    plane.h \
    sphere.h \
    physicsobject.h \
    boundingvolume.h \
    collision.h \
    cube.h \
    triggervolume.h \
    transform.h \
    texture.h \
    constants.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    fragmentshader.frag \
    vertexshader.vert \
    textureshader.vert \
    textureshader.frag

RESOURCES += \
    assets.qrc
