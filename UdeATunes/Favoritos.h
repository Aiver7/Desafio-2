#ifndef FAVORITOS_H
#define FAVORITOS_H
#include "CargasCancionAnuncio.h"
#include "Usuario.h"

class Favoritos {
    int ids_[10000];
    int n_{0};
public:
    int size() const { return n_; }
    bool contains(int id) const { for(int i=0;i<n_; ++i) if(ids_[i]==id) return true; return false; }
    bool add(int id){ if(n_>=10000 || contains(id)) return false; ids_[n_++]=id; return true; }
    bool remove(int id){ for(int i=0;i<n_; ++i) if(ids_[i]==id){ ids_[i]=ids_[n_-1]; --n_; return true; } return false; }
    int  idAt(int i) const { return ids_[i]; }
};

class Reproductor {
public:
    static void aleatorio(CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium);
    static void favoritosOrden(const Favoritos& f, CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium);
    static void favoritosAleatorio(const Favoritos& f, CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium);
};

#endif
