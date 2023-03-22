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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrRecipeReport = new RecipiesReport(this);

    this->setFixedSize(750, 750);


    setWindowTitle(tr("Group Boxes"));
    resize(750, 750);
}




    //! [0]

    //! [1]

    //! [3]

    //! [4]

    //! [6]

    //! [7]

    //! [13]


MainWindow::~MainWindow()
{
    delete ui;
    delete ptrRecipeReport;
     MyDB::ResetInstance();
}

void MainWindow::on_btnAddRecipe_clicked()
{
    //
    ui->lblInfo->setText("test");
    QString sName = ui->txtName->text();
    QString sFlour = ui->txtName->text();
    //QString sFlour = ui->checkBoxFlour->text();


    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();
    query.prepare("insert into recepies(Name, Flour) values ('" + sName +"','" +sFlour + "')");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add Recipe");
        //resetElements();
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
    //ptrAddRecipe->Show();
}

void MainWindow::on_btnUpdateRecipe_clicked()
{
    ui->lblInfo->clear();
    QString sName = ui->txtName->text();
    //QString sStatus = ui->cmbStatus->currentText();

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("update recepies set name='" + sName + "' where name = '" + sName + "'");

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



void MainWindow::on_btnReport_clicked()
{
    ptrRecipeReport->Show();
}



void MainWindow::on_btnFindRecipe_clicked()
{
    QString sName = ui->txtName->text();
    /*QString sCriteriaColum = "";

    if(ui->rdoId->isChecked())
        sCriteriaColum="Name";
    else if (ui->rdoName->isChecked())
        sCriteriaColum="Name";
    else if (ui->rdoQuantity->isChecked())
        sCriteriaColum="Name";
    else if (ui->rdoSellingPrice->isChecked())
        sCriteriaColum = "Name";
    else
        sCriteriaColum = "Name";*/

    qDebug() << "in init()";
    //QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from recipies where Name like '%" + sName + "%'");

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
       if(query.numRowsAffected()>0)
       qDebug() << "== success query fetch() : " << query.lastQuery();
       else {
           qDebug() << " No record ! found ";
           qDebug() << " Query is : " << query.lastQuery();
       }
    }
    while(query.next())
    qDebug()<<query.value(0).toString();

    /*model->setQuery(query);
    ui->tableView->setModel(model);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();*/
}

void MainWindow::resetElements()
{
    ui->txtName->clear();

}
