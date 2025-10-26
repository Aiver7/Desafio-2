#ifndef IREPRODUCIBLE_H
#define IREPRODUCIBLE_H
#include <QString>
#include "Cancion.h"
#include "Anuncio.h"

enum RepTipo { REP_CANCION=0, REP_ANUNCIO=1 };

struct IReproducible {
    RepTipo  tipo{REP_CANCION};
    Cancion* cancion{nullptr};
    Anuncio* anuncio{nullptr};
    bool esCancion() const { return tipo==REP_CANCION && cancion; }
    bool esAnuncio() const { return tipo==REP_ANUNCIO && anuncio; }
    static IReproducible fromCancion(Cancion* c){ IReproducible r; r.tipo=REP_CANCION; r.cancion=c; return r; }
    static IReproducible fromAnuncio(Anuncio* a){ IReproducible r; r.tipo=REP_ANUNCIO; r.anuncio=a; return r; }
};

int      ir_duracion (const IReproducible& r);
QString  ir_titulo   (const IReproducible& r);
QString  ir_audioPath(const IReproducible& r, bool premium);
QString  ir_cover    (const IReproducible& r);
#endif
