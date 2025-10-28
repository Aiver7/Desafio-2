#include "Favoritos.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Medidor.h"
#include "ReproductorControles.h"
#include <QTextStream>
#include <chrono>
#include <thread>
#include <cstdlib>

static inline int rnd(int n){ return n? std::rand()%n : 0; }

static void pausa_reproduccion(Medidor& M){
    QTextStream out(stdout);
    out << "reproduciendo..." << Qt::flush;         med_add_iters(M,1);
    std::this_thread::sleep_for(std::chrono::seconds(3));     med_add_iters(M,1);
    out << "\n";
}

static void reproducirIdx(ColaReproduccion& cola, GestorPublicidad& gp, CancionArr& ca,
                          int idx, const Usuario& u, bool premium, Medidor& M){
    encolarCancion(cola, &ca.items[idx], premium, &gp, u);    med_add_iters(M,1);
    reproducirActual(cola, premium);                          med_add_iters(M,1);
    pausa_reproduccion(M);
    siguienteSecuencial(cola);                                 med_add_iters(M,1);
}

struct Hist {
    static const int CAP = 6;
    int a[CAP]; int top{0};
    void push(int pos){
        if(top < CAP){ a[top++] = pos; }
        else { for(int i=1;i<CAP;++i) a[i-1]=a[i]; a[CAP-1]=pos; }
    }
    bool canBack() const { return top >= 2; }
    int backPos(){
        if(top < 2) return -1;
        int prev = a[top-2];
        top -= 1;
        return prev;
    }
};

void Reproductor::aleatorio(CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium){
    const int K = 5;
    QTextStream out(stdout), in(stdin);
    ColaReproduccion cola;
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);

    Medidor M; med_add_bytes(M, cola); med_add_bytes(M, gp); med_add_bytes(M, u); med_add_bytes(M, premium);

    if(ca.n==0){ med_print("aleatorio", M); return; }
    int j = rnd(ca.n);                                         med_add_iters(M,1);
    reproducirIdx(cola, gp, ca, j, u, premium, M);

    Hist h; h.push(j);

    for(int k=1; k<K; ++k){
        char cmd = premium ? leerControlPremium(in, out) : 's';  med_add_iters(M,1);
        if(cmd=='t'){
        } else if(cmd=='r' && h.canBack()){
            j = h.backPos();                                     med_add_iters(M,1);
        } else {
            j = rnd(ca.n);                                       med_add_iters(M,1);
        }
        reproducirIdx(cola, gp, ca, j, u, premium, M);
        h.push(j);                                               med_add_iters(M,1);
    }
    med_print("aleatorio", M);
}

void Reproductor::favoritosOrden(const Favoritos& f, CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium){
    QTextStream out(stdout), in(stdin);
    ColaReproduccion cola; GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    Medidor M; med_add_bytes(M, cola); med_add_bytes(M, gp);

    // Construir secuencia (mapear id → idx catálogo)
    int seq[10000]; int m=0;
    for(int k=0; k<f.size(); ++k){
        int id=f.idAt(k), idx=-1;
        for(int i=0;i<ca.n; ++i){ if(ca.items[i].id==id){ idx=i; break; } } med_add_iters(M, ca.n);
        if(idx>=0) seq[m++]=idx;
    }
    if(m==0){ med_print("fav-orden", M); return; }

    int pos = 0;
    reproducirIdx(cola, gp, ca, seq[pos], u, premium, M);
    Hist histPos; histPos.push(pos);                               med_add_iters(M,1);

    while(true){
        char cmd = premium ? leerControlPremium(in, out) : 's';    med_add_iters(M,1);

        if(cmd=='t'){
            // repetir: pos no cambia
        } else if((cmd=='r' || cmd=='v') && histPos.canBack()){
            pos = histPos.backPos();                                med_add_iters(M,1);
        } else { // ‘s’, ‘c’, enter u otra tecla → siguiente
            if(pos+1 < m){ pos++; } else break;                     med_add_iters(M,1);
        }

        reproducirIdx(cola, gp, ca, seq[pos], u, premium, M);
        histPos.push(pos);                                          med_add_iters(M,1);
    }
    med_print("fav-orden", M);
}

void Reproductor::favoritosAleatorio(const Favoritos& f, CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium){
    QTextStream out(stdout), in(stdin);
    ColaReproduccion cola; GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    Medidor M; med_add_bytes(M, cola); med_add_bytes(M, gp);

    if(f.size()<=0){ med_print("fav-aleatorio", M); return; }

    // Secuencia barajada (índices de catálogo)
    int seq[10000]; int m=0;
    for(int k=0; k<f.size(); ++k){
        int id=f.idAt(k), idx=-1;
        for(int i=0;i<ca.n; ++i){ if(ca.items[i].id==id){ idx=i; break; } } med_add_iters(M, ca.n);
        if(idx>=0) seq[m++]=idx;
    }
    for(int i=m-1;i>0; --i){ int j=rnd(i+1); int t=seq[i]; seq[i]=seq[j]; seq[j]=t; } med_add_iters(M, m);
    if(m==0){ med_print("fav-aleatorio", M); return; }

    int pos = 0;
    reproducirIdx(cola, gp, ca, seq[pos], u, premium, M);
    Hist histPos; histPos.push(pos);                                  med_add_iters(M,1);

    while(true){
        char cmd = premium ? leerControlPremium(in, out) : 's';       med_add_iters(M,1);

        if(cmd=='t'){
            // repetir pos
        } else if((cmd=='r' || cmd=='v') && histPos.canBack()){
            pos = histPos.backPos();                                   med_add_iters(M,1);
        } else { // siguiente
            if(pos+1 < m){ pos++; } else break;                        med_add_iters(M,1);
        }

        reproducirIdx(cola, gp, ca, seq[pos], u, premium, M);
        histPos.push(pos);                                             med_add_iters(M,1);
    }
    med_print("fav-aleatorio", M);
}
