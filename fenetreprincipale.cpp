#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout();
    QFormLayout *layoutDefinition = new QFormLayout();
    QFormLayout *layoutOptions = new QFormLayout();
//    QVBoxLayout *layoutAttributs = new QVBoxLayout();
    QFormLayout *layoutCommentaires = new QFormLayout();
    QHBoxLayout *layoutBoutons = new QHBoxLayout();
//    QFormLayout *layoutAjouterAttribut = new QFormLayout();

    QGroupBox *definition = new QGroupBox(tr("Définition de la classe"));
    QGroupBox *options = new QGroupBox(tr("Options"));
//    QGroupBox *attributs = new QGroupBox(tr("Attributs"));
    m_commentaires = new QGroupBox(tr("Commentaires"));
    m_commentaires->setCheckable(true);

//    m_listeAttributs = new QListWidget();

    m_nom = new QLineEdit();
    m_mere = new QLineEdit();

    m_proteger = new QCheckBox(tr("Protéger le &header contre les inclusions multiples"));
    m_constructeur = new QCheckBox(tr("Générer un &constructeur par défaut"));
    m_destructeur = new QCheckBox(tr("Générer un &destructeur"));
    m_headerGuard = new QLineEdit();
    m_proteger->setChecked(true);
    m_constructeur->setChecked(true);

//    m_attributPrefixe = new QLineEdit();
//    m_attributNom = new QLineEdit();
//    m_ajouterAttribut = new QPushButton("Ajouter");

    m_auteur = new QLineEdit();
    m_date = new QDateEdit(QDate::currentDate());
    m_role = new QTextEdit();

    m_generer = new QPushButton(tr("Générer !"));
    m_quitter = new QPushButton(("Quitter"));

    layoutDefinition->addRow(tr("&Nom :"), m_nom);
    layoutDefinition->addRow(tr("Classe &mère :"), m_mere);
    definition->setLayout(layoutDefinition);

    layoutOptions->addRow(m_proteger);
    layoutOptions->addRow(m_constructeur);
    layoutOptions->addRow(m_destructeur);
    layoutOptions->addRow(tr("Header :"), m_headerGuard);
    options->setLayout(layoutOptions);

//    layoutAjouterAttribut->addRow(tr("Préfixe de l'attribut :"), m_attributPrefixe);
//    layoutAjouterAttribut->addRow(tr("Nom de l'attribut :"), m_attributNom);
//    layoutAjouterAttribut->addRow(m_ajouterAttribut);

//    layoutAttributs->addLayout(layoutAjouterAttribut);
//    layoutAttributs->addWidget(m_listeAttributs);
//    attributs->setLayout(layoutAttributs);
//    m_listeAttributs->set

    layoutCommentaires->addRow(tr("Auteur :"), m_auteur);
    layoutCommentaires->addRow(tr("Da&te de création :"), m_date);
    layoutCommentaires->addRow(tr("&Rôle de la classe :"), m_role);
    m_commentaires->setLayout(layoutCommentaires);

    layoutBoutons->addWidget(m_generer, 10, Qt::AlignRight);
    layoutBoutons->addWidget(m_quitter, 0, Qt::AlignRight);

    layoutPrincipal->addWidget(definition);
    layoutPrincipal->addWidget(options);
//    layoutPrincipal->addWidget(attributs);
    layoutPrincipal->addWidget(m_commentaires);
    layoutPrincipal->addLayout(layoutBoutons);

    this->setLayout(layoutPrincipal);

    connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_generer, SIGNAL(clicked()), this, SLOT(genererFenetre()));
    connect(m_proteger, SIGNAL(toggled(bool)), this, SLOT(enableHeader(bool)));
    connect(m_nom, SIGNAL(textChanged(QString)), this, SLOT(changerHeader(QString)));
//    connect(m_ajouterAttribut, SIGNAL(clicked()), this, SLOT(ajouterAttribut()));
}

void FenetrePrincipale::genererFenetre()
{
    QString texte;
    QString titreErreur(tr("Données incorrectes"));
    if(m_nom->text().isEmpty()) {
        QMessageBox::warning(this, titreErreur, tr("Vous devez préciser le nom de la classe !"));
        return;
    }
    if(m_headerGuard->isEnabled() && m_headerGuard->text().isEmpty()) {
        QMessageBox::warning(this, titreErreur, tr("Vous devez précisez le header guard"));
    }
    if(m_commentaires->isChecked()) {
        if(m_auteur->text().isEmpty()) {
            QMessageBox::warning(this, titreErreur, tr("Vous devez entrer l'auteur"));
            return;
        }
        if(m_role->toPlainText().isEmpty()) {
            QMessageBox::warning(this, titreErreur, tr("Vous devez entrer le rôle"));
        }
        texte += "/*\n" + tr("Auteur : ") + m_auteur->text() + "\n";
        texte += tr("Date de création : ") + m_date->date().toString() + "\n\n";
        texte += tr("Rôle :") +"\n" + m_role->toPlainText() + "\n*/\n\n";
    }
    if(m_proteger->isChecked()) {
        texte += "#ifndef " + m_headerGuard->text() + "\n#define " + m_headerGuard->text() + "\n\n";
    }
    texte += "Class " + m_nom->text();
    if(!(m_mere->text().isEmpty())) {
        texte += " : public " + m_mere->text();
    }
    texte += "\n{\n    public:\n";
    if(m_constructeur->isChecked()) {
        texte += "        " + m_nom->text() + "();\n";
    }
    if(m_destructeur->isChecked()) {
        texte += "        ~" + m_nom->text() + "();\n";
    }
    texte += "\n\n    protected:\n\n\n    private:\n\n\n};";
    if(m_proteger->isChecked()) {
        texte += "\n\n#endif";
    }
    FenetreGeneree(texte).exec();
}

void FenetrePrincipale::enableHeader(bool checked)
{
    m_headerGuard->setEnabled(checked);
}

void FenetrePrincipale::changerHeader(QString nouveauNom)
{
    m_headerGuard->setText("HEADER_"+nouveauNom.toUpper());
}

//void FenetrePrincipale::ajouterAttribut()
//{
//    m_listeAttributs->addItem(new QListWidgetItem(m_attributPrefixe->text() + " " + m_attributNom->text() + ";"));
//}
