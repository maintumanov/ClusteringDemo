#ifndef QCPOINT_H
#define QCPOINT_H

#include "qabstractcluster.h"
#include <QColor>

class QCPoint : public QAbstractCluster
{
private:
    int point_x;
    int point_y;

public:
    void GetPoints(QVector<QPoint> *points);
    QCPoint(int x, int y, QString name);
    int x();
    int y();
    void DenPaint(QDrawParametrs *DP, float CL, float CT);
    QPointF GetUpperConnectorPoint();
    float GetMaxHeight(QDrawParametrs *DP, float vol);


};

#endif // QCPOINT_H
