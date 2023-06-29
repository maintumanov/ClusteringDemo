#include "qmatrixclusters.h"

QMatrixClusters::QMatrixClusters(QObject *parent) :
    QAbstractTableModel(parent)
{
    ClusterNameIncrement = 0;
    rootCluster = Q_NULLPTR;
}

QVariant QMatrixClusters::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())  return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(MatrixDistances[index.row()][index.column()]);
    return QVariant();
}

int QMatrixClusters::rowCount(const QModelIndex &) const
{
    return RowHeaderMatrix.count();
}

int QMatrixClusters::columnCount(const QModelIndex &) const
{
    return ColumnHeaderMatrix.count();
}

QVariant QMatrixClusters::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal)
        return  ColumnHeaderMatrix[section]->GetName();
    else return  RowHeaderMatrix[section]->GetName();
}

void QMatrixClusters::IntMatrix(QVector<QCPoint *> *points)
{
    Clear();
    int sizeMatrix = points->count();
    int i = 0;
    RowHeaderMatrix.resize(sizeMatrix);
    ColumnHeaderMatrix.resize(sizeMatrix);
    MatrixDistances.resize(sizeMatrix);
    for (i = 0; i < sizeMatrix; i ++)
    {
        ColumnHeaderMatrix[i] = points->at(i);
        RowHeaderMatrix[i] = points->at(i);
        MatrixDistances[i].resize(sizeMatrix);
    }
    FillDistancesPoints();
}

QAbstractCluster *QMatrixClusters::GetRootCluster()
{
    return rootCluster;
}

QAbstractCluster *QMatrixClusters::GetClusterFromPoint(QPoint point)
{
    int i = 0;
    while (i < Clusters.count())
    {
        if (Clusters[i]->Inside(point)) return Clusters[i];
        i ++;
    }
    return Q_NULLPTR;
}

ClisterMethod *QMatrixClusters::GetDistanceMethod()
{
    return DistanceMethod;
}

ClusterMeasure *QMatrixClusters::GetDistanceMeasure()
{
    return DistanceMeasure;
}

void QMatrixClusters::SetDistanceMetod(ClisterMethod *cmethod)
{
    DistanceMethod = cmethod;
}

void QMatrixClusters::SetDistanceMeasure(ClusterMeasure *cmeasure)
{
    DistanceMeasure = cmeasure;
}


void QMatrixClusters::AutoClustering(QVector<QCPoint *> *points)
{
    IntMatrix(points);
    while (RowHeaderMatrix.count() > 1)
        CreateClasterFromItemMatrix(FindMinimum());
    if (SetRootCluster())  EndClustering();
}

void QMatrixClusters::Clustering()
{
    while (RowHeaderMatrix.count() > 1)
        CreateClasterFromItemMatrix(FindMinimum());
    SetRootCluster();
}

bool QMatrixClusters::SetRootCluster()
{
    bool res = (RowHeaderMatrix.count() == 1);
    if (res) rootCluster = RowHeaderMatrix[0];
    else rootCluster = Q_NULLPTR;
    ChangeDatagram(res);
    return res;
}

void QMatrixClusters::CreateClasterFromItemMatrix(QPoint matrixItem)
{
    QCluster *cluster = new QCluster(RowHeaderMatrix[matrixItem.x()],
                                     RowHeaderMatrix[matrixItem.y()],
                                     QString("M%1").arg(ClusterNameIncrement++));
    Clusters.append(cluster);
    cluster->Distance = MatrixDistances[matrixItem.x()][matrixItem.y()];

    int index = AppendMatrixColRow(cluster);

    for (int i = 0; i < RowHeaderMatrix.count(); i ++)
    {
        MatrixDistances[i][index] = DistanceMethod->GetDistanceMethod(MatrixDistances[i][matrixItem.x()],
                                                                      MatrixDistances[i][matrixItem.y()],
                                                                      cluster->Distance,
                                                                      RowHeaderMatrix[matrixItem.x()]->GetPointCount(),
                                                                      RowHeaderMatrix[matrixItem.y()]->GetPointCount());
        MatrixDistances[index][i] = MatrixDistances[i][index];
    }

    DeleteItem(matrixItem);

}

