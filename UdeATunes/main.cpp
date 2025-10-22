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
        if (opcion == 0) break;

        if (opcion == 2) {
            // muestraa
            Anuncio ad("AD003", "Premium 3 meses", 12, 3);
            ad.reproducir();

            Album album("Lugar Secreto","Claudia Lorelle",
                        "/users/storage/x/claudia lorelle/image/lugar secreto.png");
            Cancion tema("000030001","A tu lado",180,false);
            tema.asignarAlbum(&album);
            tema.asignarRutas("/users/storage/x/claudia lorelle/audio/a tu lado_128.ogg",
                              "/users/storage/x/claudia lorelle/audio/a tu lado_320.ogg");
            tema.reproducir();
        }
    }
    return 0;
}
