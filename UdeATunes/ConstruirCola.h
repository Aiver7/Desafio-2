#ifndef CONSTRUIR_COLA_H
#define CONSTRUIR_COLA_H
#include "Loaders.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Usuario.h"

struct ResultadoCarga {
    CancionArr canciones;
    AnuncioArr anuncios;
    GestorPublicidad gestor;
};

static void ReconstruirCola(CancionArr& ca, AnuncioArr& aa, ColaReproduccion& cola, bool premium, const Usuario& u){
    cola.clear();
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    for(int i=0;i<ca.n; ++i){
        encolarCancion(cola, &ca.items[i], premium, &gp, u);
    }
}
#endif
