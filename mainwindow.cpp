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
    raquette1.drawRect(50, ordonneeRectangle1, 20, longueurRectangle);

    QPainter raquette2(this);
    raquette2.setBrush(QBrush(QColor(221, 20, 212)));
    raquette2.setBrush(QColor(221, 20, 212));
    raquette2.setPen(QColor(221, 20, 212));
    raquette2.drawRect(width() - 50, ordonneeRectangle2, 20, longueurRectangle);

    if (avancee && point)
    {
        abscisse += abscisseTir;

        if (abscisse >= width() - 70 && abscisse <= width() - 62 && ordonnee >= ordonneeRectangle2 && ordonnee <= ordonneeRectangle2 + longueurRectangle)
        {
            avancee = false;
            descente = false;
            ace = false;
            angleDeTir();
        }

        if (abscisse >= width())
            pointPourJoueur1();
    }

    else if (!avancee && point)
    {
        abscisse -= abscisseTir;

        if (abscisse <= 70 && abscisse >= 62 && ordonnee >= ordonneeRectangle1 && ordonnee <= ordonneeRectangle1 + longueurRectangle)
        {
            avancee = true;
            descente = false;
            ace = false;
            angleDeTir();
        }

        if (abscisse <= 0)
            pointPourJoueur2();
    }

    if (descente && point)
    {
        ordonnee += ordonneeTir;
        if (ordonnee >= height() || ordonnee <= 0)
            descente = false;
    }

    else if (!descente && point)
    {
        ordonnee -= ordonneeTir;
        if (ordonnee <= 0 || ordonnee >= height())
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

    if (!point && !debut)
        entrePoint();

    if (debut)
    {
        if (servicePour() == "joueur1")
            ui->messageCentral->setText("Service pour " + joueur1->getNom());

        else
            ui->messageCentral->setText("Service pour " + joueur2->getNom());
    }
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

    if (event->key() == Qt::Key_Enter)
        recommencerLaMemePartie();

    if (event->key() == Qt::Key_Return)
        recommencerLaMemePartie();
}

void MainWindow::setJoueur1(QString nom)
{
    ui->joueur1label->setText(nom);
    joueur1->setNom(nom);
}

void MainWindow::setJoueur2(QString nom)
{
    ui->joueur2label->setText(nom);
    joueur2->setNom(nom);
}

void MainWindow::setNbSets(int sets)
{
    nbSets = sets;
}

void MainWindow::setNbPoints(int points)
{
    nbPoints = points;
}

void MainWindow::pointPourJoueur1()
{
    point = false;
    joueur1->setDernierPoint(true);
    joueur2->setDernierPoint(false);

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

    if (joueur1->getSetsRemportes() == nbSets)
        joueur1->setVictoire(true);
}

void MainWindow::pointPourJoueur2()
{
    point = false;
    joueur1->setDernierPoint(false);
    joueur2->setDernierPoint(true);

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

    if (joueur2->getSetsRemportes() == nbSets)
        joueur2->setVictoire(true);
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
    if (debut)
    {
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
        if ((joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 2 == 0)
            return toss;

        else
        {
            if (toss == "joueur1")
                return "joueur2";

            else
                return "joueur1";
        }
    }
}

void MainWindow::service()
{
    point = true;
    ace = true;
    periodeEntrePoint = 0;
    ui->messageCentral->setText("");
    angleDeTir();
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
}

void MainWindow::angleDeTir()
{
    if (ace)
        angle = QRandomGenerator::global()->bounded(2 * PI / 3) - PI / 3;

    else
    {
        if (avancee)
            angle = (( ordonnee - ordonneeRectangle1 ) / longueurRectangle * 2 * PI / 3) - PI / 3;

        else
            angle = (( ordonnee - ordonneeRectangle2 ) / longueurRectangle * 2 * PI / 3) - PI / 3;
    }

    abscisseTir = 10 * cos (angle);
    ordonneeTir = -10 * sin (angle);
}

void MainWindow::entrePoint()
{
    periodeEntrePoint++;

    if (periodeEntrePoint == 1)
    {
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
    }

    if (periodeEntrePoint == 51)
    {
        if (joueur1->getDernierpoint() && !joueur2->getDernierpoint())
            ui->messageCentral->setText("Point pour " + joueur1->getNom());

        else
            ui->messageCentral->setText("Point pour " + joueur2->getNom());
    }

    if (periodeEntrePoint == 101 && !joueur1->getVictoire() && !joueur2->getVictoire())
    {
        if (servicePour() == "joueur1")
            ui->messageCentral->setText("Service pour " + joueur1->getNom());

        else
            ui->messageCentral->setText("Service pour " + joueur2->getNom());
    }

    if (periodeEntrePoint >= 101 && (joueur1->getVictoire() || joueur2->getVictoire()))
        finDePartie();
}

void MainWindow::finDePartie()
{
    if (periodeEntrePoint == 101 && joueur1->getVictoire())
        ui->messageCentral->setText("Jeu, set et match " + joueur1->getNom() + " !");

    if (periodeEntrePoint == 101 && joueur2->getVictoire())
        ui->messageCentral->setText("Jeu, set et match " + joueur2->getNom() + " !");

    if (periodeEntrePoint == 151)
        ui->messageCentral->setText("Entree pour recommencer.");
}

void MainWindow::recommencerLaMemePartie()
{
    debut = true;

    for (int i = 0; i <= 4; i++)
        score[i] = 0;

    joueur1->setScore(score);
    joueur2->setScore(score);

    joueur1->setSetsRemportes(0);
    joueur2->setSetsRemportes(0);

    joueur1->setVictoire(false);
    joueur2->setVictoire(false);

    ui->joueur1set1label->setNum(0);
    ui->joueur1set2label->setNum(0);
    ui->joueur1set3label->setNum(0);
    ui->joueur1set4label->setNum(0);
    ui->joueur1set5label->setNum(0);
    ui->joueur2set1label->setNum(0);
    ui->joueur2set2label->setNum(0);
    ui->joueur2set3label->setNum(0);
    ui->joueur2set4label->setNum(0);
    ui->joueur2set5label->setNum(0);

    setEnCours = 1;
}
