#include "joueur.h"

#include <QApplication>


Joueur::Joueur()
{

}

Joueur::~Joueur(){}

QString Joueur::getNom()
{
    return nom;
}

void Joueur::setNom(QString nouveauNom)
{
    nom = nouveauNom;
}

int Joueur::getScore(int set)
{
    return score[set - 1];
}

void Joueur::setScore(int nouveauScore[5])
{
    for (int i = 0; i <= 4; i++)
         score[i] = nouveauScore[i];
}

int Joueur::getSetsRemportes()
{
    return setsRemportes;
}

void Joueur::setSetsRemportes(int nouveauxSets)
{
    setsRemportes = nouveauxSets;
}

bool Joueur::getVictoire()
{
    return (victoire);
}

void Joueur::setVictoire(bool gagne)
{
    victoire = gagne;
}
