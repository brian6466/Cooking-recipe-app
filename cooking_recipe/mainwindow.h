#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recipesReport.h"
#include <QWidget>
#include <QMessageBox>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
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

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void on_btnAddRecipe_clicked();
    void on_btnUpdateRecipe_clicked();
    void on_btnReport_clicked();
    void on_btnFindRecipe_clicked();
    void on_btnClear_clicked();
    void getUserData();
    void on_btnShowNotesMenu_clicked();

    void on_horizontalSliderTime_valueChanged(int value);
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();
private:
    Ui::MainWindow *ui;
    RecipiesReport *ptrRecipeReport;


    void resetElements();

    void createActions();
    void createMenus();
    //! [2]

    //! [3]
        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *formatMenu;
        QMenu *helpMenu;
        QActionGroup *alignmentGroup;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *printAct;
        QAction *exitAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
        QAction *boldAct;
        QAction *italicAct;
        QAction *leftAlignAct;
        QAction *rightAlignAct;
        QAction *justifyAct;
        QAction *centerAct;
        QAction *setLineSpacingAct;
        QAction *setParagraphSpacingAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
        QLabel *infoLabel;

};

#endif // MAINWINDOW_H
