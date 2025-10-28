#ifndef CLASEPRINCIPAL_H
#define CLASEPRINCIPAL_H
#include <QTextStream>
#include "CargasCancionAnuncio.h"
#include "CargasUsuarios.h"
#include "ColaReproduccion.h"
#include "GestorPublicidad.h"
#include "Usuario.h"
#include "Aleatorio.h"
#include "Favoritos.h"
#include "Medidor.h"

class ClasePrincipal {
public:
    ClasePrincipal(QTextStream& in, QTextStream& out);
    bool init();
    void run();

private:
    QTextStream& in; QTextStream& out;
    CancionArr ca; AnuncioArr aa; UsuarioArr ua;
    ColaReproduccion cola;
    Usuario u; bool premium{false};
    Favoritos fav;

    void imprimirMenu();
    void reconstruirCola();
    void mostrarEstado();
    void cambiarPlan();
    void recargarDatos();
    void reproducirActual_();
    void siguiente_();
    void reproducirTodo_();
    void aleatorio_();
    void menuFavoritos_();
    bool login_();
};

#endif
