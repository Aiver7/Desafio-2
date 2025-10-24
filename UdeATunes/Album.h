#ifndef ALBUM_H
#define ALBUM_H
#include <QString>

class Artista;

class Album {
public:
    qint64 idAlbum{0};
    QString titulo, coverPngPath;
    Artista* artistaPrincipal{nullptr};
    qint64 pistasIds[128];
    int pistasCount{0};
};
#endif
