TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(./MinGL2/mingl.pri)

SOURCES += \
    button.cpp \
    entity.cpp \
    fpslimiter.cpp \
    game.cpp \
    main.cpp

HEADERS += \
    button.h \
    entity.h \
    fpslimiter.h \
    game.h
