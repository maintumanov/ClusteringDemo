#ifndef QCLUSTER_H
#define QCLUSTER_H

#include <QColor>
#include <QtCore>
#include "qabstractcluster.h"

class QCluster : public QAbstractCluster
{
    Q_DECLARE_TR_FUNCTIONS(QCluster)
private:
    QAbstractCluster *Cluster1;
    QAbstractCluster *Cluster2;


public:
    explicit QCluster(QAbstractCluster *cluster1, QAbstractCluster *cluster2, QString name);
    ~QCluster();
    void GetPoints(QVector<QPoint> *clusters);
    void GetCPoints(QVector<QAbstractCluster *> *cpoints);
    int GetDepth(int depth);
    float GetMaxHeight(QDrawParametrs *DP, float vol);
    int PointCount(int count);
    void DenPaint(QDrawParametrs *DP, float CL, float CT);
    QPointF GetLeftConnectorPoint();
    void PaintLink(QAbstractCluster *childCluster);
    void SetCutClusterColor(int level, VColor *vcolor, QColor upColor);
    void SetClusterColor(QColor color);
    bool Inside(QPoint point);
    void ClearLinePoint();
    void LineClustering();
    void PaintClusterStatistic();
    float GetPointsDist(QAbstractCluster* p1, QAbstractCluster* p2);

};

#endif // QCLUSTER_H
