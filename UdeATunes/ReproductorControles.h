#ifndef REPRODUCTORCONTROLES_H
#define REPRODUCTORCONTROLES_H
#include <QTextStream>

inline char leerControlPremium(QTextStream& in, QTextStream& out){
    out << "[controles premium] (r=retroceder, s=siguiente, t=repetir, v=volver, c=continuar): " << Qt::flush;
    QString s = in.readLine();
    return s.isEmpty()? 'c' : s[0].toLatin1();
}

#endif
