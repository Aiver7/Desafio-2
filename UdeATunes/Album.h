#ifndef ALBUM_H
#define ALBUM_H
#include <QString>

class Album {
    QString nombreAlbum, nombreCantante, rutaPortada;
public:
    Album(const QString& album, const QString& cantante, const QString& portada)
        : nombreAlbum(album), nombreCantante(cantante), rutaPortada(portada) {}

    const QString& getNombreAlbum()   const { return nombreAlbum; }
    const QString& getNombreCantante()const { return nombreCantante; }
    const QString& getRutaPortada()   const { return rutaPortada; }
};
#endif // ALBUM_H
