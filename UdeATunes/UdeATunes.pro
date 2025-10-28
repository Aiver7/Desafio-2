TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT -= gui

SOURCES += \
        Aleatorio.cpp \
        CargasCancionAnuncio.cpp \
        CargasUsuarios.cpp \
        ClasePrincipal.cpp \
        ColaReproduccion.cpp \
        Favoritos.cpp \
        IReproducible.cpp \
        main.cpp

HEADERS += \
    Album.h \
    Aleatorio.h \
    Anuncio.h \
    Artista.h \
    Cancion.h \
    CargasCancionAnuncio.h \
    CargasUsuarios.h \
    ClasePrincipal.h \
    ColaReproduccion.h \
    ConstruirCola.h \
    Favoritos.h \
    GestorPublicidad.h \
    IReproducible.h \
    Medidor.h \
    Usuario.h
