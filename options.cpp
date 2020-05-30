#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    QIntValidator *validateur = new QIntValidator;          // L'option pour choisir le nombre de points d'une partie n'autorise qu'un nombre entre 1 et 99
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



void Options::boutonOK_onClicked()          // Slot du bouton OK, la partie est créée, le nombre de sets et le nombe de points par sets sont enregistrés.
{                                           // Les joueurs seront créés plus tard, leur nom est stocké dans la table des scores en attendant.
    if (ui->groupSet->checkedButton() && ui->groupPoint->checkedButton() && (ui->groupPoint->checkedId() != -4 || ui->lineEditAutre->text() != ""))
    {
        MainWindow *partie = new MainWindow;
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

void Options::boutonAnnuler_onClicked()         // Slot du bouton annuler
{
    this->close();
}

void Options::lineEditAutre_onToggled(bool checked)         // Slot du bouton autre dans le menu nombre de points
{                                                           // il rend le lineedit disponible pour écrire le nombre de points
    if (checked)
        ui->lineEditAutre->setEnabled(true);

    else
        ui->lineEditAutre->setEnabled(false);
}

