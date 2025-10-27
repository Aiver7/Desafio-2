#include "Aleatorio.h"
#include "Cancion.h"
#include "Anuncio.h"
#include "Usuario.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include <QTextStream>
#include <chrono>
#include <thread>

// ... implementación reproducirAleatorio(...)


static inline int nextIdx(int n){
    static unsigned seed=123457u;
    seed = seed*1103515245u + 12345u;
    return (int)(seed % (unsigned)n);
}

void reproducirAleatorio(CancionArr& ca, AnuncioArr& aa, Usuario& u, bool premium){
    QTextStream out(stdout);
    ColaReproduccion cola;
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    for(int i=0;i<ca.n; ++i){
        int j = nextIdx(ca.n);
        encolarCancion(cola, &ca.items[j], premium, &gp, u);
    }
    int k=0;
    while(k<5 && cola.count>0){
        reproducirActual(cola, premium);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        siguienteSecuencial(cola);
        ++k;
    }
}
