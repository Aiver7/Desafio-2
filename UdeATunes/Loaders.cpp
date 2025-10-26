#include "Loaders.h"
#include <QFile>
#include <QTextStream>

static bool split5(const QString& line, QString (&f)[6]){
    int i=0, start=0;
    for (int k=0;k<5 && i<line.size();++i){
        if (line[i]=='|'){ f[k++]=line.mid(start, i-start); start=i+1; }
    }
    f[5]=line.mid(start);
    return true;
}

bool cargarCanciones(const QString& path, CancionArr& out){
    QFile f(path); if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream ts(&f);
    while(!ts.atEnd() && out.n<128){
        QString line = ts.readLine();
        if(line.trimmed().isEmpty()) continue;
        QString a[6]; split5(line, a);
        Cancion c;
        c.id = a[0].toLongLong();
        c.titulo = a[1];
        c.path128 = a[2];
        c.path320 = a[3];
        c.coverPng = a[4];
        c.duracionSeg = a[5].toInt();
        out.items[out.n++] = c;
    }
    return true;
}

bool cargarAnuncios(const QString& path, AnuncioArr& out){
    QFile f(path); if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream ts(&f);
    while(!ts.atEnd() && out.n<64){
        QString line = ts.readLine();
        if(line.trimmed().isEmpty()) continue;
        QStringList parts = line.split('|');
        if(parts.size()<4) continue;
        Anuncio a;
        a.id = parts[0].toLongLong();
        a.mensaje = parts[1];
        a.duracionSeg = parts[2].toInt();
        a.peso = parts[3].toInt();
        out.items[out.n++] = a;
    }
    return true;
}
