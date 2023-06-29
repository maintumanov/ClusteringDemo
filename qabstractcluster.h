#ifndef QABSTRACTCLUSTER_H
#define QABSTRACTCLUSTER_H
#include <QtCore>
#include <QPainter>
#include "vcolor.h"

struct QDrawParametrs {
    float CanvasLeft;
    float CanvasTop;
    float CanvasHeight;
    float CanvasWidth;
    float ClusterHeight;
    float ClusterWidtht;
    float PointHeight;
    float PointWidtht;
    float SpaceHeight;
    float SpaceWidtht;
    float LinkRatio;
    float LinkScale;
    bool EnableLine;
    bool LineSorting;
    int DMode;

    int StatClustersCount;
    int StatClustersDistants;
    int StatPointsCount;
    QPoint ClusterInfoPoint;
    float ClusterDistance;

    QPainter *painter;
};

class QAbstractCluster
{
public:
    struct QPDraw {
        float BLeft;
        float DLeft;
        float DTop;
        QDrawParametrs *GP;
    };

    QAbstractCluster();
    QAbstractCluster *parent;

    QPDraw PDraw;
    float Distance;
    QString clusterName;

    virtual void GetPoints(QVector<QPoint> * points);
    virtual void GetCPoints(QVector<QAbstractCluster *> *cpoints);
    virtual QString GetName();
    virtual void SetName(QString cName);
    virtual int x();
    virtual int y();
    virtual int GetDepth(int depth);
    virtual float GetMaxHeight(QDrawParametrs *DP, float vol);
    virtual int PointCount(int count);
    virtual int GetPointCount();
    virtual void DenPaint(QDrawParametrs *DP, float CL, float CT);
    virtual QPointF GetUpperConnectorPoint();
    virtual QColor GetColor();
    virtual void SetColor(QColor color);
    virtual void SetCutClusterColor(int level, VColor *vcolor, QColor upColor);
    virtual void SetClusterColor(QColor color);
    virtual bool Inside(QPoint point);
    virtual void SetLinePoint(QAbstractCluster *lPoint);
    virtual void ClearLinePoint();
    virtual QAbstractCluster * GetLinePoint();
    virtual void LineClustering();
    virtual void SetEnableCaption();

protected:
    QColor pColor;
    QAbstractCluster *linePoint;
    bool EnableCaption;

};

#endif // QABSTRACTCLUSTER_H
