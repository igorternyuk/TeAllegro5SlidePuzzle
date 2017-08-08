TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DEFINES -= DEBUG
SOURCES += main.cpp \
    tile.cpp \
    model.cpp \
    controller.cpp \
    view.cpp

HEADERS += \
    tile.h \
    model.h \
    controller.h \
    view.h \
    modellistener.h \
    constantmodelinterface.h \
    constants.h


LIBS += `pkg-config --libs allegro-5.0 allegro_dialog-5.0 allegro_ttf-5.0 allegro_font-5.0 allegro_primitives-5.0 allegro_image-5.0`

QMAKE_CXXFLAGS += -std=gnu++14
