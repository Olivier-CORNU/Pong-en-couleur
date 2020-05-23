#include "reglesdujeu.h"
#include "ui_reglesdujeu.h"

ReglesDuJeu::ReglesDuJeu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReglesDuJeu)
{
    ui->setupUi(this);
}

ReglesDuJeu::~ReglesDuJeu()
{
    delete ui;
}
