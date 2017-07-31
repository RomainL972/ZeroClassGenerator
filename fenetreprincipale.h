#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QtWidgets>
#include "fenetregeneree.h"

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    FenetrePrincipale();

public slots:
    void genererFenetre();
    void enableHeader(bool checked);
    void changerHeader(QString nouveauNom);

private:
    QGroupBox *m_commentaires;
    QLineEdit *m_nom;
    QLineEdit *m_mere;
    QCheckBox *m_proteger;
    QCheckBox *m_constructeur;
    QCheckBox *m_destructeur;
    QLineEdit *m_headerGuard;
    QLineEdit *m_auteur;
    QDateEdit *m_date;
    QTextEdit *m_role;
    QPushButton *m_generer;
    QPushButton *m_quitter;
//    QPushButton *m_ajouterAttribut;
//    QLineEdit *m_attributNom;
//    QLineEdit *m_attributPrefixe;
//    QListWidget *m_listeAttributs;
};

#endif // FENETREPRINCIPALE_H
