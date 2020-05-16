#ifndef JOUEUR_H
#define JOUEUR_H

#include "mainwindow.h"
#include "options.h"

#include <QString>


class Joueur
{
public:
    Joueur();
    ~Joueur();
    QString getNom();
    void setNom(QString nomEntreParUtilisateur);
    int getScore(int set);
    void setScore(int nouveauScore[]);
    int getSetsRemportes();
    void setSetsRemportes(int nouveauxSets);
    bool getVictoire();
    void setVictoire(bool gagne);
    bool getDernierpoint();
    void setDernierPoint(bool point);

private:
    QString nom;
    int score[5] = {0,0,0,0,0};
    int setsRemportes = 0;
    bool victoire = false;
    bool dernierPoint = false;

};

#endif // JOUEUR_H
