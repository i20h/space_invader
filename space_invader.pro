TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

include(./MinGL2/mingl.pri)

SOURCES += \
    bullet.cpp \
    button.cpp \
    entity.cpp \
    fpslimiter.cpp \
    game.cpp \
    invader.cpp \
    main.cpp \
    party.cpp \
    player.cpp

HEADERS += \
    bullet.h \
    button.h \
    entity.h \
    fpslimiter.h \
    game.h \
    invader.h \
    party.h \
    player.h
