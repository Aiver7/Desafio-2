#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include "CargasCancionAnuncio.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Usuario.h"
#include "CargasUsuarios.h"
#include "Aleatorio.h"
#include "Medidor.h"

// Reconstruye cola según plan/anuncios
static void ReconstruirColaFull(CancionArr& ca, AnuncioArr& aa, ColaReproduccion& cola, bool premium, const Usuario& u){
    cola.clear();
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    for(int i=0;i<ca.n; ++i){ encolarCancion(cola, &ca.items[i], premium, &gp, u); }
}

static void ImprimirMenu(QTextStream& out){
    out << "\n--- UdeATunes ---\n"
        << "1) Reproducir actual\n"
        << "2) Siguiente\n"
        << "3) Cambiar plan (Premium/Estandar)\n"
        << "4) Recargar datos\n"
        << "5) Reproducir todo\n"
        << "6) Mostrar estado\n"
        << "7) Aleatorio\n"
        << "0) Salir\n> " << Qt::flush;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);

    // Carga base de catálogo
    CancionArr ca; AnuncioArr aa;
    bool okC = cargarCanciones("./canciones.txt", ca);
    bool okA = cargarAnuncios ("./anuncios.txt",  aa);
    out << "canciones=" << ca.n << " anuncios=" << aa.n
        << " okC=" << okC << " okA=" << okA << "\n";

    // Login
    UsuarioArr ua;
    if(!cargarUsuarios("./usuarios.txt", ua)){
        out << "No se pudo cargar usuarios\n";
        return 0;
    }
    Usuario u; bool premium=false;
    out << "Usuario: "; out.flush();
    QString basura = in.readLine(); // limpia si vienes de >>
    QString nick   = in.readLine();
    if(!loginPorNick(ua, nick.toUtf8().constData(), u)){
        out << "Usuario no encontrado. Entrando como estandar.\n";
        u.setNickname("invitado");
        u.setPlanPremium(false);
    }
    premium = u.esPremium();
    out << "Bienvenido " << u.getNickname()
        << " (plan=" << (premium? "PREMIUM":"ESTANDAR") << ")\n";

    // Cola y lambda
    ColaReproduccion cola;
    auto ReconstruirCola = [&](){
        ReconstruirColaFull(ca, aa, cola, premium, u);
    };

    // Construcción inicial
    ReconstruirCola();
    out << "cola=" << cola.count << "\n";

    for(;;){
        ImprimirMenu(out);
        int op = -1;
        in >> op;
        if (in.status()!=QTextStream::Ok){ in.reset(); in.readLine(); out<<"Entrada no valida.\n"; continue; }

        if(op==0){ out<<"Saliendo...\n"; break; }

        else if(op==1){ // Reproducir actual
            Medidor M; med_add_bytes(M, cola);
            reproducirActual(cola, premium);
            med_add_iters(M,1);
            med_print("actual", M);
        }
        else if(op==2){ // Siguiente
            Medidor M; med_add_bytes(M, cola);
            siguienteSecuencial(cola);
            reproducirActual(cola, premium);
            med_add_iters(M,2);
            med_print("siguiente", M);
        }
        else if(op==3){ // Cambiar plan
            Medidor M;
            med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
            premium = !premium;
            out << "[Plan cambiado] premium=" << (premium?1:0) << "\n";
            ReconstruirCola();
            out << "cola=" << cola.count << "\n";
            med_add_iters(M, ca.n + aa.n + cola.count);
            med_print("reconstruir", M);
        }
        else if(op==4){ // Recargar datos
            Medidor M;
            ca.n=0; aa.n=0;
            bool okC2 = cargarCanciones("./canciones.txt", ca);
            bool okA2 = cargarAnuncios ("./anuncios.txt",  aa);
            out << "recarga: okC=" << okC2 << " okA=" << okA2
                << " canciones=" << ca.n << " anuncios=" << aa.n << "\n";
            ReconstruirCola();
            out << "cola=" << cola.count << "\n";
            med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
            med_add_iters(M, ca.n + aa.n + cola.count);
            med_print("recargar", M);
        }
        else if(op==5){ // Reproducir todo
            Medidor M; med_add_bytes(M, cola);
            for(int i=0;iola.count; ++i){ reproducirActual(cola, premium); siguienteSecuencial(cola); }
            med_add_iters(M, 2*cola.count);
            med_print("todo", M);
        }
        else if(op==6){ // Mostrar estado
            Medidor M; med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
            out << "estado: canciones="<.n<<" anuncios="<<aa.n
                                            <<" premium="<<(premium?1:0)<<" cola="<ola.count<<"\n";
            med_add_iters(M,1);
            med_print("estado", M);
        }
        else if(op==7){ // Aleatorio
            reproducirAleatorio(ca, aa, u, premium);
        }
        else { out << "Opcion no valida.\n"; }
    }
    return 0;
}
