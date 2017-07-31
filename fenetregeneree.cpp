#include "fenetregeneree.h"

FenetreGeneree::FenetreGeneree(QString texte) : QDialog()
{
    QTextEdit *conteneur = new QTextEdit();
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *bouton = new QPushButton(tr("Fermer"));

    conteneur->setReadOnly(true);
    conteneur->setText(texte);
    layout->addWidget(conteneur);
    layout->addWidget(bouton);
    this->setLayout(layout);
    conteneur->setFont(QFont("Courrier"));

    QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(close()));
}
