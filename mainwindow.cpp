#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PointCanvas = new cdCanvas(this);
    ui->MainLayout->addWidget(PointCanvas);
    Dendrogram = new DendrogramDialog(PointCanvas->GetMatrixModel(), this);
    MethodSelect = new MethodSelectDialog(&MethodsList, PointCanvas->GetMatrixModel(), this);
    MeasureSelect = new MeasureSelectDialog(&MeasureList, PointCanvas->GetMatrixModel(), this);

    PointCanvas->SetClusterMethod(MethodsList.GetMethod());
    PointCanvas->SetClusterMeasure(MeasureList.GetMeasure());
    connect(ui->actionClustering, SIGNAL(triggered()), PointCanvas, SLOT(AutoClustering()));
    connect(ui->actionViewDendrogram, SIGNAL(triggered()), Dendrogram, SLOT(show()));
    connect(Dendrogram, SIGNAL(Update()), PointCanvas, SLOT(repaint()));
    connect(ui->actionClear, SIGNAL(triggered()), PointCanvas, SLOT(Clear()));
    connect(ui->actionMethod, SIGNAL(triggered()), MethodSelect, SLOT(exec()));
    connect(ui->actionMeasure, SIGNAL(triggered()), MeasureSelect, SLOT(exec()));
    connect(PointCanvas, SIGNAL(CursorChangeDistance(float)), this, SLOT(ChangeDistance(float)));
    connect(PointCanvas, SIGNAL(CursorNoDistance()), this, SLOT(ShowInfo()));
    connect(MethodSelect, SIGNAL(accepted()), this, SLOT(ShowInfo()));
    connect(MeasureSelect, SIGNAL(accepted()), this, SLOT(ShowInfo()));
    connect(MethodSelect, SIGNAL(accepted()), PointCanvas->GetMatrixModel(), SLOT(Clear()));
    connect(MeasureSelect, SIGNAL(accepted()), PointCanvas->GetMatrixModel(), SLOT(Clear()));
    connect(ui->actionLine, SIGNAL(triggered(bool)), PointCanvas, SLOT(SetEnableLines(bool)));
    connect(ui->actionNet, SIGNAL(triggered(bool)), PointCanvas, SLOT(SetEnableGrid(bool)));
    ShowInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    LoadSettings();
}

void MainWindow::SaveSettings()
{
    QSettings Settings;
    Settings.setValue(QLatin1String("WindowGeometry"), geometry());
    Settings.setValue(QLatin1String("indexMethod"), MethodsList.GetIndex());
    Settings.setValue(QLatin1String("indexMeasure"), MeasureList.GetIndex());
    Settings.setValue(QLatin1String("EnableLines"), ui->actionLine->isChecked());
    Settings.setValue(QLatin1String("EnableGrid"), ui->actionNet->isChecked());
    Dendrogram->SaveSetting(&Settings);
    PointCanvas->SaveSetting(&Settings);
}

void MainWindow::LoadSettings()
{
    QSettings Settings;
    QRect rect = Settings.value(QLatin1String("WindowGeometry"), QRect(0,0,0,0)).toRect();
    if (QRect(0,0,0,0) != rect) setGeometry(rect);
    MethodsList.SetIndex(Settings.value(QLatin1String("indexMethod"), MethodsList.GetIndex()).toInt());
    MeasureList.SetIndex(Settings.value(QLatin1String("indexMeasure"), MeasureList.GetIndex()).toInt());
    ui->actionLine->setChecked(Settings.value(QLatin1String("EnableLines"), true).toBool());
    PointCanvas->SetEnableLines(ui->actionLine->isChecked());
    ui->actionNet->setChecked(Settings.value(QLatin1String("EnableGrid"), false).toBool());
    PointCanvas->SetEnableGrid(ui->actionNet->isChecked());
    Dendrogram->LoadSetting(&Settings);
    PointCanvas->LoadSetting(&Settings);

    PointCanvas->GetMatrixModel()->SetDistanceMetod(MethodsList.GetMethod());
    PointCanvas->GetMatrixModel()->SetDistanceMeasure(MeasureList.GetMeasure());

    ShowInfo();
}



void MainWindow::on_actionViewMatrix_triggered()
{
    FViewMatrix FMatric(PointCanvas->GetMatrixModel(), this);
    FMatric.exec();

}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("Clusters (*.Clu);;"));

    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file!"), file.errorString());
        return;
    }
    PointCanvas->SaveToFile(&file);

    file.close();

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Clusters (*.Clu);;"));

    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file!"), file.errorString());
        return;
    }
    PointCanvas->LoadFromFile(&file);
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    SaveSettings();
}

void MainWindow::on_actionAbout_triggered()
{
    QDialog *dialog = new QDialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(dialog);
    dialog->exec();
    delete dialog;

}

void MainWindow::on_actionNew_triggered()
{
    QDialog *dialog = new QDialog(this);
    Ui::CreateDialog ui;
    ui.setupUi(dialog);
    ButtonClicked = false;
    connect(ui.pushButtonHapply, SIGNAL(clicked()), this, SLOT(ButtonClick()));
    connect(ui.pushButtonHapply, SIGNAL(clicked()), dialog, SLOT(close()));
    ui.spinMaxY->setValue(PointCanvas->GetHolstHeight());
    ui.spinMaxX->setValue(PointCanvas->GetHolstWidht());
    ui.spinRadius->setValue(PointCanvas->GetHolstPointR());
    dialog->exec();
    if (ButtonClicked)
    {
        PointCanvas->Clear();
        PointCanvas->SetHolstHeight(ui.spinMaxY->value());
        PointCanvas->SetHolstWitdht(ui.spinMaxX->value());
        PointCanvas->SetHolstPointR(ui.spinRadius->value());
        PointCanvas->repaint();
    }
    disconnect(ui.pushButtonHapply, SIGNAL(clicked()), this, SLOT(ButtonClick()));
    delete dialog;

}

void MainWindow::ButtonClick()
{
    ButtonClicked = true;
}

void MainWindow::ChangeDistance(float Distance)
{
    ui->statusBar->showMessage(QString(tr("Distance (%1): %2"))
                               .arg(PointCanvas->GetMatrixModel()->GetDistanceMeasure()->GetNameMeasure())
                               .arg(static_cast<double>(Distance)));
}

void MainWindow::ShowInfo()
{
    ui->statusBar->showMessage(QString(tr("%1/%2"))
                               .arg(PointCanvas->GetMatrixModel()->GetDistanceMethod()->GetNameMethod())
                               .arg(PointCanvas->GetMatrixModel()->GetDistanceMeasure()->GetNameMeasure()));
}

void MainWindow::on_actionRoundFill_triggered()
{
    QDialog *dialog = new QDialog(this);
    Ui::FillRoundDialog ui;
    ui.setupUi(dialog);
    ButtonClicked = false;
    connect(ui.buttonFill, SIGNAL(clicked()), this, SLOT(ButtonClick()));
    connect(ui.buttonFill, SIGNAL(clicked()), dialog, SLOT(close()));
    dialog->exec();
    if (ButtonClicked)
    {
        PointCanvas->AutoFill(ui.spinBox->value());
    }
    disconnect(ui.buttonFill, SIGNAL(clicked()), this, SLOT(ButtonClick()));
    delete dialog;
}

