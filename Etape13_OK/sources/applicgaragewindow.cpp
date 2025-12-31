#include "../includes/applicgaragewindow.h"
#include "ui_applicgaragewindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <sstream>
#include <iostream>
#include "unistd.h"

#include "../includes/Garage.h"
#include "../includes/OptionException.h"
#include "../includes/PasswordException.h"
using namespace carconfig;

#define IMAGES_DIR "../images/"

ApplicGarageWindow::ApplicGarageWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::ApplicGarageWindow)
{
    ui->setupUi(this);
    ::close(2);

    // Configuration de la table des options (projet en cours)
    ui->tableWidgetOptions->setColumnCount(3);
    ui->tableWidgetOptions->setRowCount(5);
    for (int i=0 ; i<5 ; i++) ui->tableWidgetOptions->setRowHeight(i,10);
    QStringList labelsTableOptions;
    labelsTableOptions << "Code" << "Prix" << "Intitulé";
    ui->tableWidgetOptions->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetOptions->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetOptions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetOptions->horizontalHeader()->setVisible(true);
    ui->tableWidgetOptions->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidgetOptions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetOptions->verticalHeader()->setVisible(false);
    ui->tableWidgetOptions->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des employes (Personnel Garage)
    ui->tableWidgetEmployees->setColumnCount(4);
    ui->tableWidgetEmployees->setRowCount(0);
    QStringList labelsTableEmployes;
    labelsTableEmployes << "Numéro" << "Nom" << "Prénom" << "Fonction";
    ui->tableWidgetEmployees->setHorizontalHeaderLabels(labelsTableEmployes);
    ui->tableWidgetEmployees->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetEmployees->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetEmployees->horizontalHeader()->setVisible(true);
    ui->tableWidgetEmployees->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetEmployees->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetEmployees->verticalHeader()->setVisible(false);
    ui->tableWidgetEmployees->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des clients
    ui->tableWidgetClients->setColumnCount(4);
    ui->tableWidgetClients->setRowCount(0);
    QStringList labelsTableClients;
    labelsTableClients << "Numéro" << "Nom" << "Prénom" << "GSM";
    ui->tableWidgetClients->setHorizontalHeaderLabels(labelsTableClients);
    ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetClients->horizontalHeader()->setVisible(true);
    ui->tableWidgetClients->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetClients->verticalHeader()->setVisible(false);
    ui->tableWidgetClients->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des contrats
    ui->tableWidgetContracts->setColumnCount(4);
    ui->tableWidgetContracts->setRowCount(0);
    QStringList labelsTableContrats;
    labelsTableContrats << "Numéro" << "Vendeur" << "Client" << "Voiture";
    ui->tableWidgetContracts->setHorizontalHeaderLabels(labelsTableContrats);
    ui->tableWidgetContracts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContracts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContracts->horizontalHeader()->setVisible(true);
    ui->tableWidgetContracts->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetContracts->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetContracts->verticalHeader()->setVisible(false);
    ui->tableWidgetContracts->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Importation des modeles (étape 10)
    try {
        Garage::getInstance().importModelsFromCsv("../CSVs/models.csv");
        
        // Remplir la combobox des modèles
        for (int i = 0; i < 100; i++) {
            Model m = Garage::getInstance().getModel(i);
            if (string(m.getName()) != "default") {
                addAvailableModel(m.getName(), m.getBasePrice());
            } else {
                break;
            }
        }
    } catch(...) {
        cout << "Erreur import modèles" << endl;
    }

    // Importation des options (étape 10)
    try {
        Garage::getInstance().importOptionsFromCsv("../CSVs/options.csv");
        
        // Remplir la combobox des options
        for (int i = 0; i < 100; i++) {
            Option o = Garage::getInstance().getOption(i);
            if (o.getCode() != "") {
                addAvailableOption(o.getLabel(), o.getPrice());
            } else {
                break;
            }
        }
    } catch(...) {
        cout << "Erreur import options" << endl;
    }

    // Lecture de config.dat, des employees, clients et contrats (étape 12)
    Garage::getInstance().load();

    setRole(0); //demarrage en mode non connecté

    // ***** TESTS de l'interfac graphique (à supprimer) *****
    
}

ApplicGarageWindow::~ApplicGarageWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTitle(string title)
{
    this->setWindowTitle(title.c_str());
}

