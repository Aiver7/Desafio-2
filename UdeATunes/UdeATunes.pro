TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT -= gui

SOURCES += \
        main.cpp

HEADERS += \
    Album.h \
    Anuncio.h \
    Cancion.h \
    ClasePrincipal.h \
    IReproducible.h \
    Usuario.h
