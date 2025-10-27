#include "Favoritos.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"

static inline int nextIdxFav(int n){
    static unsigned seed=98765u;
    seed = seed*1103515245u + 12345u;
    return (int)(seed % (unsigned)n);
}

bool ejecutarFavoritos(const Favoritos& f, AnuncioArr& aa, Usuario& u, bool premium, bool aleatorio){
    ColaReproduccion cola;
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    if(aleatorio){
        for(int i=0;i<f.n; ++i){
            int j = nextIdxFav(f.n);
            encolarCancion(cola, const_cast<Cancion*>(f.items[j]), premium, &gp, u);
        }
    } else {
        for(int i=0;i<f.n; ++i){
            encolarCancion(cola, const_cast<Cancion*>(f.items[i]), premium, &gp, u);
        }
    }
    for(int i=0;i<cola.count; ++i){ reproducirActual(cola, premium); siguienteSecuencial(cola); }
    return true;
}

bool fusionarFavoritos(Favoritos& base, const Favoritos& otra){
    bool ok=true; for(int i=0;i<otra.n; ++i) ok &= base.agregar(otra.items[i]); return ok;
}
