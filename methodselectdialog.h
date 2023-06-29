#ifndef METHODSELECTDIALOG_H
#define METHODSELECTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QRadioButton>
#include <QSpacerItem>
#include "qmatrixclusters.h"
#include "clistermethod.h"

namespace Ui {
class MethodSelectDialog;
}

class MethodSelectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MethodSelectDialog(QMethodsList *list, QMatrixClusters *matrix, QWidget *parent = Q_NULLPTR);
    ~MethodSelectDialog();
    void showEvent (QShowEvent * e);
    
private slots:
    void on_pushApply_clicked();
    void on_pushCancel_clicked();

private:
    Ui::MethodSelectDialog *ui;
    QMatrixClusters *matrixmodel;
    QMethodsList *MethodsList;
    QVector<QRadioButton *> rbuttons;
    QSpacerItem *vspaser;
};

#endif // METHODSELECTDIALOG_H
