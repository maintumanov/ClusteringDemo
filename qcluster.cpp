#include "qcluster.h"

QCluster::QCluster(QAbstractCluster *cluster1, QAbstractCluster *cluster2, QString name)
{

    parent = Q_NULLPTR;
    linePoint = Q_NULLPTR;
    Cluster1 = cluster1;
    Cluster2 = cluster2;
    Cluster1->parent = this;
    Cluster2->parent = this;
    SetName(name);
}

QCluster::~QCluster()
{

}

void QCluster::GetPoints(QVector<QPoint> *clusters)
{
    Cluster1->GetPoints(clusters);
    Cluster2->GetPoints(clusters);
}

void QCluster::GetCPoints(QVector<QAbstractCluster *> *cpoints)
{
    Cluster1->GetCPoints(cpoints);
    Cluster2->GetCPoints(cpoints);
}

int QCluster::GetDepth(int depth)
{
    int df1, df2;
    df1 = Cluster1->GetDepth(depth) + 1;
    df2 = Cluster2->GetDepth(depth) + 1;
    if (df1 > df2) return df1;
    return df2;
}

float QCluster::GetMaxHeight(QDrawParametrs *DP, float vol)
{
    float hg1, hg2;
    hg1 = Cluster1->GetMaxHeight(DP, vol);
    hg2 = Cluster2->GetMaxHeight(DP, vol);
    if (hg1 < hg2) hg1 = hg2;
    return hg1 + Distance * DP->LinkRatio * DP->LinkScale + DP->ClusterHeight + DP->SpaceHeight;
}

int QCluster::PointCount(int count)
{
    int cnt = count;
    cnt = Cluster1->PointCount(cnt);
    cnt = Cluster2->PointCount(cnt);
    return cnt;
}

void QCluster::DenPaint(QDrawParametrs *DP, float CL, float )
{
    PDraw.GP = DP;
    PDraw.BLeft = CL + (DP->PointWidtht + DP->SpaceWidtht) * static_cast<float>(Cluster1->GetPointCount());
    PDraw.DTop = DP->CanvasHeight - GetMaxHeight(DP, 0) + DP->SpaceHeight;
    Cluster1->DenPaint(DP, CL, PDraw.DTop + DP->SpaceHeight);
    Cluster2->DenPaint(DP, PDraw.BLeft, PDraw.DTop + DP->SpaceHeight);

    PDraw.DLeft = (static_cast<float>(Cluster2->GetUpperConnectorPoint().x()) + static_cast<float>(Cluster1->GetUpperConnectorPoint().x())) / 2;

    DP->painter->setBrush(QBrush(pColor, Qt::SolidPattern));
    DP->painter->setPen(QPen(pColor, 1, Qt::SolidLine));
    DP->painter->drawEllipse(static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft + PDraw.DLeft) - static_cast<double>(DP->ClusterWidtht) / 2.0),
                             static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop + PDraw.DTop) - static_cast<double>(DP->ClusterHeight) / 2.0),
                             static_cast<int>(DP->ClusterWidtht), static_cast<int>(DP->ClusterHeight));

    if (PDraw.GP->DMode == 2 && EnableCaption)
    {
        PDraw.GP->ClusterInfoPoint = QPoint(static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft + PDraw.DLeft) + static_cast<double>(DP->ClusterHeight) / 2.0),
                                            static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop + PDraw.DTop) - static_cast<double>(DP->ClusterWidtht) / 2.0));
        PDraw.GP->ClusterDistance = Distance;
        PDraw.GP->StatPointsCount = Cluster1->GetPointCount() + Cluster2->GetPointCount();
    }

    PaintLink(Cluster1);
    PaintLink(Cluster2);
}

QPointF QCluster::GetLeftConnectorPoint()
{
    return QPointF(static_cast<qreal>(PDraw.DLeft) - static_cast<qreal>(PDraw.GP->PointHeight) / 2.0, static_cast<qreal>(PDraw.DTop));
}

