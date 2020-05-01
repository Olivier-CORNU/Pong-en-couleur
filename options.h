#ifndef OPTIONS_H
#define OPTIONS_H

#include "mainwindow.h"
#include "joueur.h"

#include <QDialog>
#include <QAbstractButton>
#include <QValidator>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();


public slots:
    void boutonOK_onClicked();
    void boutonAnnuler_onClicked();
    void lineEditAutre_onToggled(bool checked);

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
