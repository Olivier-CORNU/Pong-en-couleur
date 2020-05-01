#include "mainwindow.h"
#include "ui_mainwindow.h"

Joueur *joueur1;
Joueur *joueur2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(40);
    connect(ui->action_Quitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Recommencer_une_partie, SIGNAL(triggered()), this, SLOT(RecommencerUnePartie_onClicked()));

    joueur1 = new Joueur;
    joueur2 = new Joueur;
    ui->espaceGaucheLabel->changeSize((width() - 100) / 2, 0);
    ui->espaceDroitLabel->changeSize((width() - 100) / 2, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter boule(this);
    boule.setBrush(QBrush(Qt::blue));
    boule.setBrush(Qt::blue);
    boule.setPen((Qt::blue));
    boule.drawEllipse(abscisse, ordonnee, 20, 20);

    QPainter raquette1(this);
    raquette1.setBrush(QBrush(QColor(221, 20, 212)));
    raquette1.setBrush(QColor(221, 20, 212));
    raquette1.setPen(QColor(221, 20, 212));
    raquette1.drawRect(50, ordonneeRectangle1, 20, 50);

    QPainter raquette2(this);
    raquette2.setBrush(QBrush(QColor(221, 20, 212)));
    raquette2.setBrush(QColor(221, 20, 212));
    raquette2.setPen(QColor(221, 20, 212));
    raquette2.drawRect(width() - 50, ordonneeRectangle2, 20, 50);

    if (avancee && point)
    {
        abscisse += abscisseTir;

        if (abscisse >= width() - 70 && abscisse <= width() - 62 && ordonnee >= ordonneeRectangle2 && ordonnee <= ordonneeRectangle2 + 50)
        {
            avancee = false;
            ace = false;
            angleDeTir();
        }

        if (abscisse >= width())
        {
            //avancee = false;
            pointPourJoueur1();
        }
    }

    else if (!avancee && point)
    {
        abscisse -= abscisseTir;

        if (abscisse <= 70 && abscisse >= 62 && ordonnee >= ordonneeRectangle1 && ordonnee <= ordonneeRectangle1 + 50)
        {
            avancee = true;
            ace = false;
            angleDeTir();
        }

        if (abscisse <= 0)
        {
            //avancee = true;
            //scoreJoueur2 += 1;
            pointPourJoueur2();
        }
    }

    if (descente && point)
    {
        ordonnee += ordonneeTir;
        if (ordonnee >= height())
            descente = false;
    }

    else if (!descente && point)
    {
        ordonnee -= ordonneeTir;
        if (ordonnee <= 0)
        descente = true;
    }

    QPainter tableau(this);         // Quadrillage du tableau des scores
    tableau.setPen(Qt::red);
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 0).bottomLeft().x() - ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 0).bottomLeft().y() - ui->tableauGridLayout->verticalSpacing(),
                   ui->tableauGridLayout->cellRect(1, 5).bottomRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 5).bottomRight().y() - ui->tableauGridLayout->verticalSpacing());
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 0).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 0).topRight().y() - 3 * ui->tableauGridLayout->verticalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 0).bottomRight().x() - ui->tableauGridLayout->cellRect(1, 0).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 0).bottomRight().y() - ui->tableauGridLayout->cellRect(1, 0).topRight().y() - ui->tableauGridLayout->verticalSpacing() / 2);
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 1).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 1).topRight().y() - 3 * ui->tableauGridLayout->verticalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 1).bottomRight().x() - ui->tableauGridLayout->cellRect(1, 1).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 1).bottomRight().y() - ui->tableauGridLayout->cellRect(1, 1).topRight().y() - ui->tableauGridLayout->verticalSpacing() / 2);
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 2).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 2).topRight().y() - 3 * ui->tableauGridLayout->verticalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 2).bottomRight().x() - ui->tableauGridLayout->cellRect(1, 2).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 2).bottomRight().y() - ui->tableauGridLayout->cellRect(1, 2).topRight().y() - ui->tableauGridLayout->verticalSpacing() / 2);
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 3).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 3).topRight().y() - 3 * ui->tableauGridLayout->verticalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 3).bottomRight().x() - ui->tableauGridLayout->cellRect(1, 3).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 3).bottomRight().y() - ui->tableauGridLayout->cellRect(1, 3).topRight().y() - ui->tableauGridLayout->verticalSpacing() / 2);
    tableau.drawLine(ui->tableauGridLayout->cellRect(1, 4).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   ui->tableauGridLayout->cellRect(1, 4).topRight().y() - 3 * ui->tableauGridLayout->verticalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 4).bottomRight().x() - ui->tableauGridLayout->cellRect(1, 4).topRight().x() + ui->tableauGridLayout->horizontalSpacing() / 2,
                   2 * ui->tableauGridLayout->cellRect(1, 4).bottomRight().y() - ui->tableauGridLayout->cellRect(1, 4).topRight().y() - ui->tableauGridLayout->verticalSpacing() / 2);
}