void QCluster::PaintLink(QAbstractCluster *childCluster)
{
    PDraw.GP->painter->setBrush(QBrush(pColor, Qt::SolidPattern));
    PDraw.GP->painter->setPen(QPen(pColor, 1, Qt::SolidLine));
    QPointF childPoint = childCluster->GetUpperConnectorPoint();
    QPointF thisPoint;
    if (childPoint.x() < static_cast<qreal>(PDraw.DLeft))
        thisPoint = QPointF(static_cast<qreal>(PDraw.DLeft) - static_cast<qreal>(PDraw.GP->PointHeight) / 2.0, static_cast<qreal>(PDraw.DTop));
    else
        thisPoint = QPointF(static_cast<qreal>(PDraw.DLeft) + static_cast<qreal>(PDraw.GP->PointHeight) / 2.0, static_cast<qreal>(PDraw.DTop));

    PDraw.GP->painter->drawLine(static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft) + thisPoint.x()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop) + thisPoint.y()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft) + childPoint.x()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop) + thisPoint.y()));
    PDraw.GP->painter->drawLine(static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft) + childPoint.x()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop) + thisPoint.y()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft) + childPoint.x()),
                                static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop) + childPoint.y()));
}

void QCluster::SetCutClusterColor(int level, VColor *vcolor, QColor upColor)
{
    if (PDraw.DTop > level - PDraw.GP->CanvasTop)  {
        SetClusterColor(vcolor->GetNewColor());
        PDraw.GP->StatClustersCount ++;
        if (PDraw.GP->EnableLine) LineClustering();
    }
    else
    {
        pColor = upColor;
        Cluster1->SetCutClusterColor(level, vcolor, upColor);
        Cluster2->SetCutClusterColor(level, vcolor, upColor);
    }
}

void QCluster::SetClusterColor(QColor color)
{
    EnableCaption = false;
    pColor = color;
    Cluster1->SetClusterColor(pColor);
    Cluster2->SetClusterColor(pColor);
}

bool QCluster::Inside(QPoint point)
{
    if ((point.x() >= (PDraw.GP->CanvasLeft + PDraw.DLeft - PDraw.GP->ClusterWidtht / 2)) &&
            (point.x() <= (PDraw.GP->CanvasLeft + PDraw.DLeft + PDraw.GP->ClusterWidtht / 2)) &&
            (point.y() >= (PDraw.GP->CanvasTop + PDraw.DTop - PDraw.GP->ClusterWidtht / 2)) &&
            (point.y() <= (PDraw.GP->CanvasTop + PDraw.DTop + PDraw.GP->ClusterWidtht / 2)))
        return true;
    return false;
}

void QCluster::ClearLinePoint()
{
    Cluster1->ClearLinePoint();
    Cluster2->ClearLinePoint();
}

void QCluster::LineClustering()
{

    if (!PDraw.GP->EnableLine) return;
    QVector<QAbstractCluster*> p;
    GetCPoints(&p);

    // sorting
    float min = 0;
    QAbstractCluster* tmp;

    for (int i = 0; i < p.count() - 1; i ++)
    {
        min = GetPointsDist(p[i],p[i+1]);
        for (int j = i + 1; j < p.count(); j ++)
            if (GetPointsDist(p[i],p[j]) < min)
            {
                tmp = p[j];
                p[j] = p[i + 1];
                p[i + 1] = tmp;
                min = GetPointsDist(p[i],p[i+1]);
            }
    }
    //=======

    for (int i = 0; i < p.count() - 1; i ++)
        p[i + 1]->SetLinePoint(p[i]);


}

void QCluster::PaintClusterStatistic()
{

}

float QCluster::GetPointsDist(QAbstractCluster *p1, QAbstractCluster *p2)
{
    return static_cast<float>(sqrt((p1->x() - p2->x()) * (p1->x() - p2->x()) +
                (p1->y() - p2->y()) * (p1->y() - p2->y())));
}


