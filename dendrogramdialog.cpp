#include "dendrogramdialog.h"
#include "ui_dendrogramdialog.h"

DendrogramDialog::DendrogramDialog(QMatrixClusters *matrix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendrogramDialog)
{
    ui->setupUi(this);
    dendragram = new cdDendrogram(matrix, this);
    ui->ScrollLayout->addWidget(dendragram);
    connect(matrix, SIGNAL(EndClustering()), this, SLOT(show()));
    connect(dendragram, SIGNAL(DendrogramUpdate()), this, SLOT(DUpdate()));
    connect(ui->ScaleSlider, SIGNAL(valueChanged(int)), dendragram, SLOT(SetScale(int)));
    connect(ui->RatioSlider, SIGNAL(valueChanged(int)), dendragram, SLOT(SetLinkRatio(int)));
    connect(dendragram, SIGNAL(PreSetRatio(int)), ui->RatioSlider, SLOT(setValue(int)));
}

DendrogramDialog::~DendrogramDialog()
{
    delete ui;
}

cdDendrogram *DendrogramDialog::GetDendrogram()
{
   return dendragram;
}

void DendrogramDialog::DUpdate()
{
    ui->labelMethod->setText(dendragram->GetMethodName());
    Update();
}

void DendrogramDialog::SaveSetting(QSettings *settings)
{
    settings->setValue(QLatin1String("WinDendragramGeometry"), geometry());
    dendragram->SaveSetting(settings);
}

void DendrogramDialog::LoadSetting(QSettings *settings)
{
    QRect rect = settings->value(QLatin1String("WinDendragramGeometry"), QRect(0,0,0,0)).toRect();
    if (QRect(0,0,0,0) != rect) setGeometry(rect);

    dendragram->LoadSetting(settings);
}
