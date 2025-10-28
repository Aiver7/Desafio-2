#include "ClasePrincipal.h"
#include <QDir>
#include <chrono>
#include <thread>
#include <cstdlib>

ClasePrincipal::ClasePrincipal(QTextStream& in_, QTextStream& out_)
    : in(in_), out(out_) {}

bool ClasePrincipal::init(){
    bool okC = cargarCanciones("./canciones.txt", ca);
    bool okA = cargarAnuncios ("./anuncios.txt",  aa);
    out << "canciones=" << ca.n << " anuncios=" << aa.n
        << " okC=" << okC << " okA=" << okA << "\n";

    if(!cargarUsuarios("./usuarios.txt", ua)){
        out << "No se pudo cargar usuarios\n";
        return false;
    }
    if(!login_()) return false;

    reconstruirCola();
    out << "cola=" << cola.count << "\n";
    return true;
}

bool ClasePrincipal::login_(){
    out << "Usuario: "; out.flush();
    QString nick = in.readLine();
    if(!loginPorNick(ua, nick.toUtf8().constData(), u)){
        out << "Usuario no encontrado. Entrando como estandar.\n";
        u.setNickname("invitado");
        u.setPlanPremium(false);
    }
    premium = u.esPremium();
    out << "Bienvenido " << u.getNickname()
        << " (plan=" << (premium? "PREMIUM":"ESTANDAR") << ")\n";
    return true;
}

void ClasePrincipal::imprimirMenu(){
    out << "\n--- UdeATunes ---\n"
        << "1) Reproducir actual\n"
        << "2) Siguiente\n"
        << "3) Cambiar plan (Premium/Estandar)\n"
        << "4) Recargar datos\n"
        << "5) Reproducir todo\n"
        << "6) Mostrar estado\n"
        << "7) Aleatorio\n";
    if(premium) out << "8) Favoritos\n";
    out << "0) Salir\n> " << Qt::flush;
}

void ClasePrincipal::reconstruirCola(){
    cola.clear();
    GestorPublicidad gp; for(int i=0;i<aa.n; ++i) gp.add(&aa.items[i]);
    for(int i=0;i<ca.n; ++i){ encolarCancion(cola, &ca.items[i], premium, &gp, u); }
}

void ClasePrincipal::mostrarEstado(){
    Medidor M; med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
    out << "estado: canciones="<<ca.n<<" anuncios="<<aa.n
        <<" premium="<<(premium?1:0)<<" cola="<<cola.count<<"\n";
    med_add_iters(M,1);
    med_print("estado", M);
}

void ClasePrincipal::cambiarPlan(){
    Medidor M; med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
    premium = !premium;
    out << "[Plan cambiado] premium=" << (premium?1:0) << "\n";
    reconstruirCola();
    out << "cola=" << cola.count << "\n";
    med_add_iters(M, ca.n + aa.n + cola.count);
    med_print("reconstruir", M);
}

void ClasePrincipal::recargarDatos(){
    Medidor M;
    ca.n=0; aa.n=0;
    bool okC = cargarCanciones("./canciones.txt", ca);
    bool okA = cargarAnuncios ("./anuncios.txt",  aa);
    out << "recarga: okC=" << okC << " okA=" << okA
        << " canciones=" << ca.n << " anuncios=" << aa.n << "\n";
    reconstruirCola();
    out << "cola=" << cola.count << "\n";
    med_add_bytes_arr(M, ca); med_add_bytes_arr(M, aa); med_add_bytes(M, cola);
    med_add_iters(M, ca.n + aa.n + cola.count);
    med_print("recargar", M);
}

void ClasePrincipal::reproducirActual_(){
    Medidor M; med_add_bytes(M, cola);
    reproducirActual(cola, premium);
    med_add_iters(M,1);
    med_print("actual", M);
}

void ClasePrincipal::siguiente_(){
    Medidor M; med_add_bytes(M, cola);
    siguienteSecuencial(cola);
    reproducirActual(cola, premium);
    med_add_iters(M,2);
    med_print("siguiente", M);
}

