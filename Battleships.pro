#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T01:49:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = battleships
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    openglrender/openglrender.cpp \
    openglrender/openglobject.cpp \
    openglrender/openglpoint.cpp \
    openglrender/openglline.cpp \
    openglrender/openglcircle.cpp \
    openglrender/openglpolygon.cpp \
    openglrender/openglpolyedge.cpp \
    openglrender/openglellipse.cpp \
    openglrender/openglcycloids.cpp \
    openglrender/bucket.cpp \
    openglrender/edge.cpp \
    tutor/glm.cpp \
    openglrender/openglmesh.cpp \
    openglrender/openglcamera.cpp \
    openglrender/ship.cpp \
    openglrender/projectile.cpp \
    openglrender/barrier.cpp \
    openglrender/terrain.cpp \
    openglrender/boundingbox.cpp

HEADERS  += window.h \
    openglrender/openglrender.h \
    openglrender/openglobject.h \
    openglrender/openglpoint.h \
    openglrender/openglline.h \
    openglrender/openglcircle.h \
    openglrender/openglpolygon.h \
    openglrender/openglpolyedge.h \
    openglrender/openglellipse.h \
    openglrender/openglcycloids.h \
    openglrender/bucket.h \
    openglrender/edge.h \
    tutor/glm.h \
    openglrender/openglmesh.h \
    openglrender/openglcamera.h \
    openglrender/ship.h \
    openglrender/projectile.h \
    openglrender/barrier.h \
    openglrender/terrain.h \
    openglrender/boundingbox.h \
    openglrender/wingdi.h

FORMS    += window.ui
