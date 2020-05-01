#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    QIntValidator *validateur = new QIntValidator;
    validateur->setRange(1, 99);
    ui->lineEditAutre->setValidator(validateur);

    connect(ui->boutonOK, SIGNAL(clicked()), this, SLOT(boutonOK_onClicked()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), this, SLOT(boutonAnnuler_onClicked()));
    connect(ui->radioButtonAutre, SIGNAL(toggled(bool)), this, SLOT(lineEditAutre_onToggled(bool)));
}

Options::~Options()
{
    delete ui;
}



void Options::boutonOK_onClicked()
{
    if (ui->groupSet->checkedButton() && ui->groupPoint->checkedButton() && (ui->groupPoint->checkedId() != -4 || ui->lineEditAutre->text() != ""))
    {
        MainWindow *partie = new MainWindow;
        Joueur *joueur1 = new Joueur;
        Joueur *joueur2 = new Joueur;
        joueur1->setNom(ui->lineEditJoueur1->text());
        joueur2->setNom(ui->lineEditJoueur2->text());
        partie->setJoueur1(ui->lineEditJoueur1->text());
        partie->setJoueur2(ui->lineEditJoueur2->text());

        if (ui->groupSet->checkedId() == -2)
            partie->setNbSets(1);

        if (ui->groupSet->checkedId() == -3)
            partie->setNbSets(2);

        if (ui->groupSet->checkedId() == -4)
            partie->setNbSets(3);

        if (ui->groupPoint->checkedId() == -2)
            partie->setNbPoints(11);

        if (ui->groupPoint->checkedId() == -3)
            partie->setNbPoints(21);

        if (ui->groupPoint->checkedId() == -4)
            partie->setNbPoints(ui->lineEditAutre->text().toInt());

        partie->show();
        this->close();
    }
}

void Options::boutonAnnuler_onClicked()
{
    this->close();
}

void Options::lineEditAutre_onToggled(bool checked)
{
    if (checked)
        ui->lineEditAutre->setEnabled(true);

    else
        ui->lineEditAutre->setEnabled(false);
}

