#ifndef IREPRODUCIBLE_H
#define IREPRODUCIBLE_H
#include <QString>
struct Cancion; struct Anuncio;

struct IReproducible {
    enum Tipo { T_CANCION, T_ANUNCIO } tipo;
    union { Cancion* c; Anuncio* a; } ref;
    static IReproducible fromCancion(Cancion* pc){ IReproducible r; r.tipo=T_CANCION; r.ref.c=pc; return r; }
    static IReproducible fromAnuncio(Anuncio* pa){ IReproducible r; r.tipo=T_ANUNCIO; r.ref.a=pa; return r; }
    bool esCancion() const { return tipo==T_CANCION; }
    bool esAnuncio() const { return tipo==T_ANUNCIO; }
};

QString ir_titulo(const IReproducible& r);
QString ir_cover (const IReproducible& r);
QString ir_audioPath(const IReproducible& r, bool premium);

#endif
