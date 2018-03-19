#-------------------------------------------------
#
# Project created by QtCreator 2018-03-03T23:22:33
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
    axis.cpp \
    boundingvolume.cpp \
    camera.cpp \
    collision.cpp \
    cube.cpp \
    objectinstance.cpp \
    physicsobject.cpp \
    plane.cpp \
    renderwindow.cpp \
    sceneobject.cpp \
    shader.cpp \
    sphere.cpp \
    texture.cpp \
    transform.cpp \
    triggervolume.cpp \
    vertex.cpp \
    door.cpp \
    ball.cpp

HEADERS += \
        mainwindow.h \
    axis.h \
    boundingvolume.h \
    camera.h \
    collision.h \
    constants.h \
    cube.h \
    objectinstance.h \
    physicsobject.h \
    plane.h \
    renderwindow.h \
    sceneobject.h \
    shader.h \
    sphere.h \
    texture.h \
    transform.h \
    triggervolume.h \
    vertex.h \
    door.h \
    ball.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    fragmentshader.frag \
    textureshader.frag \
    textureshader.vert \
    vertexshader.vert
