#ifndef CARGAS_USUARIOS_H
#define CARGAS_USUARIOS_H
#include "Usuario.h"

struct UsuarioArr { Usuario items[256]; int n{0}; };
bool cargarUsuarios(const char* ruta, UsuarioArr& ua);
bool loginPorNick(const UsuarioArr& ua, const char* nick, Usuario& u);

#endif
