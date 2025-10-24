#include <iostream>
#include <QCoreApplication>
#include <QTextStream>
#include "Album.h"
#include "Cancion.h"
#include "Anuncio.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);
    int opcion = -1;
    while (true) {
        out << "\nUdeATunes\n"
            << "1) Ingresar\n2) Reproducir aleatorio\n3) Favoritos (Premium)\n0) Salir\n> ";
        out.flush();
        in >> opcion;
    return 0;
}
