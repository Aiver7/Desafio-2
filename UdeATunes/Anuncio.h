#ifndef ANUNCIO_H
#define ANUNCIO_H
#include <QTextStream>
#include "IReproducible.h"

class Anuncio : public IReproducible {
    QString id, mensaje; int duracion = 0; int prioridad = 1; // 1=C,2=B,3=AAA
public:
    Anuncio(const QString& id_, const QString& msg, int dur, int pri)
        : id(id_), mensaje(msg), duracion(dur), prioridad(pri) {}
    int duracionSeg() const override { return duracion; }
    QString titulo() const override { return id; }
    void reproducir() override {
        QTextStream out(stdout);
        out << "Mensaje publicitario: " << mensaje << " (cat: " << prioridad << ")\n";
    }
};
#endif // ANUNCIO_H
