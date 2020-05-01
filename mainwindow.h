#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "options.h"
#include "joueur.h"

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QLayout>
#include <QRandomGenerator>
#include <chrono>
#include <thread>
#include <QtTest/QTest>
#define PI          3.14159265358979323846264338327950288419716939937510582

using namespace std::chrono;
using namespace std::this_thread;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setJoueur1(QString nom);
    void setJoueur2(QString nom);
    void setNbSets(int sets);
    void setNbPoints(int points);
    void pointPourJoueur1();
    void pointPourJoueur2();
    void service();
    void angleDeTir();
    QString servicePour();

public slots:
    void RecommencerUnePartie_onClicked();

private:
    Ui::MainWindow *ui;
    QTimer *updateTimer;
    QString nomJoueur1;
    QString nomJoueur2;
    QString toss;
    QString messageDePoints[5] =
    {
        "Bien joué !",
        "Joli coup !",
        "Quel point !",
        "Impressionnnant !",
        "Bravo !",
    };
    QString messageDAce[2] =
    {
        "C'est un ace !",
        "Quel ace !"
    };
    QRandomGenerator *numeroMessage;
    bool avancee = true;
    bool descente = true;
    bool ace = true;
    bool point = false;
    bool debut = true;
    double angle;
    int abscisse = 0;
    int ordonnee = 0;
    double abscisseTir;
    double ordonneeTir;
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    int ordonneeRectangle1 = 275;
    int ordonneeRectangle2 = 275;
    int nbSets;
    int nbPoints;
    int setEnCours = 1;
    int score[5] = {0,0,0,0,0};
    int set[2] = {0,0};
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
