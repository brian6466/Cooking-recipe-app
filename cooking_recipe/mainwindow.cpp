#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QMenu>
#include <QPushButton>
#include <QRadioButton>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

// Declare all the strings to hold values for the db query, which are Global to all the methods below
QString sName,sType,sTime,sInstructions,
        sFlour,sParsley,sPepper,sGarlic,sEgg,sMilk,sButter,sSuger,sCream,sOnion,sPotatoe,sPasta,sTomatoe
        ,sCheese,sOliveOil,sCurryPowder,sSalt,sChocolat,sStrawberry,sRaspberry,sOregano, sGinger
        ,sRice,sBanana,sPaprika,sVinegar,sBeef,sChicken,sSalmon,sLamb,sDuck,sCelery,sMushroom
        ,sRedPepper,sGreenPepper,sCarrot,sCoconut,sFructose,sCorn,sTurnip,sPeas,sFudge,sParsnip,sCauliflower,sBroccoli;

int sSliderValue;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrRecipeReport = new RecipiesReport(this);

    this->setFixedSize(850, 850);
}

void MainWindow::on_btnShowNotesMenu_clicked()
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);
//! [0]

//! [1]
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);
//! [1]

//! [2]
    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Make Notes on new Recipies"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

// This destructor helps to manage and free up memory
MainWindow::~MainWindow()
{
    delete ui;
    delete ptrRecipeReport;
     MyDB::ResetInstance();
}


// Gets att the data from the main UI window
void MainWindow::getUserData()
{
sName = ui->txtName->text();
if (ui->radioStarter->isChecked())  { sType = "Starter"; }
if (ui->radioMain->isChecked())  { sType = "Main Course"; }
if (ui->radioDesert->isChecked())  { sType = "Desert"; }
sInstructions = ui->plainTextInstructions->toPlainText();
sSliderValue = ui->horizontalSliderTime->value();
// The following converts int to String for Storing
sTime = QString::number(sSliderValue);
if (ui->checkBoxFlour->isChecked())  { sFlour = 'Y'; } else { sFlour = 'N'; }
if (ui->checkBoxParsley->isChecked())  { sParsley = 'Y'; } else { sFlour = 'N'; }
if (ui->checkBoxPepper->isChecked())  { sPepper = 'Y'; } else { sPepper = 'N'; }
if (ui->checkBoxGarlic->isChecked())  { sGarlic = 'Y'; } else { sGarlic = 'N'; }
if (ui->checkBoxEgg->isChecked())  { sEgg = 'Y'; } else { sEgg = 'N'; }
if (ui->checkBoxMilk->isChecked())  { sMilk = 'Y'; } else { sMilk = 'N'; }
if (ui->checkBoxButter->isChecked())  { sButter = 'Y'; } else { sButter = 'N'; }
if (ui->checkBoxSuger->isChecked())  { sSuger = 'Y'; } else { sSuger = 'N'; }
if (ui->checkBoxCream->isChecked())  { sCream = 'Y'; } else { sCream = 'N'; }
if (ui->checkBoxOnion->isChecked())  { sOnion = 'Y'; } else { sOnion = 'N'; }
if (ui->checkBoxPotatoe->isChecked())  { sPotatoe = 'Y'; } else { sPotatoe = 'N'; }
if (ui->checkBoxPasta->isChecked())  { sPasta = 'Y'; } else { sPasta = 'N'; }
if (ui->checkBoxRice->isChecked())  { sRice = 'Y'; } else { sRice = 'N'; }
if (ui->checkBoxTomatoe->isChecked())  { sTomatoe = 'Y'; } else { sTomatoe = 'N'; }
if (ui->checkBoxCheese->isChecked())  { sCheese = 'Y'; } else { sCheese = 'N'; }
if (ui->checkBoxOliveOil->isChecked())  { sOliveOil = 'Y'; } else { sOliveOil = 'N'; }
if (ui->checkBoxCurryPowder->isChecked())  { sCurryPowder = 'Y'; } else { sCurryPowder = 'N'; }
if (ui->checkBoxSalt->isChecked())  { sSalt = 'Y'; } else { sSalt = 'N'; }
if (ui->checkBoxChocolat->isChecked())  { sChocolat = 'Y'; } else { sChocolat = 'N'; }
if (ui->checkBoxStrawberry->isChecked())  { sStrawberry = 'Y'; } else { sStrawberry = 'N'; }
if (ui->checkBoxRaspberry->isChecked())  { sRaspberry = 'Y'; } else { sRaspberry = 'N'; }
if (ui->checkBoxGinger->isChecked())  { sGinger = 'Y'; } else { sGinger = 'N'; }
if (ui->checkBoxPaprika->isChecked())  { sPaprika = 'Y'; } else { sPaprika = 'N'; }
if (ui->checkBoxOregano->isChecked())  { sOregano = 'Y'; } else { sOregano = 'N'; }
if (ui->checkBoxBanana->isChecked())  { sBanana = 'Y'; } else { sBanana = 'N'; }
if (ui->checkBoxVinegar->isChecked())  { sVinegar = 'Y'; } else { sVinegar = 'N'; }
if (ui->checkBoxBeef->isChecked())  { sBeef = 'Y'; } else { sBeef = 'N'; }
if (ui->checkBoxChicken->isChecked())  { sChicken = 'Y'; } else { sChicken = 'N'; }
if (ui->checkBoxSalmon->isChecked())  { sSalmon = 'Y'; } else { sSalmon = 'N'; }
if (ui->checkBoxDuck->isChecked())  { sDuck = 'Y'; } else { sDuck = 'N'; }
if (ui->checkBoxLamb->isChecked())  { sLamb = 'Y'; } else { sLamb = 'N'; }
if (ui->checkBoxCelery->isChecked())  { sCelery = 'Y'; } else { sCelery = 'N'; }
if (ui->checkBoxMushroom->isChecked())  { sMushroom = 'Y'; } else { sMushroom = 'N'; }
if (ui->checkBoxRedPepper->isChecked())  { sRedPepper = 'Y'; } else { sRedPepper = 'N'; }
if (ui->checkBoxGreenPepper->isChecked())  { sGreenPepper = 'Y'; } else { sGreenPepper = 'N'; }
if (ui->checkBoxCarrot->isChecked())  { sCarrot = 'Y'; } else { sCarrot = 'N'; }
if (ui->checkBoxCoconut->isChecked())  { sCoconut = 'Y'; } else { sCoconut = 'N'; }
if (ui->checkBoxFructose->isChecked())  { sFructose = 'Y'; } else { sFructose = 'N'; }
if (ui->checkBoxCorn->isChecked())  { sCorn = 'Y'; } else { sCorn = 'N'; }
if (ui->checkBoxTurnip->isChecked())  { sTurnip = 'Y'; } else { sTurnip = 'N'; }
if (ui->checkBoxPeas->isChecked())  { sPeas = 'Y'; } else { sPeas = 'N'; }
if (ui->checkBoxFudge->isChecked())  { sFudge= 'Y'; } else { sFudge = 'N'; }
if (ui->checkBoxParsnip->isChecked())  { sParsnip = 'Y'; } else { sParsnip = 'N'; }
if (ui->checkBoxCauliflower->isChecked())  { sCauliflower = 'Y'; } else { sCauliflower = 'N'; }
if (ui->checkBoxBroccoli->isChecked())  { sBroccoli = 'Y'; } else { sBroccoli = 'N'; }
}

