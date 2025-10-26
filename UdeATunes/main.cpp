// src/main.cpp
#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include "Loaders.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Usuario.h"

// Utilidad simple para reconstruir la cola aplicando la política de anuncios
static void ReconstruirCola(CancionArr& ca, AnuncioArr& aa, ColaReproduccion& cola, bool premium, const Usuario& u){
    cola.clear();
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    int toAdd = ca.n<5 ? ca.n : 5;
    for(int i=0;i<toAdd; ++i){
        encolarCancion(cola, &ca.items[i], premium, &gp, u);
    }
}

static void ImprimirMenu(QTextStream& out){
    out << "\n--- UdeATunes ---\n"
        << "1) Reproducir actual\n"
        << "2) Siguiente\n"
        << "3) Cambiar plan (Premium/Estandar)\n"
        << "4) Recargar datos\n"
        << "0) Salir\n> " << Qt::flush;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    out << "WD: " << QDir::currentPath() << "\n";

    // Cargar datos iniciales
    CancionArr ca; AnuncioArr aa;
    bool okC = cargarCanciones("./canciones.txt", ca);
    bool okA = cargarAnuncios ("./anuncios.txt",  aa);
    out << "canciones=" << ca.n << " anuncios=" << aa.n << " okC=" << okC << " okA=" << okA << "\n";

    Usuario u; // usa tu implementación real
    bool premium = true; // inicia premium
    ColaReproduccion cola;
    ReconstruirCola(ca, aa, cola, premium, u);
    out << "cola=" << cola.count << "\n";

    for(;;){
        ImprimirMenu(out);
        int op = -1;

        // 1) Lee un entero con extracción
        in >> op;

        // 2) Verifica fallos de entrada (no compares el stream directamente)
        if (in.status() != QTextStream::Ok) {
            in.reset();        // limpia flags de error
            in.readLine();     // descarta la línea inválida
            out << "Entrada no valida.\n";
            continue;
        }

        out << "op=" << op << "\n";

        if(op==0){ out << "Saliendo...\n"; break; }
        if(op==1){
            out << "[Reproducir actual]\n";
            reproducirActual(cola, premium);
        } else if(op==2){
            out << "[Siguiente]\n";
            siguienteSecuencial(cola);
            reproducirActual(cola, premium);
        } else if(op==3){
            premium = !premium;
            out << "[Plan cambiado] premium=" << (premium?1:0) << "\n";
            ReconstruirCola(ca, aa, cola, premium, u);
            out << "cola=" << cola.count << "\n";
        } else if(op==4){
            out << "[Recargar datos]\n";
            ca.n=0; aa.n=0;
            bool okC = cargarCanciones("data/canciones.txt", ca);
            bool okA = cargarAnuncios ("data/anuncios.txt",  aa);
            out << "recarga: okC=" << okC << " okA=" << okA << " canciones=" << ca.n << " anuncios=" << aa.n << "\n";
            ReconstruirCola(ca, aa, cola, premium, u);
            out << "cola=" << cola.count << "\n";
        } else {
            out << "Opcion no valida.\n";
        }
    }
    return 0;
}
