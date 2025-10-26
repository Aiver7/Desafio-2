#include <QCoreApplication>
#include <QTextStream>
#include "Cancion.h"
#include "Anuncio.h"
#include "IReproducible.h"
#include "ColaReproduccion.h"
#include "Usuario.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    Usuario u;
    // selección de plan
    out << "Plan (0=Estandar, 1=Premium): ";
    out.flush();
    int p=0; in >> p;
    if (p==1) { /* suponer método set a premium si lo tienes; sino usa flag local */ }

    // Datos demo
    Cancion c; c.titulo="Demo Song"; c.path128="audio/demo_128.aac"; c.path320="audio/demo_320.aac"; c.coverPng="covers/demo.png"; c.duracionSeg=180;
    Anuncio a; a.mensaje="Compra 2x1 en UdeAStore"; a.duracionSeg=15; a.peso=2;

    ColaReproduccion cola;
    cola.push(IReproducible::fromCancion(&c));
    cola.push(IReproducible::fromAnuncio(&a));
    cola.push(IReproducible::fromCancion(&c));

    bool premium = (p==1);
    reproducirActual(cola, premium);
    siguienteSecuencial(cola);
    reproducirActual(cola, premium);
    siguienteSecuencial(cola);
    reproducirActual(cola, premium);
    return 0;
}