void ClasePrincipal::reproducirTodo_(){
    Medidor M; med_add_bytes(M, cola);
    for(int i=0;i<cola.count; ++i){ reproducirActual(cola, premium); siguienteSecuencial(cola); }
    med_add_iters(M, 2*cola.count);
    med_print("todo", M);
}

void ClasePrincipal::aleatorio_(){
    reproducirAleatorio(ca, aa, u, premium);
}

void ClasePrincipal::menuFavoritos_(){
    if(!premium){ out<<"Solo premium tiene favoritos.\n"; return; }
    for(;;){
        out << "\n-- Favoritos --\n"
            << "1) Agregar por id\n"
            << "2) Quitar por id\n"
            << "3) Listar\n"
            << "4) Seguir usuario (fusionar)\n"
            << "5) Reproducir (orden)\n"
            << "6) Reproducir (aleatorio)\n"
            << "0) Volver\n> " << Qt::flush;
        int fop=-1; in >> fop;
        if (in.status()!=QTextStream::Ok){ in.reset(); in.readLine(); out<<"Entrada no valida.\n"; continue; }
        if(fop==0) break;

        if(fop==1){
            out<<"id: "; int id; in>>id;
            Medidor M; bool ok = fav.add(id); med_add_iters(M,1); med_add_bytes(M, fav);
            out<<(ok?"[OK] agregado\n":"[WARN] ya estaba o lleno\n");
            med_print("fav-add", M);
        } else if(fop==2){
            out<<"id: "; int id; in>>id;
            Medidor M; bool ok = fav.remove(id); med_add_iters(M,1); med_add_bytes(M, fav);
            out<<(ok?"[OK] eliminado\n":"[WARN] no estaba\n");
            med_print("fav-del", M);
        } else if(fop==3){
            Medidor M; med_add_bytes(M, fav);
            out<<"favoritos(n="<<fav.size()<<"):";
            for(int i=0;i<fav.size(); ++i) out<<" "<<fav.idAt(i);
            out<<"\n"; med_add_iters(M, fav.size()+1);
            med_print("fav-list", M);
        } else if(fop==4){
            out<<"nick premium a seguir: "; QString dump=in.readLine(); QString tgt=in.readLine();
            Usuario temp; bool okU=false;
            for(int i=0;i<ua.n; ++i){
                if(ua.items[i].getNickname().compare(tgt, Qt::CaseInsensitive)==0){ temp=ua.items[i]; okU=true; break; }
            }
            Medidor M; med_add_bytes(M, fav);
            if(!okU || !temp.esPremium()){ out<<"No existe o no es premium.\n"; med_print("fav-seguir", M); continue; }
            int added = 0; // integrar persistencia si se requiere
            med_add_iters(M, added);
            out<<"fusionados="<<added<<"\n";
            med_print("fav-seguir", M);
        } else if(fop==5){
            if(fav.size()==0){ out<<"Sin favoritos.\n"; continue; }
            Reproductor::favoritosOrden(fav, ca, aa, u, premium);
        } else if(fop==6){
            if(fav.size()==0){ out<<"Sin favoritos.\n"; continue; }
            Reproductor::favoritosAleatorio(fav, ca, aa, u, premium);
        } else {
            out<<"Opcion no valida.\n";
        }
    }
}

void ClasePrincipal::run(){
    for(;;){
        imprimirMenu();
        int op = -1; in >> op;
        if (in.status()!=QTextStream::Ok){ in.reset(); in.readLine(); out<<"Entrada no valida.\n"; continue; }
        if(op==0){ out<<"Saliendo...\n"; break; }
        else if(op==1){ reproducirActual_(); }
        else if(op==2){ siguiente_(); }
        else if(op==3){ cambiarPlan(); }
        else if(op==4){ recargarDatos(); }
        else if(op==5){ reproducirTodo_(); }
        else if(op==6){ mostrarEstado(); }
        else if(op==7){ aleatorio_(); }
        else if(op==8){ if(!premium){ out<<"Opcion solo para usuarios PREMIUM.\n"; continue; } menuFavoritos_(); }
        else { out<<"Opcion no valida.\n"; }
    }
}
