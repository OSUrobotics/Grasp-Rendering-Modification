
QT       += core gui opengl

TARGET = 07-core-profile
TEMPLATE = app

SOURCES +=  \
            main.cpp \
            glwidget.cpp

HEADERS  += \
            glwidget.h \
    objloader.hpp

OTHER_FILES +=  \
                simple.vert \
                simple.frag \
                suzanne.obj \
    blue_yellow_gradient.bmp

unix:!macx: LIBS += -lX11 -ldl -lXxf86vm -lGLEW -lXrandr -lXcursor -lXinerama
