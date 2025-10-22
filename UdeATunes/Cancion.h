#ifndef CANCION_H
#define CANCION_H
#include <QTextStream>
#include "IReproducible.h"
class Album;

class Cancion : public IReproducible {
    QString id, tituloCancion, rutaOgg128, rutaOgg320;
    int duracion = 0; bool esExplicita = false; Album* album = nullptr;
public:
    Cancion(const QString& id_, const QString& titulo_, int dur, bool explicita)
        : id(id_), tituloCancion(titulo_), duracion(dur), esExplicita(explicita) {}

    void asignarAlbum(Album* a){ album = a; }
    void asignarRutas(const QString& ogg128, const QString& ogg320){ rutaOgg128 = ogg128; rutaOgg320 = ogg320; }

    int duracionSeg() const override { return duracion; }
    QString titulo()   const override { return tituloCancion; }

    void reproducir() override {
        QTextStream out(stdout);
        out << "Cantante: " << (album? album->getNombreCantante() : "N/D") << "\n"
            << "Album: "    << (album? album->getNombreAlbum()    : "N/D") << "\n"
            << "Ruta a la portada: " << (album? album->getRutaPortada() : "N/D") << "\n"
            << "Titulo: " << tituloCancion << "\n"
            << "Ruta al audio: " << rutaOgg128 << "\n"
            << "Ruta al audio: " << rutaOgg320 << "\n"
            << "Duracion): " << duracion << "\n";
    }
};
#endif // CANCION_H
