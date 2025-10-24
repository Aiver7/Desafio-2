#ifndef ARTISTA_H
#define ARTISTA_H
#include <QString>

class Artista {
public:
    qint64 idArtista{0};
    QString nombre;
    QString pais;
    int edad{0}, seguidores{0}, ranking{0};
};
#endif
