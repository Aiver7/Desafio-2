#ifndef FAVORITOS_H
#define FAVORITOS_H
#include "Cancion.h"
#include "Anuncio.h"
#include "Usuario.h"

struct Favoritos {
    const Cancion* items[10000];
    int n{0};
    bool agregar(const Cancion* c){
        if(n>=10000) return false;
        for(int i=0;i<n; ++i) if(items[i]==c) return false;
        items[n++]=c; return true;
    }
    bool quitar(long id){
        for(int i=0;i<n; ++i){ if(items[i]->id==id){ items[i]=items[n-1]; --n; return true; } }
        return false;
    }
};

bool ejecutarFavoritos(const Favoritos& f, AnuncioArr& aa, Usuario& u, bool premium, bool aleatorio);
bool fusionarFavoritos(Favoritos& base, const Favoritos& otra);

#endif
