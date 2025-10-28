#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

class Usuario {
public:
    enum TipoPlan { ESTANDAR=0, PREMIUM=1 };

private:
    qint64  idUsuario{0};
    QString nickname;
    TipoPlan plan{ESTANDAR};
    QString ciudad;
    QString pais;

public:
    void setId(qint64 v){ idUsuario=v; }
    qint64 id() const { return idUsuario; }
    void setNickname(const QString& n){ nickname=n; }
    QString getNickname() const { return nickname; }
    void setPlanPremium(bool p){ plan = p? PREMIUM : ESTANDAR; }
    bool esPremium() const { return plan==PREMIUM; }
    void setCiudad(const QString& c){ ciudad=c; }
    void setPais(const QString& p){ pais=p; }
    QString getCiudad() const { return ciudad; }
    QString getPais() const { return pais; }
};

#endif
