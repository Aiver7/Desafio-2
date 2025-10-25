#include "IReproducible.h"
#include <QString>


class Cancion {
public:
    qint64 id{0}; int duracionSeg{0};
    QString titulo, path128, path320, coverPng;
};
class Anuncio {
public:
    qint64 id{0}; int duracionSeg{0};
    QString mensaje; int peso{1};
};

// Implementaciones asociadas a IReproducible
int ir_duracion(const IReproducible& r){
    return r.esCancion() ? r.cancion->duracionSeg
                         : (r.esAnuncio() ? r.anuncio->duracionSeg : 0);
}
QString ir_titulo(const IReproducible& r){
    return r.esCancion() ? r.cancion->titulo
                         : (r.esAnuncio() ? QStringLiteral("[AD] ") + r.anuncio->mensaje
                                          : QString());
}
QString ir_audioPath(const IReproducible& r, bool premium){
    return r.esCancion() ? (premium ? r.cancion->path320 : r.cancion->path128)
                         : QString();
}
QString ir_cover(const IReproducible& r){
    return r.esCancion() ? r.cancion->coverPng : QString();
}