void MainWindow::on_btnAddRecipe_clicked()
{

    getUserData();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();
    query.prepare("insert into recipes(Name, Type, CookTime, Instructions, Flour, Parsley,"
                  "Pepper, Garlic, Egg, Milk, Butter, Suger, Cream, Onion, Potatoe, Pasta,"
                  "Rice, Tomatoe, Cheese, OliveOil, CurryPowder, Salt, Chocolat, Strawberry,"
                  "Raspberry, Banana, Paprika, Oregano, Vinegar, Beef, Chicken, Salmon,"
                  "Lamb, Duck, Celery, Mushroom, RedPepper, GreenPepper, Carrot, Coconut, Fructose,"
                  "Corn, Turnip, Peas, Fudge, Parsnip, Cauliflower, Broccoli, Ginger) "
         "values ('" + sName +"','" + sType +"','" + sTime +"','" + sInstructions +"','" +sFlour + "','" +sParsley + "',"
                  "'" + sPepper +"','" + sGarlic +"','" + sEgg +"','" + sMilk +"','" +sButter + "','" +sSuger + "','" +sCream + "', "
                  "'" + sOnion +"','" + sPotatoe +"','" + sPasta +"','" + sRice +"','" +sTomatoe + "','" +sCheese + "','" +sOliveOil + "', "
                  "'" + sCurryPowder +"','" + sSalt +"','" + sChocolat +"','" + sStrawberry +"','" +sRaspberry + "','" +sBanana + "','" +sPaprika + "', "
                  "'" + sOregano +"','" + sVinegar +"','" + sBeef +"','" + sChicken +"','" +sSalmon + "','" +sLamb + "','" +sDuck + "', "
                  "'" + sCelery +"','" + sMushroom +"','" + sRedPepper +"','" + sGreenPepper +"','" +sCarrot + "','" +sCoconut + "','" +sFructose + "', "
                  "'" + sCorn +"','" + sTurnip +"','" + sPeas +"','" + sFudge +"','" +sParsnip + "','" +sCauliflower + "','" +sBroccoli + "', "
                  "'" + sGinger +"')");
    try
    {
        if(!query.exec())
        {
            qDebug() << query.lastError().text() << query.lastQuery();
            ui->lblInfo->setText("Unable to Add Recipe");

        }
        else
        {
            if(query.numRowsAffected() > 0)
            {
                qDebug() <<"read was successful "<< query.lastQuery();
                ui->lblInfo->setText("Recipe Added Successfully!");
                resetElements();
            }
            else
                qDebug() <<"Unable to Add new Recipe";
         }
    }
    catch(std::exception & e)
    {
        qDebug() << " Unable to Process Add Query";

    }
}

