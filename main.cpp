#include "pageprincipal.h"

#include <QApplication>

// Point d'entrée de l'application Qt
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pageprincipal w;
    w.show();
    return a.exec();
}
