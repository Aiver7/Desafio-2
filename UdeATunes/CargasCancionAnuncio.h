#ifndef CARGASCANCIONANUNCIO_H
#define CARGASCANCIONANUNCIO_H
#include "Cancion.h"
#include "Anuncio.h"

bool cargarCanciones(const char* ruta, CancionArr& ca);
bool cargarAnuncios (const char* ruta, AnuncioArr& aa);

#endif
