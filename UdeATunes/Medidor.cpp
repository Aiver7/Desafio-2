#include "Medidor.h"
#include <QTextStream>

Medida gMed;
void med_iniciar(){ gMed.iter=0; gMed.memoria=0; }
void med_iter(long k){ gMed.iter+=k; }
void med_sumarMem(size_t b){ gMed.memoria+=b; }
void med_imprimir(){ QTextStream(stdout)<<"[Metrica] iter="<<gMed.iter<<" bytes="<<gMed.memoria<<"\n"; }
