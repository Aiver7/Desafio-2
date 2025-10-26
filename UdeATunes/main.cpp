#include <QCoreApplication>
#include <QTextStream>
#include "Loaders.h"
#include "IReproducible.h"
#include "ColaReproduccion.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    out << "Plan (0=Estandar, 1=Premium): " << Qt::flush;
    int p=0; in >> p; bool premium = (p==1);

    CancionArr ca; AnuncioArr aa;
    cargarCanciones("./canciones.txt", ca);
    cargarAnuncios ("./anuncios.txt",  aa);

    ColaReproduccion cola;
    if (ca.n>0) cola.push(IReproducible::fromCancion(&ca.items[0]));
    if (!premium && aa.n>0) cola.push(IReproducible::fromAnuncio(&aa.items[0])); // solo en estándar
    if (ca.n>1) cola.push(IReproducible::fromCancion(&ca.items[1]));

    reproducirActual(cola, premium);
    siguienteSecuencial(cola); reproducirActual(cola, premium);
    siguienteSecuencial(cola); reproducirActual(cola, premium);
    return 0;
}
