#include "IReproducible.h"
#include "Cancion.h"
#include "Anuncio.h"

QString ir_titulo(const IReproducible& r){
    return r.esCancion()? r.ref.c->titulo : r.ref.a->mensaje;
}
QString ir_cover(const IReproducible& r){
    return r.esCancion()? r.ref.c->coverPng : QString("N/A");
}
QString ir_audioPath(const IReproducible& r, bool premium){
    if(r.esCancion()){
        return premium? r.ref.c->path320 : r.ref.c->path128;
    }
    return "N/A";
}