void QMatrixClusters::FillDistancesPoints()
{
    int r, c;
    for (r = 0; r < RowHeaderMatrix.count(); r ++)
        for (c = 0; c < ColumnHeaderMatrix.count(); c ++)
            MatrixDistances[r][c] = GetDistancePoints(RowHeaderMatrix[r], ColumnHeaderMatrix[c]);
}

void QMatrixClusters::ClustersClear()
{
    while (!Clusters.isEmpty())
    {
        delete Clusters.last();
        Clusters.removeLast();
    }
}

void QMatrixClusters::MatrixClear()
{
    RowHeaderMatrix.clear();
    ColumnHeaderMatrix.clear();
    MatrixDistances.clear();
}

void QMatrixClusters::Clear()
{
    if (rootCluster != Q_NULLPTR)
    {
        rootCluster->ClearLinePoint();
        rootCluster->SetClusterColor(Qt::black);
    }
    rootCluster = Q_NULLPTR;
    MatrixClear();
    ClustersClear();
    ChangeDatagram(false);
}

float QMatrixClusters::GetDistancePoints(QAbstractCluster *p1, QAbstractCluster *p2)
{
    return DistanceMeasure->GetDistanceMeasure(
                QPoint(p1->x(), p1->y()),
                QPoint(p2->x(), p2->y()));
}

QPoint QMatrixClusters::FindMinimum()
{
    if (MatrixDistances.count() < 2) return QPoint(0,0);
    int r,c;
    QPoint res = QPoint(0,1);
    float dmin = MatrixDistances[0][1];

    int mSize = MatrixDistances.count();
    for (r = 0; r < mSize; r ++)
        for (c = r + 1; c < mSize; c ++)
            if (dmin > MatrixDistances[r][c])
            {
                dmin = MatrixDistances[r][c];
                res = QPoint(r,c);
            }
    return res;
}

void QMatrixClusters::DeleteMatrixRow(int row)
{
    for (int i = row; i < RowHeaderMatrix.count() - 1; i ++)
        RowHeaderMatrix[i] = RowHeaderMatrix[i + 1];
    RowHeaderMatrix.resize(RowHeaderMatrix.count() - 1);

    for (int i = row; i < MatrixDistances.count() - 1; i ++)
        MatrixDistances[i] = MatrixDistances[i + 1];
    MatrixDistances.resize(MatrixDistances.count() - 1);
}

void QMatrixClusters::DeleteMatrixColumn(int col)
{
    for (int i = col; i < ColumnHeaderMatrix.count() - 1; i ++)
        ColumnHeaderMatrix[i] = ColumnHeaderMatrix[i + 1];
    ColumnHeaderMatrix.resize(ColumnHeaderMatrix.count() - 1);

    for (int j = 0; j < MatrixDistances.count(); j ++)
    {
        for (int i = col; i < MatrixDistances[j].count() - 1; i ++)
            MatrixDistances[j][i] = MatrixDistances[j][i + 1];
        MatrixDistances[j].resize(MatrixDistances[j].count() - 1);
    }
}

void QMatrixClusters::DeleteItem(QPoint matrixItem)
{
    if (matrixItem.x() < matrixItem.y()) {
        DeleteMatrixRow(matrixItem.y());
        DeleteMatrixColumn(matrixItem.y());
        DeleteMatrixRow(matrixItem.x());
        DeleteMatrixColumn(matrixItem.x());
        return;
    }
    if (matrixItem.x() == matrixItem.y()) {
        DeleteMatrixRow(matrixItem.x());
        DeleteMatrixColumn(matrixItem.y());
        return;
    }
    DeleteMatrixRow(matrixItem.x());
    DeleteMatrixColumn(matrixItem.x());
    DeleteMatrixRow(matrixItem.y());
    DeleteMatrixColumn(matrixItem.y());
}

int QMatrixClusters::AppendMatrixColRow(QAbstractCluster *cluster)
{
    int newSize = MatrixDistances.count() + 1;
    MatrixDistances.resize(newSize);
    for (int i = 0; i < newSize; i ++)
        MatrixDistances[i].resize(newSize);
    ColumnHeaderMatrix.append(cluster);
    RowHeaderMatrix.append(cluster);
    return newSize - 1;
}


