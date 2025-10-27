#include "CargasCancionAnuncio.h"
#include <QFile>
#include <QTextStream>

static inline QString at(const QStringList& v, int i){ return (i>=0 && i<v.size())? v[i].trimmed() : QString(); }

bool cargarCanciones(const char* ruta, CancionArr& ca){
    ca.n=0; QFile f(QString::fromUtf8(ruta));
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream in(&f);
    while(!in.atEnd() && ca.n<10000){
        QString s=in.readLine().trimmed(); if(s.isEmpty()) continue;
        QStringList p=s.split('|'); if(p.size()<8) continue;
        Cancion& c=ca.items[ca.n];
        c.id          = at(p,0).toLongLong();
        c.titulo      = at(p,1);
        c.albumId     = 0;
        c.duracionSeg = at(p,3).toInt();
        c.path128     = at(p,4);
        c.path320     = at(p,5);
        c.coverPng    = at(p,6);
        ca.n++;
    }
    return true;
}

bool cargarAnuncios(const char* ruta, AnuncioArr& aa){
    aa.n=0; QFile f(QString::fromUtf8(ruta));
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream in(&f);
    while(!in.atEnd() && aa.n<1000){
        QString s=in.readLine().trimmed(); if(s.isEmpty()) continue;
        // id|mensaje|duracionSeg|prioridadNum
        QStringList p=s.split('|'); if(p.size()<4) continue;
        Anuncio& a=aa.items[aa.n];
        a.id          = at(p,0).toLongLong();
        a.mensaje     = at(p,1);
        a.duracionSeg = at(p,2).toInt();
        a.peso        = at(p,3).toInt(); // usaremos 'peso' como prioridad/ponderación
        aa.n++;
    }
    return true;
}
