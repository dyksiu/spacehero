TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        asteroid.cpp \
        boost.cpp \
        boss.cpp \
        main.cpp \
        przycisk.cpp \
        shot.cpp \
        spaceship.cpp \
        ufo.cpp

HEADERS += \
    AnimowaneObiekty.h \
    StatyczneObiekty.h \
    asteroid.h \
    boost.h \
    boss.h \
    funkcje.h \
    okna.h \
    przycisk.h \
    shot.h \
    spaceship.h \
    ufo.h
