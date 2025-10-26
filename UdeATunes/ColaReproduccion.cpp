#include "ColaReproduccion.h"
#include <QTextStream>

// Impresión uniforme según IReproducible
static void imprimirItem(const IReproducible& r, bool premium){
    QTextStream out(stdout);
    if (r.esCancion()){
        out << "Portada: " << ir_cover(r) << "\n";
        out << "Audio: "   << ir_audioPath(r, premium) << "\n";
    } else if (r.esAnuncio()){
        out << ir_titulo(r) << "\n";
    }
}

// Reproduce el elemento actual (si existe).
void reproducirActual(ColaReproduccion& cola, bool premium){
    IReproducible* it = cola.actual();
    if (!it) return;
    imprimirItem(*it, premium);
}

// Avanza al siguiente en modo secuencial.
void siguienteSecuencial(ColaReproduccion& cola){
    if (cola.count==0) return;
    cola.avanzarSecuencial();
}
