#ifndef IREPRODUCIBLE_H
#define IREPRODUCIBLE_H

#include <QString>

class IReproducible {
public:
    virtual ~IReproducible() = default;
    virtual int duracionSeg() const = 0;
    virtual QString titulo() const = 0;
    virtual void reproducir() = 0; // imprimirá info de reproducción
};

#endif // IREPRODUCIBLE_H
