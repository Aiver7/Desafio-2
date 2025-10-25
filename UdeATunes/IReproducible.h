#ifndef IREPRODUCIBLE_H
#define IREPRODUCIBLE_H
#include <QString>

    class Cancion;
class Anuncio;

enum RepTipo { REP_CANCION=0, REP_ANUNCIO=1 };

struct IReproducible {
    RepTipo tipo{REP_CANCION};
    Cancion* cancion{nullptr};
    Anuncio* anuncio{nullptr};
    bool esCancion() const { return tipo==REP_CANCION && cancion; }
    bool esAnuncio() const { return tipo==REP_ANUNCIO && anuncio; }
};
inline int ir_duracion(const IReproducible& r);
inline QString ir_titulo(const IReproducible& r);
inline QString ir_audioPath(const IReproducible& r, bool premium);
inline QString ir_cover(const IReproducible& r);

#endif