//! [3]
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
//! [3]

void MainWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::print()
{
    infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void MainWindow::undo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::cut()
{
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void MainWindow::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::bold()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::justify()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
}

void MainWindow::center()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::setLineSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

//! [4]
void MainWindow::createActions()
{
//! [5]
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
//! [4]

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
//! [5]

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, &QAction::triggered, this, &MainWindow::bold);

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, &QAction::triggered, this, &MainWindow::italic);

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, &QAction::triggered, this, &MainWindow::setLineSpacing);

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, &QAction::triggered,
            this, &MainWindow::setParagraphSpacing);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, &QAction::triggered, this, &MainWindow::justify);

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, &QAction::triggered, this, &MainWindow::center);

//! [6] //! [7]
    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
//! [6]
}
//! [7]

//! [8]
void MainWindow::createMenus()
{
//! [9] //! [10]
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
//! [9]
    fileMenu->addAction(openAct);
//! [10]
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
//! [11]
    fileMenu->addSeparator();
//! [11]
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
//! [8]

//! [12]
    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
}
//! [12]



void MainWindow::on_btnUpdateRecipe_clicked()
{
    getUserData();
    ui->lblInfo->clear();
    QString sName = ui->txtName->text();


    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("update recipes set Type='" + sType + "',CookTime = '" + sTime + "',Instructions='" + sInstructions + "',"
     "Flour='" + sFlour + "',Parsley='" + sParsley + "',Pepper='" + sPepper + "',Garlic='" + sGarlic + "',Egg='" + sEgg + "',Milk='" + sMilk + "',"
     "Butter='" + sButter + "',Suger='" + sSuger + "',Cream='" + sCream + "',Onion='" + sOnion + "',Potatoe='" + sPotatoe + "',Pasta='" + sPasta + "',"
     "Rice='" + sRice + "',Tomatoe='" + sTomatoe + "',Cheese='" + sCheese + "',OliveOil='" + sOliveOil + "',CurryPowder='" + sCurryPowder + "',Salt='" + sSalt + "',"
     "Chocolat='" + sChocolat + "',Strawberry='" + sStrawberry + "',Raspberry='" + sRaspberry + "',Banana='" + sBanana + "',Paprika='" + sPaprika + "',"
     "Oregano='" + sOregano + "',Vinegar='" + sVinegar + "',Beef='" + sBeef + "',Chicken='" + sChicken + "',Salmon='" + sSalmon + "',Lamb= + '" + sLamb + "',"
     "Duck='" + sDuck + "',Celery='" + sCelery + "',Mushroom='" + sMushroom + "',RedPepper='" + sRedPepper + "',GreenPepper='" + sGreenPepper + "',Carrot='" + sCarrot + "',"
     "Coconut='" + sCoconut + "',Fructose='" + sFructose + "',Corn='" + sCorn + "',Turnip='" + sTurnip + "',Peas='" + sPeas + "',Fudge='" + sFudge + "',"
     "Parsnip='" + sParsnip + "',Cauliflower='" + sCauliflower + "',Broccoli='" + sBroccoli + "',Ginger='" + sGinger + "'"
     " where name = '" + sName + "'");


    try{
        if(!query.exec())
        {
           qDebug() << query.lastError().text() << query.lastQuery();
           ui->lblInfo->setText("Unable to update Recipe" + query.lastError().text());
        }
        else{
           if(query.numRowsAffected()>0)
           {
                qDebug() << "Recipe Updated Successfully!";
                ui->lblInfo->setText("Recipe Updated Successfully!");
           }
           else
           {
            qDebug() << " Unable to update Recipe";
            ui->lblInfo->setText("Unable to Update Recipe");
          }
        }
        }
    catch(std::exception & e)
    {
        qDebug() << " Unable to Process Update Query";

    }
}



