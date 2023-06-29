#include "qabstractcluster.h"

QAbstractCluster::QAbstractCluster()
{
    linePoint = NULL;
    pColor = Qt::black;
}

void QAbstractCluster::GetPoints(QVector<QPoint> *points)
{
    points->append(QPoint(x(),y()));

}

void QAbstractCluster::GetCPoints(QVector<QAbstractCluster *> * cpoints)
{
    cpoints->append(this);
}

QString QAbstractCluster::GetName()
{
    return clusterName;
}

void QAbstractCluster::SetName(QString cName)
{
    clusterName = cName;
}

int QAbstractCluster::x()
{
    return 0;
}

int QAbstractCluster::y()
{
    return 0;
}

int QAbstractCluster::GetDepth(int depth)
{
    return depth + 1;
}

float QAbstractCluster::GetMaxHeight(QDrawParametrs *DP, float vol)
{
    return float();
}

int QAbstractCluster::PointCount(int count)
{
    return ++ count;
}

int QAbstractCluster::GetPointCount()
{
    int count = 0;
    return PointCount(count);
}

void QAbstractCluster::DenPaint(QDrawParametrs *DP, float CL, float CT)
{


}

QPointF QAbstractCluster::GetUpperConnectorPoint()
{
    return QPointF(PDraw.DLeft, PDraw.DTop - PDraw.GP->PointHeight / 2.0);
}

QColor QAbstractCluster::GetColor()
{
    return pColor;
}

void QAbstractCluster::SetColor(QColor color)
{
    pColor = color;
}

void QAbstractCluster::SetCutClusterColor(int level, VColor *vcolor, QColor upColor)
{
    if (PDraw.DTop > level - PDraw.GP->CanvasTop)
    {
        pColor = vcolor->GetNewColor();
        PDraw.GP->StatPointsCount ++;

    }
    else pColor = upColor;
    ClearLinePoint();
}

void QAbstractCluster::SetClusterColor(QColor color)
{
    pColor = color;
}

bool QAbstractCluster::Inside(QPoint point)
{
    if ((point.x() >= (PDraw.GP->CanvasLeft + PDraw.DLeft - PDraw.GP->PointWidtht / 2)) &&
            (point.x() <= (PDraw.GP->CanvasLeft + PDraw.DLeft + PDraw.GP->PointWidtht / 2)) &&
            (point.y() >= (PDraw.GP->CanvasTop + PDraw.DTop - PDraw.GP->PointHeight / 2)) &&
            (point.y() <= (PDraw.GP->CanvasTop + PDraw.DTop + PDraw.GP->PointHeight / 2)))
        return true;
    return false;

}

void QAbstractCluster::SetLinePoint(QAbstractCluster *lPoint)
{
    linePoint = lPoint;
}

void QAbstractCluster::ClearLinePoint()
{
    linePoint = NULL;
}

QAbstractCluster *QAbstractCluster::GetLinePoint()
{
    return linePoint;
}

void QAbstractCluster::LineClustering()
{

}

void QAbstractCluster::SetEnableCaption()
{
    EnableCaption = true;
}

