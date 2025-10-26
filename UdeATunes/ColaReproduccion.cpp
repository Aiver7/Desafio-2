#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Cancion.h"
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
    QTextStream out(stdout);
    if (it->esCancion()){
        out << "Portada: " << ir_cover(*it) << "\n";
        out << "Audio: "   << ir_audioPath(*it, premium) << "\n";
    } else if (it->esAnuncio()){
        out << ir_titulo(*it) << "\n";
    }
}

void siguienteSecuencial(ColaReproduccion& cola){
    if (cola.count==0) return;
    cola.avanzarSecuencial();
}

void encolarCancion(ColaReproduccion& cola, Cancion* c, bool premium, GestorPublicidad* gp, const Usuario& u){
    if (!premium && cola.cancionesDesdeAd >= 2 && gp){
        CtxAnuncio ctx;
        Anuncio* ad = gp->seleccionarPara(u, ctx);
        if (ad){ cola.push(IReproducible::fromAnuncio(ad)); cola.cancionesDesdeAd = 0; }
    }
    cola.push(IReproducible::fromCancion(c));
    if (!premium) cola.cancionesDesdeAd++;
}
