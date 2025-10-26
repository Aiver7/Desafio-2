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
    for(int i=0;i<ca.n; ++i){
        encolarCancion(cola, &ca.items[i], premium, &gp, u);
    }
}

static void ImprimirMenu(QTextStream& out){
    out << "\n--- UdeATunes ---\n"
        << "1) Reproducir actual\n"
        << "2) Siguiente\n"
        << "3) Cambiar plan (Premium/Estandar)\n"
        << "4) Recargar datos\n"
        << "5) Reproducir todo\n"
        << "6) Mostrar estado\n"
        << "0) Salir\n> " << Qt::flush;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    CancionArr ca; AnuncioArr aa;
    bool okC = cargarCanciones("./canciones.txt", ca);
    bool okA = cargarAnuncios ("./anuncios.txt",  aa);
    out << "canciones=" << ca.n << " anuncios=" << aa.n
        << " okC=" << okC << " okA=" << okA << "\n";

    Usuario u;
    bool premium = true;
    ColaReproduccion cola;              // declara cola aquí

    auto ReconstruirCola = [&](void){
        cola.clear();
        GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
        for(int i=0;i<ca.n; ++i){
            encolarCancion(cola, &ca.items[i], premium, &gp, u);
        }
    };

    ReconstruirCola();
    out << "cola=" << cola.count << "\n";

    for(;;){
        ImprimirMenu(out);
        int op = -1;
        in >> op;
        if (in.status()!=QTextStream::Ok){ in.reset(); in.readLine(); out<<"Entrada no valida.\n"; continue; }

        if(op==0){ out<<"Saliendo...\n"; break; }
        else if(op==1){ reproducirActual(cola, premium); }
        else if(op==2){ siguienteSecuencial(cola); reproducirActual(cola, premium); }
        else if(op==3){
            premium = !premium;
            out << "[Plan cambiado] premium=" << (premium?1:0) << "\n";
            ReconstruirCola();                          // úsala
            out << "cola=" << cola.count << "\n";
        }
        else if(op==4){
            ca.n=0; aa.n=0;
            okC = cargarCanciones("./canciones.txt", ca);
            okA = cargarAnuncios ("./anuncios.txt",  aa);
            out << "recarga: okC=" << okC << " okA=" << okA
                << " canciones=" << ca.n << " anuncios=" << aa.n << "\n";
            ReconstruirCola();                          // úsala
            out << "cola=" << cola.count << "\n";
        }
        else if(op==5){
            for(int i=0;i<cola.count; ++i){ reproducirActual(cola, premium); siguienteSecuencial(cola); }
        }
        else { out << "Opcion no valida.\n"; }
    }
    return 0;
}
