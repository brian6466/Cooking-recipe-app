#ifndef RECIPESREPORT_H
#define RECIPESREPORT_H

#include <QDialog>
#include "mydb.h"
#include <QSqlQueryModel>

// namespace declaration is a forward declaration of this ui class

namespace Ui {
class RecipiesReport;
}

class RecipiesReport : public QDialog
{
    Q_OBJECT

public:
    explicit RecipiesReport(QWidget *parent = nullptr);
    ~RecipiesReport();
    void Show();

private:
    Ui::RecipiesReport *ui;
    void updateUI();
};

#endif // RECIPIESREPORT_H
