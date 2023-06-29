#include "methodselectdialog.h"

#include "ui_methodselectdialog.h"

MethodSelectDialog::MethodSelectDialog(QMethodsList *list, QMatrixClusters *matrix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodSelectDialog)
{
    ui->setupUi(this);
    MethodsList = list;
    vspaser = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    matrixmodel = matrix;


    for (int i = 0; i < MethodsList->GetCountMethods(); i ++)
    {

        rbuttons.append(new QRadioButton(MethodsList->GetMethodFromIndex(i)->GetNameMethod(), this));
        ui->ScrollLayout->addWidget(rbuttons.last());
        if (MethodsList->GetIndex() == i) rbuttons.last()->setChecked(true);
       // labels.append(new QLabel(MethodsList->GetMethodFromIndex(i)->GetNoteMethod()));
        //labels.last()->setWordWrap(true);

        //ui->ScrollLayout->addWidget(labels.last());


    }
    ui->ScrollLayout->addSpacerItem(vspaser);
}

MethodSelectDialog::~MethodSelectDialog()
{
    delete ui;
}

void MethodSelectDialog::showEvent(QShowEvent *)
{
    rbuttons[MethodsList->GetIndex()]->setChecked(true);
}

void MethodSelectDialog::on_pushApply_clicked()
{
    for (int i = 0; i < MethodsList->GetCountMethods(); i ++)
    {
        if (rbuttons[i]->isChecked()) MethodsList->SetIndex(i);
        matrixmodel->SetDistanceMetod(MethodsList->GetMethod());
    }
    accept();
}

void MethodSelectDialog::on_pushCancel_clicked()
{
    reject();
}
