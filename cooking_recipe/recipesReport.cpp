#include "recipesReport.h"
#include "ui_recipesreport.h"

RecipiesReport::RecipiesReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipiesReport)
{
    ui->setupUi(this);
}

RecipiesReport::~RecipiesReport()
{
    delete ui;
}

void RecipiesReport::Show()
{
    updateUI();
    this->show();
}

void RecipiesReport::updateUI()
{
       qDebug() << "in init()";
       QSqlQueryModel * model = new QSqlQueryModel(this);

       QSqlQuery query( MyDB::getInstance()->getDBInstance());
       query.prepare("select * from recipes order by Id desc");

       if(!query.exec())
          qDebug() << query.lastError().text() << query.lastQuery();
       else
          qDebug() << "== success query fetch()";

       while(query.next())
       qDebug()<<query.value(0).toString();

       model->setQuery(query);
       ui->tableView->setModel(model);
       qDebug() << "rows are : " << model->rowCount();
       ui->tableView->show();
}
