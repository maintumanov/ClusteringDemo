#include "qcpoint.h"



QCPoint::QCPoint(int x, int y, QString name)
{
    linePoint = Q_NULLPTR;
    point_x = x;
    point_y = y;
    SetName(name);
}

void QCPoint::GetPoints(QVector<QPoint> *points)
{
    points->append(QPoint(point_x, point_y));
}

int QCPoint::x()
{
    return point_x;
}

int QCPoint::y()
{
    return point_y;
}

void QCPoint::DenPaint(QDrawParametrs *DP, float CL, float )
{
        PDraw.GP = DP;
        PDraw.DLeft = CL + DP->SpaceWidtht;
        PDraw.DTop = DP->CanvasHeight - DP->SpaceHeight;
        DP->painter->setBrush(QBrush(pColor, Qt::SolidPattern));
        DP->painter->setPen(QPen(pColor, 1, Qt::SolidLine));
        DP->painter->drawRect(static_cast<int>(static_cast<double>(PDraw.GP->CanvasLeft + PDraw.DLeft) - static_cast<double>(DP->PointWidtht) / 2.0),
                              static_cast<int>(static_cast<double>(PDraw.GP->CanvasTop + PDraw.DTop) - static_cast<double>(DP->PointHeight) / 2.0),
                              static_cast<int>(DP->PointWidtht), static_cast<int>(DP->PointHeight));

}

QPointF QCPoint::GetUpperConnectorPoint()
{
    return QPointF(static_cast<double>(PDraw.DLeft), static_cast<double>(PDraw.GP->CanvasHeight - PDraw.GP->SpaceHeight) - static_cast<double>(PDraw.GP->PointHeight) / 2.0);
}

float QCPoint::GetMaxHeight(QDrawParametrs *DP, float vol)
{
    return vol + DP->PointHeight + DP->SpaceHeight;
}

