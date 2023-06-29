#ifndef QMATRIXCLUSTERS_H
#define QMATRIXCLUSTERS_H

#include <QAbstractTableModel>
#include "clistermethod.h"
#include "clustermeasure.h"
#include "qabstractcluster.h"
#include "qcluster.h"
#include "qcpoint.h"

class QMatrixClusters : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QMatrixClusters(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void IntMatrix(QVector<QCPoint *> *points);
    QAbstractCluster *GetRootCluster();
    QAbstractCluster *GetClusterFromPoint(QPoint point);
    ClisterMethod *GetDistanceMethod();
    ClusterMeasure *GetDistanceMeasure();

signals:
    void ChangeDatagram(bool EnableView);
    void EndClustering();
    
public slots:
    void SetDistanceMetod(ClisterMethod *cmethod);
    void SetDistanceMeasure(ClusterMeasure *cmeasure);
    void Clustering();
    void AutoClustering(QVector<QCPoint *> *points);
    void CreateClasterFromItemMatrix(QPoint matrixItem);
    void Clear();

private:
    QVector< QAbstractCluster *> RowHeaderMatrix;
    QVector< QAbstractCluster *> ColumnHeaderMatrix;
    QVector< QVector<float> > MatrixDistances;
    ClisterMethod *DistanceMethod;
    ClusterMeasure *DistanceMeasure;
    QAbstractCluster *rootCluster;
    QList<QAbstractCluster*> Clusters;
    int ClusterNameIncrement;
    void FillDistancesPoints();
    void ClustersClear();
    void MatrixClear();

    float GetDistancePoints(QAbstractCluster *p1, QAbstractCluster *p2);
    QPoint FindMinimum();
    void DeleteMatrixRow(int row);
    void DeleteMatrixColumn(int col);
    void DeleteItem(QPoint matrixItem);
    int AppendMatrixColRow(QAbstractCluster *cluster);
    bool SetRootCluster();

    
};

#endif // QMATRIXCLUSTERS_H
