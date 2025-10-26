#ifndef CANCION_H
#define CANCION_H
#include <QString>

class Cancion {
public:
    qint64 id{0};
    QString titulo;
    QString path128;
    QString path320;
    QString coverPng;
    int duracionSeg{0};
    qint64 albumId{0};
};
#endif
