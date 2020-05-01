#include "mainwindow.h"
#include "options.h"
#include "joueur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.show();
    Options x;
    x.show();

    return a.exec();
}
