#include "mainwindow.h"
#include "options.h"
#include "joueur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Options w;
    w.show();

    return a.exec();
}
