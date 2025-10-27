#include "CargasUsuarios.h"
#include <QFile>
#include <QTextStream>

static inline QString at(const QStringList& v, int i){
    return (i>=0 && i<v.size())? v[i].trimmed() : QString();
}

bool cargarUsuarios(const char* ruta, UsuarioArr& ua){
    ua.n=0;
    QFile f(QString::fromUtf8(ruta));
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream in(&f);
    while(!in.atEnd() && ua.n<256){
        QString line = in.readLine().trimmed();
        if(line.isEmpty()) continue;
        QStringList parts = line.split('|');
        if(parts.size()<4) continue;

        Usuario& u = ua.items[ua.n];
        u.setNickname(at(parts,0));
        u.setPlanPremium(at(parts,1).toLower()=="premium");
        u.setCiudad(at(parts,2));
        u.setPais(at(parts,3));
        // si quieres, usa setId para guardar un correlativo
        u.setId(ua.n+1);

        ua.n++;
    }
    return true;
}

bool loginPorNick(const UsuarioArr& ua, const char* nick, Usuario& u){
    const QString qn = QString::fromUtf8(nick);
    for(int i=0;i<ua.n; ++i){
        if(ua.items[i].getNickname()==qn){ u=ua.items[i]; return true; }
    }
    return false;
}
