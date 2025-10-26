#ifndef LOADERS_H
#define LOADERS_H
#include <QString>
#include "Cancion.h"
#include "Anuncio.h"

struct CancionArr { Cancion items[128]; int n{0}; };
struct AnuncioArr { Anuncio items[64];  int n{0};  };

bool cargarCanciones(const QString& path, CancionArr& out);
bool cargarAnuncios (const QString& path, AnuncioArr& out);

#endif
