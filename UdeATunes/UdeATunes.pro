TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT -= gui

SOURCES += \
        ColaReproduccion.cpp \
        IReproducible.cpp \
        Loaders.cpp \
        main.cpp

HEADERS += \
    Album.h \
    Anuncio.h \
    Artista.h \
    Cancion.h \
    ClasePrincipal.h \
    ColaReproduccion.h \
    IReproducible.h \
    Loaders.h \
    Usuario.h
