#include "fviewdendrogram.h"
#include "ui_fviewdendrogram.h"

FViewDendrogram::FViewDendrogram(QMatrixClusters *matrix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FViewDendrogram)
{
    ui->setupUi(this);
    dendragram = new cdDendrogram(matrix, this);
    ui->MainLayout->addWidget(dendragram);
}

FViewDendrogram::~FViewDendrogram()
{
    delete ui;
}
