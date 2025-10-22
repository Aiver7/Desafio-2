#include <iostream>
#include <QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    int opcion = -1;
    out << "UdeATunes\n";
    out << "1) Ingresar\n2) Reproducir aleatorio\n3) Favoritos (Premium)\n0) Salir\n> " << flush;
    in >> opcion; // luego haremos el bucle y dispatcher
    return 0;     // temporal
}
