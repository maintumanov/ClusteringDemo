#include "qcmatrix.h"


QCMatrix::QCMatrix(QObject *parent) :
    QAbstractTableModel(parent)
{

}

QVariant QCMatrix::data(const QModelIndex &index, int role) const
{
}

bool QCMatrix::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

int QCMatrix::rowCount(const QModelIndex &parent) const
{
}

int QCMatrix::columnCount(const QModelIndex &parent) const
{
}

Qt::ItemFlags QCMatrix::flags(const QModelIndex &index) const
{
}

QVariant QCMatrix::headerData(int section, Qt::Orientation orientation, int role) const
{
}

