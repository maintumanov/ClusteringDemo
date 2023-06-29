#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "cdcanvas.h"
#include "clistermethod.h"
#include "fviewmatrix.h"
#include "dendrogramdialog.h"
#include "methodselectdialog.h"
#include "measureselectdialog.h"
#include "ui_createdialog.h"
#include "ui_aboutdialog.h"
#include "ui_fillrounddialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
    void showEvent (QShowEvent * );

private slots:
    void SaveSettings();
    void LoadSettings();
    void on_actionViewMatrix_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void closeEvent(QCloseEvent *e);
    void on_actionAbout_triggered();
    void on_actionNew_triggered();
    void ButtonClick();
    void ChangeDistance(float Distance);
    void ShowInfo();
    void on_actionRoundFill_triggered();


private:
    Ui::MainWindow *ui;
    cdCanvas *PointCanvas;
    QMethodsList MethodsList;
    QMeasureList MeasureList;
    DendrogramDialog *Dendrogram;
    MethodSelectDialog *MethodSelect;
    MeasureSelectDialog *MeasureSelect;
    bool ButtonClicked;

};

#endif // MAINWINDOW_H
