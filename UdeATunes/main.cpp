#include <QCoreApplication>
#include <QTextStream>
#include "Cancion.h"
#include "IReproducible.h"
#include "ColaReproduccion.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    ColaReproduccion cola;
    Cancion c; c.titulo="Demo Song"; c.path128="audio/demo_128.aac"; c.path320="audio/demo_320.aac"; c.coverPng="covers/demo.png"; c.duracionSeg=180;
    cola.push(IReproducible::fromCancion(&c));
    reproducirActual(cola, true);
    return 0;
}
