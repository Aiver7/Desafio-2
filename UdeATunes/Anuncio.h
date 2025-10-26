#ifndef ANUNCIO_H
#define ANUNCIO_H
#include <QString>

class Anuncio {
public:
    qint64 id{0};
    QString mensaje;
    int duracionSeg{0};
    int peso{1};
};
#endif
