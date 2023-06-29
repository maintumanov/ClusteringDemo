#ifndef FVIEWMATRIX_H
#define FVIEWMATRIX_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class FViewMatrix;
}

class FViewMatrix : public QDialog
{
    Q_OBJECT
    
public:
    explicit FViewMatrix(QAbstractTableModel *modelTable, QWidget *parent = 0);
    ~FViewMatrix();
    
private:
    Ui::FViewMatrix *ui;
};

#endif // FVIEWMATRIX_H
