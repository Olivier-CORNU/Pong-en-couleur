#include "apropos.h"
#include "ui_apropos.h"

APropos::APropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::APropos)
{
    ui->setupUi(this);
}

APropos::~APropos()
{
    delete ui;
}
