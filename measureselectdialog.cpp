#include "measureselectdialog.h"
#include "ui_measureselectdialog.h"

MeasureSelectDialog::MeasureSelectDialog(QMeasureList *list, QMatrixClusters *matrix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasureSelectDialog)
{
    ui->setupUi(this);

    MeasureList = list;
    vspaser = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    matrixmodel = matrix;


    for (int i = 0; i < MeasureList->GetCountMeasure(); i ++)
    {
        rbuttons.append(new QRadioButton(MeasureList->GetMeasureFromIndex(i)->GetNameMeasure(), this));
        ui->ScrollLayout->addWidget(rbuttons.last());
        if (MeasureList->GetIndex() == i) rbuttons.last()->setChecked(true);
    }
    ui->ScrollLayout->addSpacerItem(vspaser);
}

MeasureSelectDialog::~MeasureSelectDialog()
{
    delete ui;
}

void MeasureSelectDialog::showEvent(QShowEvent *)
{
    rbuttons[MeasureList->GetIndex()]->setChecked(true);
}

void MeasureSelectDialog::on_pushApply_clicked()
{
    for (int i = 0; i < MeasureList->GetCountMeasure(); i ++)
    {
        if (rbuttons[i]->isChecked()) MeasureList->SetIndex(i);
        matrixmodel->SetDistanceMeasure(MeasureList->GetMeasure());
    }
    accept();
}