void MainWindow::keyPressEvent(QKeyEvent *event)        // Activer les touches du clavier
{
    if (event->key() == Qt::Key_A)
        ordonneeRectangle1 -= 20;

    if (event->key() == Qt::Key_Q)
        ordonneeRectangle1 += 20;

    if (event->key() == Qt::Key_Up)
        ordonneeRectangle2 -= 20;

    if (event->key() == Qt::Key_Down)
        ordonneeRectangle2 += 20;

    if (event->key() == Qt::Key_Space)
        service();
}

void MainWindow::setJoueur1(QString nom)
{
    ui->joueur1label->setText(nom);
}

void MainWindow::setJoueur2(QString nom)
{
    ui->joueur2label->setText(nom);
}

void MainWindow::setNbSets(int sets)
{
    nbSets = sets;
}

void MainWindow::setNbPoints(int points)
{
    nbPoints = points;
    qDebug() << nbPoints;
}

void MainWindow::pointPourJoueur1()
{
    point = false;

    for (int i = 0; i < setEnCours; i++)
        score[i] = joueur1->getScore(i+1);

    score[setEnCours - 1]++;
    switch (setEnCours)
    {
        case 1 : ui->joueur1set1label->setNum(score[0]);
            break;

        case 2 : ui->joueur1set2label->setNum(score[1]);
            break;

        case 3 : ui->joueur1set3label->setNum(score[2]);
            break;

        case 4 : ui->joueur1set4label->setNum(score[3]);
            break;

        case 5 : ui->joueur1set5label->setNum(score[4]);
            break;

        default: break;
    }
    joueur1->setScore(score);
    if (joueur1->getScore(setEnCours) >= nbPoints && joueur1->getScore(setEnCours) > (joueur2->getScore(setEnCours) + 1))
    {
        joueur1->setSetsRemportes(joueur1->getSetsRemportes() + 1);
        setEnCours++;
    }

    qDebug() <<"points par set : " << nbPoints << endl << "points pour joueur1 : " << joueur1->getScore(setEnCours) << endl << "Set pour joueur1 : "  << joueur1->getSetsRemportes() << endl << "set : " << setEnCours;
    if (joueur1->getSetsRemportes() == nbSets)
    {
        joueur1->setVictoire(true);
        qDebug() << "1 vainqueur" << endl << endl;
    }

    if (ace)
    {
        int i = QRandomGenerator::global()->bounded(0, 2);
        ui->messageCentral->setText(messageDAce[i]);
    }

    else
    {
        int i = QRandomGenerator::global()->bounded(0, 4);
        ui->messageCentral->setText(messageDePoints[i]);
    }
    sleep_for(milliseconds(2000));
    ui->messageCentral->setText("Point pour " + joueur1->getNom());
    sleep_for(milliseconds(2000));

    if (servicePour() == "joueur1")
        ui->messageCentral->setText("Service pour " + joueur1->getNom());

    else
        ui->messageCentral->setText("Service pour " + joueur2->getNom());
}

