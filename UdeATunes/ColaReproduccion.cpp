#include "ColaReproduccion.h"
#include <QTextStream>

static void imprimirItem(const IReproducible& r, bool premium){
    QTextStream out(stdout);
    if (r.esCancion()){
        out << "Portada: " << ir_cover(r) << "\n";
        out << "Audio: "   << ir_audioPath(r, premium) << "\n";
    } else if (r.esAnuncio()){
        out << ir_titulo(r) << "\n";
    }
}

void avanzarSegunPlan(ColaReproduccion& cola, bool premium){
    if (cola.count==0) return;
    int guard=0;
    while (guard<cola.count){
        IReproducible* it = cola.actual();
        if (!it) return;
        if (premium && it->esAnuncio()){ cola.avanzarSecuencial(); ++guard; continue; }
        break;
    }
}

void reproducirActual(ColaReproduccion& cola, bool premium){
    avanzarSegunPlan(cola, premium);
    IReproducible* it = cola.actual();
    if (!it) return;
    imprimirItem(*it, premium);
}

void siguienteSecuencial(ColaReproduccion& cola){
    if (cola.count==0) return;
    cola.avanzarSecuencial();
}
