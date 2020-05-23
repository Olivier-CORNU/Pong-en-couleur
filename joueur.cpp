#include "joueur.h"

#include <QApplication>


Joueur::Joueur(){}

Joueur::~Joueur(){}

QString Joueur::getNom()        // getter du nom du joueur
{
    return nom;
}

void Joueur::setNom(QString nouveauNom)         // setter du nom du joueur
{
    nom = nouveauNom;
}

int Joueur::getScore(int set)       // getter du score du set en cours du joueur
{
    return score[set - 1];
}

void Joueur::setScore(int nouveauScore[5])          // setter du score du joueur
{
    for (int i = 0; i <= 4; i++)
         score[i] = nouveauScore[i];
}

int Joueur::getSetsRemportes()          // getter du nombre de sets remportés par le joueur
{
    return setsRemportes;
}

void Joueur::setSetsRemportes(int nouveauxSets)         // setter du nombre de sets remportés par le joueur
{
    setsRemportes = nouveauxSets;
}

bool Joueur::getVictoire()          // getter booléen : le joueur a-t-il gagné
{
    return (victoire);
}

void Joueur::setVictoire(bool gagne)            // setter de victoire du joueur
{
    victoire = gagne;
}

bool Joueur::getDernierpoint()          // getter booléen : le joueur a-t-il remporté le point précédent
{
    return (dernierPoint);
}

void Joueur::setDernierPoint(bool point)            // setter de réussite du point précédent du joueur
{
    dernierPoint = point;
}
