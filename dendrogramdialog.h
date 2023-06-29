#ifndef DENDROGRAMDIALOG_H
#define DENDROGRAMDIALOG_H

#include <QDialog>
#include "qmatrixclusters.h"
#include "cddendrogram.h"

namespace Ui {
class DendrogramDialog;
}

class DendrogramDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DendrogramDialog(QMatrixClusters *matrix, QWidget *parent = 0);
    ~DendrogramDialog();
    cdDendrogram *GetDendrogram();

signals:
    void Update();

public slots:
    void SaveSetting(QSettings *settings);
    void LoadSetting(QSettings *settings);


private slots:
    void DUpdate();
    
private:
    Ui::DendrogramDialog *ui;
        cdDendrogram *dendragram;
};

#endif // DENDROGRAMDIALOG_H
