#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

class Usuario {
public:
    enum TipoPlan { ESTANDAR=0, PREMIUM=1 };
private:
    qint64 idUsuario{0};
    QString nickname;
    TipoPlan plan{ESTANDAR};
public:
    void setId(qint64 v){ idUsuario=v; }
    qint64 id() const { return idUsuario; }
    void setNickname(const QString& n){ nickname=n; }
    bool esPremium() const { return plan==PREMIUM; }
};
#endif
