#include "mainwindow.h"
#include "ui_mainwindow.h"

Joueur *joueur1;
Joueur *joueur2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTimer = new QTimer(this);         // QTimer pour rappeler la lecture du constructeur toutes les 40 ms
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(40);
    connect(ui->action_Recommencer_une_partie, SIGNAL(triggered()), this, SLOT(RecommencerUnePartie_onClicked()));
    connect(ui->action_Regles_du_jeu, SIGNAL(triggered()), this, SLOT(ReglesDuJeu_onClicked()));
    connect(ui->action_APropos, SIGNAL(triggered()), this, SLOT(APropos_onClicked()));
    connect(ui->action_Quitter, SIGNAL(triggered()), this, SLOT(close()));

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
    QPainter boule(this);           // QPainter de la boule
    boule.setBrush(QBrush(Qt::blue));
    boule.setBrush(Qt::blue);
    boule.setPen((Qt::blue));
    boule.drawEllipse(abscisse, ordonnee, longueurBoule, longueurBoule);

    QPainter raquette1(this);           // QPainter de la raquette du joueur1
    raquette1.setBrush(QBrush(QColor(221, 20, 212)));
    raquette1.setBrush(QColor(221, 20, 212));
    raquette1.setPen(QColor(221, 20, 212));
    raquette1.drawRect(50, ordonneeRectangle1, 20, longueurRectangle);

    QPainter raquette2(this);           // QPainter de la raquette du joueur2
    raquette2.setBrush(QBrush(QColor(221, 20, 212)));
    raquette2.setBrush(QColor(221, 20, 212));
    raquette2.setPen(QColor(221, 20, 212));
    raquette2.drawRect(width() - 50, ordonneeRectangle2, 20, longueurRectangle);

    if (avancee && point)           // si la balle se dirige vers le joueur2
    {
        abscisse += abscisseTir;            // la balle avance sur l'axe des x de abscisseTir

        if (abscisse >= width() - 70 && abscisse <= width() - 62 && ordonnee >= ordonneeRectangle2 && ordonnee <= ordonneeRectangle2 + longueurRectangle)
            // la balle tape dans la raquettedu joueur2
        {
            avancee = false;            // la balle fait demi-tour
            descente = false;
            ace = false;            // Ce n'est pas un ace
            angleDeTir();           // l'angle de tir est recalculé
        }

        if (abscisse >= width())            // la balle est sorti coté joueur 2 : point pour joueur 1
            pointPourJoueur1();
    }

    else if (!avancee && point)         // si la balle se dirige vers le joueur 1
    {
        abscisse -= abscisseTir;            // la balle recule sur l'axe des x de abscisseTir

        if (abscisse <= 70 && abscisse >= 62 && ordonnee >= ordonneeRectangle1 && ordonnee <= ordonneeRectangle1 + longueurRectangle)           // La balle tape dans la raquette du joueur 1
        {
            avancee = true;             // La balle fait demi-tour
            descente = false;
            ace = false;            // Ce n'est pas un ace
            angleDeTir();           // L'angle de tir est recalculé
        }

        if (abscisse <= 0)          // La balle est sortie coté Joueur 1 : point pour Joueur 2
            pointPourJoueur2();
    }

    if (descente && point)
    {
        ordonnee += ordonneeTir;
        if (ordonnee >= height() || ordonnee <= 0)          // Si la balle tape le haut ou le bas de l'écran, son sens est inversé
            descente = false;
    }

    else if (!descente && point)
    {
        ordonnee -= ordonneeTir;
        if (ordonnee <= 0 || ordonnee >= height())          // Si la balle tape le haut ou le bas de l'écran, son sens est inversé
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

    if (!point && !debut)           // A la fin d'un point, la fonction entrepoint() est lancée
        entrePoint();

    if (debut)          // Si la partie n'a pas commencé
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

void MainWindow::setJoueur1(QString nom)            // Setter du nom du Joueur 1
{
    ui->joueur1label->setText(nom);
    joueur1->setNom(nom);
}

void MainWindow::setJoueur2(QString nom)            // Setter du nom du Joueur 2
{
    ui->joueur2label->setText(nom);
    joueur2->setNom(nom);
}

void MainWindow::setNbSets(int sets)            // Setter dunombre de sets maximal dans la partie
{
    nbSets = sets;
}

void MainWindow::setNbPoints(int points)            // Set du nombre de points par set
{
    nbPoints = points;
}

void MainWindow::pointPourJoueur1()         // Fonction pour modifier le score du Joueur 1 après avoir remporté un point
{
    point = false;          // le jeu est arrêté
    joueur1->setDernierPoint(true);         // Le point précédent a été remporté par Joueur 1
    joueur2->setDernierPoint(false);

    for (int i = 0; i < setEnCours; i++)            // Le score du Joueur 1 est récupéré
        score[i] = joueur1->getScore(i+1);

    score[setEnCours - 1]++;            // +1 au set en cours
    switch (setEnCours)         // La table des scores est modifiée pour le set en cours
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
    joueur1->setScore(score);           // Le nouveau score est enregistré dans l'objet Joueur 1
    if (joueur1->getScore(setEnCours) >= nbPoints && joueur1->getScore(setEnCours) > (joueur2->getScore(setEnCours) + 1))           // Si le Joueur 1 a remporté le set
    {
        joueur1->setSetsRemportes(joueur1->getSetsRemportes() + 1);         // nombre de sets pour Joueur 1 +1
        setEnCours++;           // On change de set
    }

    if (joueur1->getSetsRemportes() == nbSets)          // Si le joueur 1 a gagné
        joueur1->setVictoire(true);
}

void MainWindow::pointPourJoueur2()         // Fonction pour modifier le score du Joueur 2 après avoir remporté un point
{
    point = false;          // le jeu est arrêté
    joueur1->setDernierPoint(false);         // Le point précédent a été remporté par Joueur 2
    joueur2->setDernierPoint(true);

    for (int i = 0; i <= setEnCours; i++)            // Le score du Joueur 1 est récupéré
        score[i] = joueur2->getScore(i+1);

    score[setEnCours - 1]++;            // +1 au set en cours
    switch (setEnCours)         // La table des scores est modifiée pour le set en cours
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
    joueur2->setScore(score);           // Le nouveau score est enregistré dans l'objet Joueur 2
    if (joueur2->getScore(setEnCours) >= nbPoints && joueur2->getScore(setEnCours) > (joueur1->getScore(setEnCours) + 1))           // Si le Joueur 2 a remporté le set
    {
        joueur2->setSetsRemportes(joueur2->getSetsRemportes() + 1);         // nombre de sets pour Joueur 2 +1
        setEnCours++;           // On change de set
    }

    if (joueur2->getSetsRemportes() == nbSets)          // Si le joueur 2 a gagné
        joueur2->setVictoire(true);
}

void MainWindow::RecommencerUnePartie_onClicked()           // Slot du menu recommencer une partie
{
    Options *nouvelleOption = new Options;
    nouvelleOption->show();
    this->close();
}

void MainWindow::ReglesDuJeu_onClicked()            // Slot de la règle du jeu
{
    ReglesDuJeu *w = new ReglesDuJeu;
    w->show();
}

void MainWindow::APropos_onClicked()            // Slot de la section A propos
{
    APropos *w = new APropos;
    w->show();
}

QString MainWindow::servicePour()           // Fonction pour désigner qui doit servir
{
    int i;
    if (debut)          // Si la partie commence, le serveur est tiré au sort
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

    else if (( nbPoints - 1) % 5 == 0 && (joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) < 2 * nbPoints - 2)            // Si la partie est en 11, 21, 31...
    {                                                                                                                                   // Le service change tous les 5 points
        if ((joueur1->getScore(setEnCours) + joueur2->getScore(setEnCours)) % 10 == 0 ||                                                // Sauf dans la zone des 2 points d'écart
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

    else            // Dans tous les autres cas, le service change à chaque point
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

void MainWindow::service()          // Fonction du service (appelé par le key_event de la barre espace)
{
    point = true;           // Nous sommes dans la séquence d'un point
    ace = true;         // Tant que la balle n'a pas été retourné, nous la sommes dans la situation de faire un ace
    periodeEntrePoint = 0;          // le compteur de l'entrepoint est remis à 0 pour l'entrepoint suivant
    ui->messageCentral->setText("");            // l'écran central est effacé
    angleDeTir();
    if (servicePour() == "joueur1")         // Si le Joueur 1 doit servir la balle est placée au centre de sa raquette
    {
        abscisse = 70;
        ordonnee = ordonneeRectangle1 + ((longueurRectangle - longueurBoule) / 2);
        avancee = true;
    }
    else            // Si le Joueur 2 doit servir la balle est placée au centre de sa raquette
    {
        abscisse = width() - 70;
        ordonnee = ordonneeRectangle2 + ((longueurRectangle - longueurBoule) / 2);
        avancee = false;
    }
    int i = QRandomGenerator::global()->bounded(0,2);           // la balle va partir aléatoirement en haut ou en bas
    if (i == 0)
        descente = false;
    else
        descente = true;
}

void MainWindow::angleDeTir()           // Fonction qui détermine aléatoirement l'angle de tir du service
{                                       // et calcule l'angle des autres coups en fonction de la position la balle sur la raquette
    if (ace)
        angle = QRandomGenerator::global()->bounded(2 * PI / 3) - PI / 3;

    else
    {
        if (avancee)
            angle = (( ordonnee - ordonneeRectangle1 ) / longueurRectangle * 2 * PI / 3) - PI / 3;

        else
            angle = (( ordonnee - ordonneeRectangle2 ) / longueurRectangle * 2 * PI / 3) - PI / 3;
    }

    abscisseTir = 10 * cos (angle);         // l'angle de tir permet de calculer abscisseTir et ordonneeTir qui sont les mouvements de la balle à chaque rechargement de la page
    ordonneeTir = -10 * sin (angle);
}

void MainWindow::entrePoint()           // Fonction appelée en boucle entre deux points
{
    periodeEntrePoint++;            // Décompte du nombre d'appel de la fonction entre deux points (1 appel toutes les 40 ms)

    if (periodeEntrePoint == 1)         // Au début affichage d'un message de félicitations
    {
        if (ace)            // Message différent si c'est un ace
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

    if (periodeEntrePoint == 51)            // Après 50 appels de la fonction soit 2 s, affichage du joueur qui le point
    {
        if (joueur1->getDernierpoint() && !joueur2->getDernierpoint())
            ui->messageCentral->setText("Point pour " + joueur1->getNom());

        else
            ui->messageCentral->setText("Point pour " + joueur2->getNom());
    }

    if (periodeEntrePoint == 101 && !joueur1->getVictoire() && !joueur2->getVictoire())         // après 100 appels de la fonction soit 4 s, affichage du joueur qui doit servir
    {
        if (servicePour() == "joueur1")
            ui->messageCentral->setText("Service pour " + joueur1->getNom());

        else
            ui->messageCentral->setText("Service pour " + joueur2->getNom());
    }

    if (periodeEntrePoint >= 101 && (joueur1->getVictoire() || joueur2->getVictoire()))         // Si un joueur a gagné, appel de la fonctin finDePartie()
        finDePartie();
}

void MainWindow::finDePartie()          // Fonction qui annonce la fin de partie et le vainqueur
{
    if (periodeEntrePoint == 101 && joueur1->getVictoire())
        ui->messageCentral->setText("Jeu, set et match " + joueur1->getNom() + " !");

    if (periodeEntrePoint == 101 && joueur2->getVictoire())
        ui->messageCentral->setText("Jeu, set et match " + joueur2->getNom() + " !");

    if (periodeEntrePoint == 151)
        ui->messageCentral->setText("Entree pour recommencer.");
}

void MainWindow::recommencerLaMemePartie()          // Fonction qui remet tout à 0 pour recommencer la même partie
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
