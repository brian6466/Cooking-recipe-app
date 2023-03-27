#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recipesReport.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

// namespace declaration is a forward declaration of this ui class
// its purpose is to group all your auto-generated windows in one namespace

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddRecipe_clicked();
    void on_btnUpdateRecipe_clicked();
    void on_btnReport_clicked();
    void on_btnFindRecipe_clicked();
    void on_btnClear_clicked();
    void getUserData();

    void on_horizontalSliderTime_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    RecipiesReport *ptrRecipeReport;

    void resetElements();

};

#endif // MAINWINDOW_H