void MainWindow::pointPourJoueur2()
{
    point = false;

    for (int i = 0; i <= setEnCours; i++)
        score[i] = joueur2->getScore(i+1);

    score[setEnCours - 1]++;
    switch (setEnCours)
    {
        case 1 : ui->joueur2set1label->setNum(score[0]);
            break;

        case 2 : ui->joueur2set2label->setNum(score[1]);
            break;

        case 3 : ui->joueur2set3label->setNum(score[2]);
            break;

        case 4 : ui->joueur2set4label->setNum(score[3]);
            break;

        case 5 : ui->joueur2set5label->setNum(score[4]);
            break;
    }
    joueur2->setScore(score);
    if (joueur2->getScore(setEnCours) >= nbPoints && joueur2->getScore(setEnCours) > (joueur1->getScore(setEnCours) + 1))
    {
        joueur2->setSetsRemportes(joueur2->getSetsRemportes() + 1);
        setEnCours++;
    }

    qDebug() <<"points par set : " << nbPoints << endl << "points pour joueur2 : " << joueur2->getScore(setEnCours) << endl << "Set pour joueur2 : "  << joueur2->getSetsRemportes() << endl << "set : " << setEnCours;
    if (joueur2->getSetsRemportes() == nbSets)
    {
        joueur2->setVictoire(true);
        qDebug() << "2 vainqueur" << endl << endl;
    }

    if (ace)
    {
        int i = QRandomGenerator::global()->bounded(0, 2);
        ui->messageCentral->setText(messageDAce[i]);
        qDebug () << "ace" << messageDAce[i];
    }

    else
    {
        int i = QRandomGenerator::global()->bounded(0, 5);
        ui->messageCentral->setText(messageDePoints[i]);
        qDebug () << "pas ace" << messageDePoints[i];
    }


    sleep_for (milliseconds(2000));//QTest::qWait(2000);
    ui->messageCentral->setText("Point pour " + joueur2->getNom());
    sleep_for(milliseconds(2000));//QTest::qWait(2000);

    if (servicePour() == "joueur1")
        ui->messageCentral->setText("Service pour " + joueur1->getNom());

    else
        ui->messageCentral->setText("Service pour " + joueur2->getNom());
}

void MainWindow::RecommencerUnePartie_onClicked()
{
    Options *nouvelleOption = new Options;
    nouvelleOption->show();
    this->close();
}

QString MainWindow::servicePour()
{
    int i;
    //qDebug() << "Entrée dans servicePour()";
    if (debut)
    {
        qDebug() << "Condition 1";
        i = QRandomGenerator::global()->bounded(1,3);
        if (i == 1)
        {
            toss = "joueur1";
            debut = false;
            return "joueur1";

        }
        else
        {
            toss = "joueur2";
            debut = false;
            return "joueur2";
        }

    }

    else if (( nbPoints - 1) % 5 == 0 && (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) < 2 * nbPoints - 2)
    {
        qDebug () << "Condition 2";
        if ((joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 0 ||
            (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 1 ||
            (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 2 ||
            (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 3 ||
            (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 4)
            return toss;
        else
        {
            if (toss == "joueur1")
                return "joueur2";
            else
                return "joueur1";
        }
    }

    else
    {
        qDebug () << "Condition 3";
        if ((joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 2 == 0)
        {qDebug () << "Condition 3.1";
            return toss;}
        else
        {
            if (toss == "joueur1")
            {qDebug () << "Condition 3.2.1";
                return "joueur2";}
            else
            {qDebug () << "Condition 3.2.2";
                return "joueur1";}
        }
    }
}

void MainWindow::service()
{
    point = true;
    ace = true;
    //qDebug() << "point = " << point;
    if (servicePour() == "joueur1")
    {
        abscisse = 70;
        ordonnee = ordonneeRectangle1 - 15;
        avancee = true;
    }
    else
    {
        abscisse = width() - 70;
        ordonnee = ordonneeRectangle2 - 15;
        avancee = false;
    }
    int i = QRandomGenerator::global()->bounded(0,2);
    if (i == 0)
        descente = false;
    else
        descente = true;
    //qDebug() << "Descente : " << descente;
}

void MainWindow::angleDeTir()
{
    if (avancee)
        angle = (( ordonnee - ordonneeRectangle1 ) / 275 * 5 * PI / 3) - 5 * PI / 6;

    else
        angle = (( ordonnee - ordonneeRectangle2 ) / 275 * 5 * PI / 3) - 5 * PI / 6;

    abscisseTir = 10 * cos (angle);
    ordonneeTir = -10 * sin (angle);
}
