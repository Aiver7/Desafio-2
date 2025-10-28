#include <QCoreApplication>
#include <QTextStream>
#include "ClasePrincipal.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream in(stdin), out(stdout);
    ClasePrincipal cp(in, out);
    if(!cp.init()) return 0;
    cp.run();
    return 0;
}
