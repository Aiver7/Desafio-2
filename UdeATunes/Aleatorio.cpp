#include "Aleatorio.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Medidor.h"
#include <QTextStream>
#include <chrono>
#include <thread>
#include <cstdlib>

static inline int rnd(int n){ return n? std::rand()%n : 0; }

void reproducirAleatorio(CancionArr& ca, AnuncioArr& aa, const Usuario& u, bool premium){
    const int K = 5;
    QTextStream out(stdout);
    ColaReproduccion cola;
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);

    Medidor M; med_add_bytes(M, cola); med_add_bytes(M, gp); med_add_bytes(M, u); med_add_bytes(M, premium);

    for(int k=0; k<K && ca.n>0; ++k){
        int j = rnd(ca.n);                   med_add_iters(M,1);
        encolarCancion(cola, &ca.items[j], premium, &gp, u); med_add_iters(M,1);
        reproducirActual(cola, premium);     med_add_iters(M,1);
        if(k < K-1){
            out << "reproduciendo...\n" << Qt::flush;  med_add_iters(M,1);
            std::this_thread::sleep_for(std::chrono::seconds(3)); med_add_iters(M,1);
            out << "\n";
        }
        siguienteSecuencial(cola);           med_add_iters(M,1);
    }
    med_print("aleatorio", M);
}
