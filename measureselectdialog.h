#ifndef MEASURESELECTDIALOG_H
#define MEASURESELECTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QRadioButton>
#include <QSpacerItem>
#include "qmatrixclusters.h"
#include "clustermeasure.h"

namespace Ui {
class MeasureSelectDialog;
}

class MeasureSelectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MeasureSelectDialog(QMeasureList *list, QMatrixClusters *matrix, QWidget *parent = Q_NULLPTR);
    ~MeasureSelectDialog();
    void showEvent (QShowEvent * e);
    
private slots:
    void on_pushApply_clicked();

private:
    Ui::MeasureSelectDialog *ui;
    QMatrixClusters *matrixmodel;
    QMeasureList *MeasureList;
    QVector<QRadioButton *> rbuttons;
    QSpacerItem *vspaser;
};

#endif // MEASURESELECTDIALOG_H