void MainWindow::on_btnReport_clicked()
{
    ptrRecipeReport->Show();
}

void MainWindow::on_btnClear_clicked()
{
    resetElements();
}

void MainWindow::on_btnFindRecipe_clicked()
{
    QString sName = ui->txtName->text();

    qDebug() << "in init()";
    //QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from recipes where Name like '%" + sName + "%'");

        try
        {

            if(!query.exec())
               qDebug() << query.lastError().text() << query.lastQuery();
            else
            {
               if(query.numRowsAffected()>0)
               {
               qDebug() << "== success query fetch() : " << query.lastQuery();

               }
               else {
                   qDebug() << " No record ! found ";
                   qDebug() << " Query is : " << query.lastQuery();
               }
            }
            while(query.next())
            {
                qDebug()<<query.value(0).toString();
                qDebug() << "== success query fetch() : " << query.lastQuery();
                ui->txtName->setText(query.value(1).toString());
                sType=query.value(2).toString();
                if (sType == "Starter")  { ui->radioStarter->setChecked(true); }
                if (sType == "Main Course")  { ui->radioMain->setChecked(true); }
                if (sType == "Desert")  { ui->radioDesert->setChecked(true); }

                ui->plainTextInstructions->setPlainText(query.value(3).toString());
                ui->horizontalSliderTime->setSliderPosition(query.value(4).toInt());

                if ('Y' == query.value(5).toString())  { ui->checkBoxFlour->setChecked(true); }
                if ('Y' == query.value(6).toString())  { ui->checkBoxParsley->setChecked(true); }
                if ('Y' == query.value(7).toString())  { ui->checkBoxPepper->setChecked(true); }
                if ('Y' == query.value(8).toString())  { ui->checkBoxGarlic->setChecked(true); }
                if ('Y' == query.value(9).toString())  { ui->checkBoxOnion->setChecked(true); }
                if ('Y' == query.value(10).toString())  { ui->checkBoxPotatoe->setChecked(true); }
                if ('Y' == query.value(11).toString())  { ui->checkBoxPasta->setChecked(true); }
                if ('Y' == query.value(12).toString())  { ui->checkBoxEgg->setChecked(true); }
                if ('Y' == query.value(13).toString())  { ui->checkBoxMilk->setChecked(true); }
                if ('Y' == query.value(14).toString())  { ui->checkBoxButter->setChecked(true); }
                if ('Y' == query.value(15).toString())  { ui->checkBoxSuger->setChecked(true); }
                if ('Y' == query.value(16).toString())  { ui->checkBoxCream->setChecked(true); }
                if ('Y' == query.value(17).toString())  { ui->checkBoxTomatoe->setChecked(true); }
                if ('Y' == query.value(18).toString())  { ui->checkBoxCheese->setChecked(true); }
                if ('Y' == query.value(19).toString())  { ui->checkBoxOliveOil->setChecked(true); }
                if ('Y' == query.value(20).toString())  { ui->checkBoxCurryPowder->setChecked(true); }
                if ('Y' == query.value(21).toString())  { ui->checkBoxSalt->setChecked(true); }
                if ('Y' == query.value(22).toString())  { ui->checkBoxChocolat->setChecked(true); }
                if ('Y' == query.value(23).toString())  { ui->checkBoxStrawberry->setChecked(true); }
                if ('Y' == query.value(24).toString())  { ui->checkBoxRaspberry->setChecked(true); }
                if ('Y' == query.value(25).toString())  { ui->checkBoxBanana->setChecked(true); }
                if ('Y' == query.value(26).toString())  { ui->checkBoxGinger->setChecked(true); }
                if ('Y' == query.value(27).toString())  { ui->checkBoxPaprika->setChecked(true); }
                if ('Y' == query.value(28).toString())  { ui->checkBoxOregano->setChecked(true); }
                if ('Y' == query.value(29).toString())  { ui->checkBoxRice->setChecked(true); }
                if ('Y' == query.value(30).toString())  { ui->checkBoxVinegar->setChecked(true); }
                if ('Y' == query.value(31).toString())  { ui->checkBoxBeef->setChecked(true); }
                if ('Y' == query.value(32).toString())  { ui->checkBoxChicken->setChecked(true); }
                if ('Y' == query.value(33).toString())  { ui->checkBoxSalmon->setChecked(true); }
                if ('Y' == query.value(34).toString())  { ui->checkBoxLamb->setChecked(true); }
                if ('Y' == query.value(35).toString())  { ui->checkBoxDuck->setChecked(true); }
                if ('Y' == query.value(36).toString())  { ui->checkBoxCelery->setChecked(true); }
                if ('Y' == query.value(37).toString())  { ui->checkBoxMushroom->setChecked(true); }
                if ('Y' == query.value(38).toString())  { ui->checkBoxRedPepper->setChecked(true); }
                if ('Y' == query.value(39).toString())  { ui->checkBoxGreenPepper->setChecked(true); }
                if ('Y' == query.value(40).toString())  { ui->checkBoxCarrot->setChecked(true); }
                if ('Y' == query.value(41).toString())  { ui->checkBoxCoconut->setChecked(true); }
                if ('Y' == query.value(42).toString())  { ui->checkBoxFructose->setChecked(true); }
                if ('Y' == query.value(43).toString())  { ui->checkBoxCorn->setChecked(true); }
                if ('Y' == query.value(44).toString())  { ui->checkBoxTurnip->setChecked(true); }
                if ('Y' == query.value(45).toString())  { ui->checkBoxPeas->setChecked(true); }
                if ('Y' == query.value(46).toString())  { ui->checkBoxFudge->setChecked(true); }
                if ('Y' == query.value(47).toString())  { ui->checkBoxParsnip->setChecked(true); }
                if ('Y' == query.value(48).toString())  { ui->checkBoxCauliflower->setChecked(true); }
                if ('Y' == query.value(49).toString())  { ui->checkBoxBroccoli->setChecked(true); }
            }

            }
            catch(std::exception & e)
            {
                qDebug() << " Unable to Process Update Query";

            }

}


