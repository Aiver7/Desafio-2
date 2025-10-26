#ifndef GESTORPUBLICIDAD_H
#define GESTORPUBLICIDAD_H
#include <QRandomGenerator>
#include "Anuncio.h"
#include "Usuario.h"

struct CtxAnuncio { int hora{0}; };

struct GestorPublicidad {
    Anuncio* anuncios[64];
    int n{0};

    void clear(){ n=0; }
    void add(Anuncio* a){ if(n<64) anuncios[n++]=a; }

    int totalPeso() const {
        int s=0; for(int i=0;i<n;++i) s += anuncios[i]->peso; return s;
    }

    Anuncio* seleccionarPara(const Usuario&, const CtxAnuncio&){
        int total = totalPeso();
        if (total<=0 || n==0) return nullptr;
        int r = QRandomGenerator::global()->bounded(total);
        int acc=0;
        for(int i=0;i<n;++i){ acc += anuncios[i]->peso; if(r<acc) return anuncios[i]; }
        return anuncios[0];
    }
};
#endif