void ApplicGarageWindow::setRole(int val)
{
    // val = 0 --> personne n'est loggé
    // val = 1 --> un administratif est loggé
    // val = 2 --> un vendeur loggé
    // val = 3 --> on a accès à tout

    if (val == 0)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(false);
        ui->actionResetPassword->setEnabled(false);

        ui->menuEmployees->setEnabled(false);

        ui->menuClients->setEnabled(false);

        ui->menuCar->setEnabled(false);
        ui->comboBoxAvailableModels->setEnabled(false);
        ui->comboBoxAvailableOptions->setEnabled(false);
        ui->pushButtonOpenProject->setEnabled(false);
        ui->pushButtonNewProject->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonSaveProject->setEnabled(false);
        ui->pushButtonAddOption->setEnabled(false);
        ui->pushButtonRemoveOption->setEnabled(false);
        ui->pushButtonSelectModel->setEnabled(false);

        ui->pushButtonShowCar->setEnabled(false);
        ui->pushButtonNewContract->setEnabled(false);
        ui->pushButtonDeleteContract->setEnabled(false);
    }

    if (val == 1)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(true);

        ui->menuClients->setEnabled(false);

        ui->menuCar->setEnabled(false);
        ui->comboBoxAvailableModels->setEnabled(false);
        ui->comboBoxAvailableOptions->setEnabled(false);
        ui->pushButtonOpenProject->setEnabled(false);
        ui->pushButtonNewProject->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonSaveProject->setEnabled(false);
        ui->pushButtonAddOption->setEnabled(false);
        ui->pushButtonRemoveOption->setEnabled(false);
        ui->pushButtonSelectModel->setEnabled(false);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(false);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

    if (val == 2)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(false);

        ui->menuClients->setEnabled(true);

        ui->menuCar->setEnabled(true);
        ui->comboBoxAvailableModels->setEnabled(true);
        ui->comboBoxAvailableOptions->setEnabled(true);
        ui->pushButtonOpenProject->setEnabled(true);
        ui->pushButtonNewProject->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonSaveProject->setEnabled(true);
        ui->pushButtonAddOption->setEnabled(true);
        ui->pushButtonRemoveOption->setEnabled(true);
        ui->pushButtonSelectModel->setEnabled(true);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(true);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

    if (val == 3)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(true);

        ui->menuClients->setEnabled(true);

        ui->menuCar->setEnabled(true);
        ui->comboBoxAvailableModels->setEnabled(true);
        ui->comboBoxAvailableOptions->setEnabled(true);
        ui->pushButtonOpenProject->setEnabled(true);
        ui->pushButtonNewProject->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonSaveProject->setEnabled(true);
        ui->pushButtonAddOption->setEnabled(true);
        ui->pushButtonRemoveOption->setEnabled(true);
        ui->pushButtonSelectModel->setEnabled(true);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(true);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Table des options du projet en cours (ne pas modifier) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTableOption(int index,string code,string label,float price)
{
    // Modifie l'option de la ligne correspondant à l'indice fourni dans la table des options de l'interface graphique
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code.c_str());
    ui->tableWidgetOptions->setItem(index,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    char tmp[20];
    sprintf(tmp,"%.2f",price);
    if (price < 0.0) item->setText("");
    else item->setText(tmp);
    ui->tableWidgetOptions->setItem(index,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(label.c_str());
    ui->tableWidgetOptions->setItem(index,2,item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableOption()
{
    for (int i=0 ; i<5 ; i++) setTableOption(i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexOptionSelectionTable() const
{
    // retourne l'indice de l'option selectionnee dans la table des options
    QModelIndexList list = ui->tableWidgetOptions->selectionModel()->selectedRows();
    if (list.size() == 0) return -1;
    QModelIndex index = list.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combobox des modèles disponibles (ne pas modifier) /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addAvailableModel(string name,float basePrice)
{
    // ajoute un modèle dans le combobox correspondant (juste le nom et le prix)
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",basePrice);
    ss << name.c_str() << " (" << temp << ")";
    ui->comboBoxAvailableModels->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearComboBoxAvailableModels()
{
    ui->comboBoxAvailableModels->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexModelSelectionCombobox() const
{
    // retourne l'indice du modèle selectionné dans le combobox des modèles
    return ui->comboBoxAvailableModels->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des options disponibles (ne pas modifier) ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addAvailableOption(string label,float price)
{
    // ajoute une option dans le combobox correspondant
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",price);
    ss << label << " (" << temp << ")";
    ui->comboBoxAvailableOptions->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearComboBoxAvailableOptions()
{
    ui->comboBoxAvailableOptions->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexOptionSelectionCombobox() const
{
    // retourne l'indice de l'option selectionnée dans le combobox des options
    return ui->comboBoxAvailableOptions->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion I/O Projet en cours (ne pas modifier) //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setCurrentProjectName(string name)
{
    // Remplit le champ nom de l'interface graphique avec le nom reçu
    ui->lineEditProjectName->setText(name.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::getCurrentProjectName() const
{
    return ui->lineEditProjectName->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setModel(string name,int power,int engine,float basePrice,string modelImage)
{
    // Remplit les champs correspondants dans l'interface graphique
    // pour le moteur (int) : 0=Essence, 1=Diesel, 2=Electrique, 3=Hybride
    ui->lineEditModelName->setText(name.c_str());
    ui->lineEditPower->setText(to_string(power).c_str());
    char tmp[20];
    sprintf(tmp,"%.2f",basePrice);
    ui->lineEditBasePrice->setText(tmp);

    ui->radioButtonPetrol->setChecked(false);
    ui->radioButtonDiesel->setChecked(false);
    ui->radioButtonElectric->setChecked(false);
    ui->radioButtonHybrid->setChecked(false);

    if (engine == 0) ui->radioButtonPetrol->setChecked(true);
    if (engine == 1) ui->radioButtonDiesel->setChecked(true);
    if (engine == 2) ui->radioButtonElectric->setChecked(true);
    if (engine == 3) ui->radioButtonHybrid->setChecked(true);

    // Met à jour l'image du modèle
    string cheminComplet = IMAGES_DIR + modelImage;
    QLabel* label = new QLabel();
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);
    QPixmap *pixmap_img = new QPixmap(cheminComplet.c_str());
    label->setPixmap(*pixmap_img);
    label->resize(label->pixmap()->size());
    ui->scrollArea->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setPrice(float price)
{
  char tmp[20];
  sprintf(tmp,"%.2f",price);
  ui->lineEditPrice->setText(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Employes (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableEmployees(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char name[40];
    strcpy(name,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char firstName[40];
    strcpy(firstName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char fonction[40];
    strcpy(fonction,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetEmployees->rowCount();
    nbLines++;
    ui->tableWidgetEmployees->setRowCount(nbLines);
    ui->tableWidgetEmployees->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetEmployees->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(name);
    ui->tableWidgetEmployees->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(firstName);
    ui->tableWidgetEmployees->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(fonction);
    ui->tableWidgetEmployees->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableEmployees()
{
    ui->tableWidgetEmployees->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexEmployeeSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetEmployees->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Clients (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableClients(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char lastName[40];
    strcpy(lastName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char firstName[40];
    strcpy(firstName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char gsm[40];
    strcpy(gsm,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetClients->rowCount();
    nbLines++;
    ui->tableWidgetClients->setRowCount(nbLines);
    ui->tableWidgetClients->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetClients->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(lastName);
    ui->tableWidgetClients->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(firstName);
    ui->tableWidgetClients->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(gsm);
    ui->tableWidgetClients->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableClients()
{
    ui->tableWidgetClients->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexClientSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetClients->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Contrats (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableContracts(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char seller[40];
    strcpy(seller,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char client[40];
    strcpy(client,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char car[40];
    strcpy(car,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetContracts->rowCount();
    nbLines++;
    ui->tableWidgetContracts->setRowCount(nbLines);
    ui->tableWidgetContracts->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetContracts->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(seller);
    ui->tableWidgetContracts->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(client);
    ui->tableWidgetContracts->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(car);
    ui->tableWidgetContracts->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableContracts()
{
    ui->tableWidgetContracts->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexContractSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetContracts->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogMessage(const char* title,const char* message)
{
   QMessageBox::information(this,title,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogError(const char* title,const char* message)
{
   QMessageBox::critical(this,title,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::dialogPromptText(const char* title,const char* question)
{
    QString chaine = QInputDialog::getText(this,title,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::dialogPromptInt(const char* title,const char* question)
{
    return QInputDialog::getInt(this,title,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplicGarageWindow::dialogPromptFloat(const char* title,const char* question)
{
    return QInputDialog::getDouble(this,title,question);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionQuit_triggered()
{
    // TO DO (étape 12)
    Garage::getInstance().save();

    cout << ">>> Clic sur item Quitter <<<" << endl;

    QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::closeEvent(QCloseEvent *event)
{
    // TO DO (étape 12)
    Garage::getInstance().save();

    cout << ">>> Clic sur croix de fenetre <<<" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNewModel_triggered()
{
    try {
        // 1. Obtenir les données via des boîtes de dialogue
        string modelName = this->dialogPromptText("Nouveau modèle","Nom :");
        int power = this->dialogPromptInt("Nouveau modèle","Puissance :");
        int engine = this->dialogPromptInt("Nouveau modèle :","Moteur (0=essence,1=diesel,2=électrique,3=hybride) :");
        float basePrice = this->dialogPromptFloat("Nouveau modèle","Prix de base :");
        string image = this->dialogPromptText("Nouveau modèle","Nom du fichier de l'image :");
        
        cout << ">>> Clic sur item NewModel <<<" << endl;
        cout << "modelName = " << modelName << endl;
        cout << "power = " << power << endl;
        cout << "engine = " << engine << endl;
        cout << "basePrice = " << basePrice << endl;
        cout << "image = " << image << endl;
        
        // 2. Validation des données
        if (modelName.empty() || power < 0 || engine < 0 || engine > 3 || basePrice < 0) {
            dialogError("Erreur", "Données invalides");
            return;
        }
        
        // 3. Créer le modèle
        Model m(modelName.c_str(), power, (Engine)engine, basePrice);
        m.setImage(image);
        
        // 4. Ajouter au garage
        Garage::getInstance().addModel(m);
        
        // 5. Mettre à jour la combobox
        addAvailableModel(modelName, basePrice);
        
        dialogMessage("Succès", "Modèle ajouté avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNewOption_triggered()
{
    try {
        // 1. Obtenir les données
        string code = this->dialogPromptText("Nouvelle option","Code :");
        string label = this->dialogPromptText("Nouvelle option","Intitulé :");
        float price = this->dialogPromptFloat("Nouvelle option","Prix :");
        
        cout << ">>> Clic sur item NewOption <<<" << endl;
        cout << "code = " << code << endl;
        cout << "label = " << label << endl;
        cout << "price = " << price << endl;
        
        // 2. Créer l'option (OptionException lancée automatiquement si invalide)
        Option o(code, label, price);
        
        // 3. Ajouter au garage
        Garage::getInstance().addOption(o);
        
        // 4. Mettre à jour la combobox
        addAvailableOption(label, price);
        
        dialogMessage("Succès", "Option ajoutée avec succès");
        
    } catch(OptionException& e) {
        dialogError("Erreur Option", e.getMessage().c_str());
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAddEmployee_triggered()
{
    try {
        string lastName = this->dialogPromptText("Nouvel employé","Nom :");
        string firstName = this->dialogPromptText("Nouvel employé","Prénom :");
        string login = this->dialogPromptText("Nouvel employé","Login :");
        int type = this->dialogPromptInt("Nouvel employé","Fonction (0=administratif,1=vendeur) :");
        
        cout << ">>> Clic sur item AddEmployee <<<" << endl;
        
        // Validation
        if (lastName.empty() || firstName.empty() || login.empty()) {
            dialogError("Erreur", "Tous les champs sont obligatoires");
            return;
        }
        
        if (type != 0 && type != 1) {
            dialogError("Erreur", "Type invalide (0=administratif, 1=vendeur)");
            return;
        }
        
        // Déterminer le rôle
        string role = (type == 0) ? Employee::ADMINISTRATIVE : Employee::SELLER;
        
        // Ajouter l'employé
        Garage::getInstance().addEmployee(lastName, firstName, login, role);
        
        // Mettre à jour la table
        clearTableEmployees();
        set<Employee> employees = Garage::getInstance().getEmployees();
        for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
            addTupleTableEmployees(it->tuple());
        }
        
        dialogMessage("Succès", "Employé ajouté avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteEmployeeById_triggered()
{
    cout << ">>> Clic sur item DeleteEmployeeById <<<" << endl;
    
    try {
        int id = this->dialogPromptInt("Supprimer employé", "ID de l'employé :");

        // ÉTAPE 13 : Vérifier si l'employé a des contrats
        if (Garage::getInstance().hasContractWithSeller(id)) {
            dialogError("Erreur", "Impossible de supprimer cet employé : il a des contrats en cours");
            return;
        }
        
        Garage::getInstance().deleteEmployeeById(id);
        
        // Mettre à jour la table
        clearTableEmployees();
        set<Employee> employees = Garage::getInstance().getEmployees();
        for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
            addTupleTableEmployees(it->tuple());
        }
        
        dialogMessage("Succès", "Employé supprimé");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteEmployeeByIndex_triggered()
{
    cout << ">>> Clic sur item DeleteEmployeeByIndex <<<" << endl;
    
    int index = getIndexEmployeeSelectionTable();
    
    if (index == -1) {
        dialogError("Erreur", "Aucun employé sélectionné");
        return;
    }

    // ÉTAPE 13 : Vérifier si l'employé a des contrats
    Employee emp = Garage::getInstance().findEmployeeByIndex(index);
    if (Garage::getInstance().hasContractWithSeller(emp.getId())) {
        dialogError("Erreur", "Impossible de supprimer cet employé : il a des contrats en cours");
        return;
    }
    
    Garage::getInstance().deleteEmployeeByIndex(index);
    
    // Mettre à jour la table
    clearTableEmployees();
    set<Employee> employees = Garage::getInstance().getEmployees();
    for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
        addTupleTableEmployees(it->tuple());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAddClient_triggered()
{
    try {
        string lastName = this->dialogPromptText("Nouveau client","Nom :");
        string firstName = this->dialogPromptText("Nouveau client","Prénom :");
        string gsm = this->dialogPromptText("Nouveau client","GSM :");
        
        cout << ">>> Clic sur item AddClient <<<" << endl;
        
        if (lastName.empty() || firstName.empty() || gsm.empty()) {
            dialogError("Erreur", "Tous les champs sont obligatoires");
            return;
        }
        
        Garage::getInstance().addClient(lastName, firstName, gsm);
        
        // Mettre à jour la table
        clearTableClients();
        set<Client> clients = Garage::getInstance().getClients();
        for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            addTupleTableClients(it->tuple());
        }
        
        dialogMessage("Succès", "Client ajouté avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteClientById_triggered()
{
    cout << ">>> Clic sur item DeleteClientById <<<" << endl;
    
    try {
        int id = this->dialogPromptInt("Supprimer client", "ID du client :");
        
        // ÉTAPE 13 : Vérifier si le client a des contrats
        if (Garage::getInstance().hasContractWithClient(id)) {
            dialogError("Erreur", "Impossible de supprimer ce client : il a des contrats en cours");
            return;
        }
        
        Garage::getInstance().deleteClientById(id);
        
        // Mettre à jour la table
        clearTableClients();
        set<Client> clients = Garage::getInstance().getClients();
        for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            addTupleTableClients(it->tuple());
        }
        
        dialogMessage("Succès", "Client supprimé");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteClientByIndex_triggered()
{
    cout << ">>> Clic sur item DeleteClientByIndex <<<" << endl;
    
    int index = getIndexClientSelectionTable();
    
    if (index == -1) {
        dialogError("Erreur", "Aucun client sélectionné");
        return;
    }
    
    // ÉTAPE 13 : Vérifier si le client a des contrats
    Client client = Garage::getInstance().findClientByIndex(index);
    if (Garage::getInstance().hasContractWithClient(client.getId())) {
        dialogError("Erreur", "Impossible de supprimer ce client : il a des contrats en cours");
        return;
    }
    
    Garage::getInstance().deleteClientByIndex(index);
    
    // Mettre à jour la table
    clearTableClients();
    set<Client> clients = Garage::getInstance().getClients();
    for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        addTupleTableClients(it->tuple());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogin_triggered()
{
    cout << ">>> Clic sur item Login <<<" << endl;
    
    try {
        // 1. Demander le login
        string login = dialogPromptText("Connexion", "Login :");
        
        if (login.empty()) {
            dialogError("Erreur", "Login vide");
            return;
        }
        
        // 2. Chercher l'employé
        set<Employee> employees = Garage::getInstance().getEmployees();
        bool found = false;
        Employee emp;
        
        for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
            if (it->getLogin() == login) {
                emp = *it;
                found = true;
                break;
            }
        }
        
        if (!found) {
            dialogError("Erreur", "Login inconnu");
            return;
        }
        
        // 3. Mémoriser l'ID
        Garage::idLoggedEmployee = emp.getId();
        
        // 4. Vérifier le mot de passe
        try {
            string existingPassword = emp.getPassword();
            
            // L'employé a un mot de passe
            string enteredPassword = dialogPromptText("Connexion", "Mot de passe :");
            
            if (enteredPassword == existingPassword) 
            {
                dialogMessage("Succès", "Connexion réussie !");
                
                // Activer l'interface selon le rôle
                if (emp.getRole() == Employee::ADMINISTRATIVE) {
                    setRole(1);
                } else {
                    setRole(2);
                }
                
                // Mettre à jour le titre
                setTitle("Application Garage : " + emp.toString());
                
                // Afficher les tables
                clearTableEmployees();
                for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
                    addTupleTableEmployees(it->tuple());
                }
                
                clearTableClients();
                set<Client> clients = Garage::getInstance().getClients();
                for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
                    addTupleTableClients(it->tuple());
                }

                clearTableContracts();
                vector<Contract> contracts = Garage::getInstance().getContracts();
                for (size_t i = 0; i < contracts.size(); i++) 
                {
                    try {
                        Employee s = Garage::getInstance().findEmployeeById(contracts[i].getSellerId());
                        Client c = Garage::getInstance().findClientById(contracts[i].getClientId());
                        
                        string tuple = to_string(contracts[i].getId()) + ";" +
                                      s.toString() + ";" +
                                      c.toString() + ";" +
                                      contracts[i].getCarProjectName();
                        
                        addTupleTableContracts(tuple);
                    }catch(...) {}
                }
                
            } 
            else {
                dialogError("Erreur", "Mot de passe incorrect");
                Garage::idLoggedEmployee = -1;
            }
            
        } catch (PasswordException& e) {
            dialogMessage("Premier login", "Vous n'avez pas de mot de passe.\nVeuillez en créer un (min 6 car, 1 lettre, 1 chiffre).");
            
            string newPassword = dialogPromptText("Nouveau mot de passe", "Créer votre mot de passe :");
            
            try {
                emp.setPassword(newPassword);

                //Mettre à jour l'employé dans le Garage 
                Garage::getInstance().updateEmployee(emp);

                dialogMessage("Succès", "Mot de passe créé.\nVeuillez vous reconnecter.");
            
                
                Garage::idLoggedEmployee = -1;
                
            } catch (PasswordException& pe) {
                string errorMsg = "Mot de passe invalide:\n";
                switch(pe.getCode()) {
                    case PasswordException::INVALID_LENGTH:
                        errorMsg += "- Minimum 6 caractères";
                        break;
                    case PasswordException::ALPHA_MISSING:
                        errorMsg += "- Au moins 1 lettre requise";
                        break;
                    case PasswordException::DIGIT_MISSING:
                        errorMsg += "- Au moins 1 chiffre requis";
                        break;
                }
                dialogError("Erreur", errorMsg.c_str());
                Garage::idLoggedEmployee = -1;
            }
        }
        
    } catch (exception& e) {
        dialogError("Erreur", e.what());
        Garage::idLoggedEmployee = -1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogout_triggered()
{
    cout << ">>> Clic sur item Logout <<<" << endl;
    
    // Réinitialiser l'ID
    Garage::idLoggedEmployee = -1;
    
    // Désactiver l'interface
    setRole(0);
    
    // Réinitialiser le titre
    setTitle("Application Garage");
    
    // Vider les tables
    clearTableEmployees();
    clearTableClients();
    clearTableContracts();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionResetPassword_triggered()
{
    cout << ">>> Clic sur item ResetPassword <<<" << endl;
    
    if (Garage::idLoggedEmployee == -1) {
        dialogError("Erreur", "Vous devez être connecté");
        return;
    }
    
    try {
        Employee emp = Garage::getInstance().findEmployeeById(Garage::idLoggedEmployee);
        emp.resetPassword();
        
        dialogMessage("Succès", "Mot de passe reseté.\nVous devrez en créer un nouveau lors de votre prochaine connexion.");
        
        // Note: La modification ne sera effective qu'après sauvegarde (Étape 12)
        
    } catch (exception& e) {
        dialogError("Erreur", e.what());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSelectModel_clicked()
{
    cout << ">>> Clic sur bouton SelectModel <<<" << endl;
    
    // 1. Récupérer l'indice sélectionné
    int index = getIndexModelSelectionCombobox();
    
    if (index == -1) {
        dialogError("Erreur", "Aucun modèle sélectionné");
        return;
    }
    
    // 2. Récupérer le modèle
    Model m = Garage::getInstance().getModel(index);
    
    // 3. Affecter au projet en cours
    Garage::getCurrentProject().setModel(m);
    
    // 4. Mettre à jour l'interface
    setModel(m.getName(), m.getPower(), (int)m.getEngine(), m.getBasePrice(), m.getImage());
    setPrice(Garage::getCurrentProject().getPrice());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonAddOption_clicked()
{
    cout << ">>> Clic sur bouton AddOption <<<" << endl;
    
    try {
        // 1. Récupérer l'indice sélectionné
        int index = getIndexOptionSelectionCombobox();
        
        if (index == -1) {
            dialogError("Erreur", "Aucune option sélectionnée");
            return;
        }
        
        // 2. Récupérer l'option
        Option o = Garage::getInstance().getOption(index);
        
        // 3. Ajouter au projet (peut lancer OptionException)
        Garage::getCurrentProject().addOption(o);
        
        // 4. Mettre à jour la table des options
        for (int i = 0; i < 5; i++) {
            Option* ptr = Garage::getCurrentProject()[i];
            if (ptr != nullptr) {
                setTableOption(i, ptr->getCode(), ptr->getLabel(), ptr->getPrice());
            } else {
                setTableOption(i);  // Vider la ligne
            }
        }
        
        // 5. Mettre à jour le prix
        setPrice(Garage::getCurrentProject().getPrice());
        
    } catch(OptionException& e) {
        dialogError("Erreur Option", e.getMessage().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonRemoveOption_clicked()
{
    cout << ">>> Clic sur bouton RemoveOption <<<" << endl;
    
    try {
        // 1. Récupérer l'indice sélectionné dans la table
        int index = getIndexOptionSelectionTable();
        
        if (index == -1) {
            dialogError("Erreur", "Aucune option sélectionnée");
            return;
        }
        
        // 2. Récupérer le pointeur vers l'option
        Option* ptr = Garage::getCurrentProject()[index];
        
        if (ptr == nullptr) {
            dialogError("Erreur", "Emplacement vide");
            return;
        }
        
        // 3. Supprimer l'option
        Garage::getCurrentProject().removeOption(ptr->getCode());
        
        // 4. Mettre à jour la table
        for (int i = 0; i < 5; i++) {
            Option* p = Garage::getCurrentProject()[i];
            if (p != nullptr) {
                setTableOption(i, p->getCode(), p->getLabel(), p->getPrice());
            } else {
                setTableOption(i);
            }
        }
        
        // 5. Mettre à jour le prix
        setPrice(Garage::getCurrentProject().getPrice());
        
    } catch(OptionException& e) {
        dialogError("Erreur", e.getMessage().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonReduction_clicked()
{
    cout << ">>> Clic sur bouton Reduction <<<" << endl;
    
    try {
        // 1. Récupérer l'indice sélectionné
        int index = getIndexOptionSelectionTable();
        
        if (index == -1) {
            dialogError("Erreur", "Aucune option sélectionnée");
            return;
        }
        
        // 2. Récupérer le pointeur
        Option* ptr = Garage::getCurrentProject()[index];
        
        if (ptr == nullptr) {
            dialogError("Erreur", "Emplacement vide");
            return;
        }
        
        // 3. Appliquer la décrémentation (peut lancer OptionException)
        --(*ptr);
        
        // 4. Mettre à jour la table
        for (int i = 0; i < 5; i++) {
            Option* p = Garage::getCurrentProject()[i];
            if (p != nullptr) {
                setTableOption(i, p->getCode(), p->getLabel(), p->getPrice());
            } else {
                setTableOption(i);
            }
        }
        
        // 5. Mettre à jour le prix
        setPrice(Garage::getCurrentProject().getPrice());
        
    } catch(OptionException& e) {
        dialogError("Erreur", e.getMessage().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSaveProject_clicked()
{
    cout << ">>> Clic sur bouton SaveProject <<<" << endl;
    
    try {
        // 1. Récupérer le nom du projet
        string name = getCurrentProjectName();
        
        if (name.empty()) {
            dialogError("Erreur", "Veuillez entrer un nom de projet");
            return;
        }
        
        // 2. Affecter le nom au projet
        Garage::getCurrentProject().setName(name);
        
        // 3. Sauvegarder
        Garage::getCurrentProject().save();
        
        dialogMessage("Succès", "Projet sauvegardé avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonOpenProject_clicked()
{
    cout << ">>> Clic sur bouton OpenProject <<<" << endl;
    
    try {
        // 1. Récupérer le nom du projet
        string name = getCurrentProjectName();
        
        if (name.empty()) {
            dialogError("Erreur", "Veuillez entrer un nom de projet");
            return;
        }
        
        // 2. Charger le projet
        Garage::getCurrentProject().load(name);
        
        // 3. Mettre à jour l'interface
        Model m = Garage::getCurrentProject().getModel();
        setModel(m.getName(), m.getPower(), (int)m.getEngine(), m.getBasePrice(), m.getImage());
        
        // Mettre à jour les options
        for (int i = 0; i < 5; i++) {
            Option* ptr = Garage::getCurrentProject()[i];
            if (ptr != nullptr) {
                setTableOption(i, ptr->getCode(), ptr->getLabel(), ptr->getPrice());
            } else {
                setTableOption(i);
            }
        }
        
        // Mettre à jour le prix
        setPrice(Garage::getCurrentProject().getPrice());
        
        dialogMessage("Succès", "Projet chargé avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNewProject_clicked()
{
    cout << ">>> Clic sur bouton NewProject <<<" << endl;
    
    // 1. Réinitialiser le projet
    Garage::resetCurrentProject();
    
    // 2. Mettre à jour l'interface
    setCurrentProjectName("");
    setModel("", 0, 0, 0.0f, "");
    clearTableOption();
    setPrice(0.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNewContract_clicked()
{
    cout << ">>> Clic sur bouton NewContract <<<" << endl;
    
    try {
        // Vérifier qu'on est connecté en tant que vendeur
        if (Garage::idLoggedEmployee == -1) {
            dialogError("Erreur", "Vous devez être connecté");
            return;
        }
        
        // Récupérer l'employé connecté
        Employee seller = Garage::getInstance().findEmployeeById(Garage::idLoggedEmployee);
        
        // Vérifier que c'est un vendeur
        if (seller.getRole() != Employee::SELLER) {
            dialogError("Erreur", "Seuls les vendeurs peuvent créer des contrats");
            return;
        }
        
        // Récupérer l'indice du client sélectionné
        int clientIndex = getIndexClientSelectionTable();
        
        if (clientIndex == -1) {
            dialogError("Erreur", "Veuillez sélectionner un client dans la table");
            return;
        }
        
        // Récupérer le client
        Client client = Garage::getInstance().findClientByIndex(clientIndex);
        
        // Récupérer le nom du projet en cours
        string projectName = Garage::getCurrentProject().getName();
        
        if (projectName.empty()) {
            dialogError("Erreur", "Le projet en cours n'a pas de nom.\nVeuillez l'enregistrer d'abord.");
            return;
        }
        
        // Créer le contrat
        int contractId = Garage::getInstance().addContract(
            Garage::idLoggedEmployee,  // ID du vendeur
            client.getId(),             // ID du client
            projectName                 // Nom du projet
        );
        
        // Mettre à jour la table des contrats
        clearTableContracts();
        vector<Contract> contracts = Garage::getInstance().getContracts();
        
        for (size_t i = 0; i < contracts.size(); i++) {
            // Récupérer les noms du vendeur et du client
            Employee s = Garage::getInstance().findEmployeeById(contracts[i].getSellerId());
            Client c = Garage::getInstance().findClientById(contracts[i].getClientId());
            
            // Format du tuple : id;vendeur;client;voiture
            string tuple = to_string(contracts[i].getId()) + ";" +
                          s.toString() + ";" +
                          c.toString() + ";" +
                          contracts[i].getCarProjectName();
            
            addTupleTableContracts(tuple);
        }
        
        string msg = "Contrat #" + to_string(contractId) + " créé avec succès";
        dialogMessage("Succès", msg.c_str());
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonDeleteContract_clicked()
{
    cout << ">>> Clic sur bouton DeleteContract <<<" << endl;
    
    try {
        // Récupérer l'indice du contrat sélectionné
        int index = getIndexContractSelectionTable();
        
        if (index == -1) {
            dialogError("Erreur", "Veuillez sélectionner un contrat dans la table");
            return;
        }
        
        // Récupérer le contrat
        Contract contract = Garage::getInstance().findContractByIndex(index);
        
        // Supprimer le contrat
        Garage::getInstance().deleteContractById(contract.getId());
        
        // Mettre à jour la table des contrats
        clearTableContracts();
        vector<Contract> contracts = Garage::getInstance().getContracts();
        
        for (size_t i = 0; i < contracts.size(); i++) {
            Employee s = Garage::getInstance().findEmployeeById(contracts[i].getSellerId());
            Client c = Garage::getInstance().findClientById(contracts[i].getClientId());
            
            string tuple = to_string(contracts[i].getId()) + ";" +
                          s.toString() + ";" +
                          c.toString() + ";" +
                          contracts[i].getCarProjectName();
            
            addTupleTableContracts(tuple);
        }
        
        dialogMessage("Succès", "Contrat supprimé avec succès");
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonShowCar_clicked()
{
    cout << ">>> Clic sur bouton ShowCar <<<" << endl;
    
    try {
        // Récupérer l'indice du contrat sélectionné
        int index = getIndexContractSelectionTable();
        
        if (index == -1) {
            dialogError("Erreur", "Veuillez sélectionner un contrat dans la table");
            return;
        }
        
        // Récupérer le contrat
        Contract contract = Garage::getInstance().findContractByIndex(index);
        
        // Charger le projet de voiture correspondant
        string projectName = contract.getCarProjectName();
        
        try {
            Garage::getCurrentProject().load(projectName);
            
            // Mettre à jour l'interface
            setCurrentProjectName(projectName);
            
            Model m = Garage::getCurrentProject().getModel();
            setModel(m.getName(), m.getPower(), (int)m.getEngine(), m.getBasePrice(), m.getImage());
            
            // Mettre à jour les options
            clearTableOption();
            for (int i = 0; i < 5; i++) {
                Option* ptr = Garage::getCurrentProject()[i];
                if (ptr != nullptr) {
                    setTableOption(i, ptr->getCode(), ptr->getLabel(), ptr->getPrice());
                }
            }
            
            // Mettre à jour le prix
            setPrice(Garage::getCurrentProject().getPrice());
            
            string msg = "Projet '" + projectName + "' chargé avec succès";
            dialogMessage("Succès", msg.c_str());
            
        } catch(exception& e) {
            string msg = string("Impossible de charger le projet:\n") + e.what();
            dialogError("Erreur", msg.c_str());
        }
        
    } catch(exception& e) {
        dialogError("Erreur", e.what());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Mes méthodes à moi /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void ApplicGarageWindow::MAJtableOptions()
{
    for (int i=0 ; i<5 ; i++)
    {
        Option *ptr = Garage::getProjetEnCours()[i];
        if (ptr != NULL) setTableOption(i,ptr->getCode(),ptr->getLabel(),ptr->getPrice());
        else setTableOption(i);
    }
}

void ApplicGarageWindow::MAJprojetEnCours()
{
    setCurrentProjectName(Garage::getProjetEnCours().getName());
    setModel(Garage::getProjetEnCours().getModele().getName(),
              Garage::getProjetEnCours().getModele().getPower(),
              Garage::getProjetEnCours().getModele().getEngine(),
              Garage::getProjetEnCours().getModele().getBasePrice(),
              Garage::getProjetEnCours().getModele().getImage());
    MAJtableOptions();
    setPrice(Garage::getProjetEnCours().getPrice());
}

void ApplicGarageWindow::MAJtableEmployes()
{
    videTableEmployes();
    VecteurTrie<Employe> employes = Garage::getInstance().getEmployes();
    Iterateur<Employe> it(employes);
    while (!it.end())
    {
        addTupleTableEmployees(((Employe)it).Tuple());
        it++;
    }
}

void ApplicGarageWindow::MAJtableClients()
{
    videTableClients();
    VecteurTrie<Client> clients = Garage::getInstance().getClients();
    Iterateur<Client> it(clients);
    while (!it.end())
    {
        ajouteTupleTableClients(((Client)it).Tuple());
        it++;
    }
}

void ApplicGarageWindow::MAJtableContrats()
{
    videTableContrats();
    Vecteur<Contrat> contrats = Garage::getInstance().getContrats();
    Iterateur<Contrat> it(contrats);
    while (!it.end())
    {
        ajouteTupleTableContrats(((Contrat)it).Tuple());
        it++;
    }
}
*/


