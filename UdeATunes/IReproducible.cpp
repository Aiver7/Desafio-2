#include "IReproducible.h"
#include <QString>

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
