#ifndef MEDIDOR_H
#define MEDIDOR_H
#include <cstddef>

struct Medida { long iter{0}; size_t memoria{0}; };
extern Medida gMed;
void med_iniciar();
void med_iter(long k=1);
void med_sumarMem(size_t b);
void med_imprimir();

#endif
