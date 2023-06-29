#include "fviewmatrix.h"
#include "ui_fviewmatrix.h"

FViewMatrix::FViewMatrix(QAbstractTableModel *modelTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FViewMatrix)
{
    ui->setupUi(this);
    ui->tableView->setModel(modelTable);
}

FViewMatrix::~FViewMatrix()
{
    delete ui;
}

