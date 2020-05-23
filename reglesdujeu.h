#ifndef REGLESDUJEU_H
#define REGLESDUJEU_H

#include <QDialog>

namespace Ui {
class ReglesDuJeu;
}

class ReglesDuJeu : public QDialog
{
    Q_OBJECT

public:
    explicit ReglesDuJeu(QWidget *parent = nullptr);
    ~ReglesDuJeu();

private:
    Ui::ReglesDuJeu *ui;
};

#endif // REGLESDUJEU_H
