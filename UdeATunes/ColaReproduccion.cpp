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

void listarCola(const ColaReproduccion& cola){
    QTextStream out(stdout);
    out << "[Cola] total=" << cola.count << "\n";
    for(int i=0;i<cola.count; ++i){
        const IReproducible& it = cola.items[i];
        out << i << ": " << (it.esCancion()? "cancion":"anuncio") << "\n";
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

void encolarCancion(ColaReproduccion& cola, Cancion* c, bool premium, GestorPublicidad* gp, const Usuario& u){
    if (!premium && cola.cancionesDesdeAd >= AD_INTERVAL && gp){
        CtxAnuncio ctx;
        Anuncio* ad = gp->seleccionarPara(u, ctx);
        if (ad){ cola.push(IReproducible::fromAnuncio(ad)); cola.cancionesDesdeAd = 0; }
    }
    cola.push(IReproducible::fromCancion(c));
    if (!premium) cola.cancionesDesdeAd++;
}