void MainWindow::resetElements()
{
    ui->txtName->clear();
    ui->horizontalSliderTime->setValue(0);
    ui->plainTextInstructions->clear();
    ui->lblInfo->setText("");

    ui->radioStarter->setChecked(false);
    ui->radioMain->setChecked(false);
    ui->radioDesert->setChecked(false);


    ui->checkBoxFlour->setChecked(false);
    ui->checkBoxParsley->setChecked(false);
    ui->checkBoxPepper->setChecked(false);
    ui->checkBoxGarlic->setChecked(false);
    ui->checkBoxEgg->setChecked(false);
    ui->checkBoxMilk->setChecked(false);
    ui->checkBoxButter->setChecked(false);
    ui->checkBoxSuger->setChecked(false);
    ui->checkBoxCream->setChecked(false);
    ui->checkBoxOnion->setChecked(false);
    ui->checkBoxPotatoe->setChecked(false);
    ui->checkBoxPasta->setChecked(false);
    ui->checkBoxRice->setChecked(false);
    ui->checkBoxTomatoe->setChecked(false);
    ui->checkBoxCheese->setChecked(false);
    ui->checkBoxOliveOil->setChecked(false);
    ui->checkBoxCurryPowder->setChecked(false);
    ui->checkBoxSalt->setChecked(false);
    ui->checkBoxChocolat->setChecked(false);
    ui->checkBoxStrawberry->setChecked(false);
    ui->checkBoxRaspberry->setChecked(false);
    ui->checkBoxGinger->setChecked(false);
    ui->checkBoxPaprika->setChecked(false);
    ui->checkBoxOregano->setChecked(false);
    ui->checkBoxBanana->setChecked(false);
    ui->checkBoxVinegar->setChecked(false);
    ui->checkBoxBeef->setChecked(false);
    ui->checkBoxChicken->setChecked(false);
    ui->checkBoxSalmon->setChecked(false);
    ui->checkBoxDuck->setChecked(false);
    ui->checkBoxLamb->setChecked(false);
    ui->checkBoxCelery->setChecked(false);
    ui->checkBoxMushroom->setChecked(false);
    ui->checkBoxRedPepper->setChecked(false);
    ui->checkBoxGreenPepper->setChecked(false);
    ui->checkBoxCarrot->setChecked(false);
    ui->checkBoxCoconut->setChecked(false);
    ui->checkBoxFructose->setChecked(false);
    ui->checkBoxCorn->setChecked(false);
    ui->checkBoxTurnip->setChecked(false);
    ui->checkBoxPeas->setChecked(false);
    ui->checkBoxFudge->setChecked(false);
    ui->checkBoxParsnip->setChecked(false);
    ui->checkBoxCauliflower->setChecked(false);
    ui->checkBoxBroccoli->setChecked(false);

    }






void MainWindow::on_horizontalSliderTime_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

