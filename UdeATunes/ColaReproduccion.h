#ifndef COLA_REPRODUCCION_H
#define COLA_REPRODUCCION_H
#include <QTextStream>
#include "IReproducible.h"
class Cancion; class GestorPublicidad; class Usuario;

// Estructura de la cola
struct ColaReproduccion {
    IReproducible items[256];
    int count{0}, idx{0};
    int cancionesDesdeAd{0};
    void clear(){ count=idx=cancionesDesdeAd=0; }
    bool push(const IReproducible& it){ if(count>=256) return false; items[count++]=it; return true; }
    IReproducible* actual(){ return (idx<count)? &items[idx] : nullptr; }
    void avanzarSecuencial(){ if(count) idx = (idx+1)%count; }
};

const int AD_INTERVAL = 2;

// API
void reproducirActual(ColaReproduccion& cola, bool premium);
void siguienteSecuencial(ColaReproduccion& cola);
void avanzarSegunPlan(ColaReproduccion& cola, bool premium);
void encolarCancion(ColaReproduccion& cola, Cancion* c, bool premium, GestorPublicidad* gp, const Usuario& u);
void listarCola(const ColaReproduccion& cola); // opcional

#endif
