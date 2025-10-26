#ifndef COLAREPRODUCCION_H
#define COLAREPRODUCCION_H
#include <QString>
#include "IReproducible.h"

struct ColaReproduccion {
    IReproducible items[256];
    int count{0}, idx{0};
    int cancionesDesdeAd{0}; // cada 2 canciones para estándar
    void clear(){ count=idx=cancionesDesdeAd=0; }
    bool push(const IReproducible& it){ if(count>=256) return false; items[count++]=it; return true; }
    IReproducible* actual(){ return (idxount)? &items[idx] : nullptr; }
    void avanzarSecuencial(){ if(count) idx = (idx+1)%count; }
};
#endif
