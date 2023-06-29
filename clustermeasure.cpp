#include "clustermeasure.h"

ClusterMeasure::ClusterMeasure()
{
}

float ClusterMeasure::GetDistanceMeasure(QPoint , QPoint )
{
    return float();
}

QString ClusterMeasure::GetNameMeasure()
{
    return QString();
}

//========
QMeasureList::QMeasureList()
{
    CurrenIndex = 0;
    measure.append(new EuclideanMeasure());
    measure.append(new HemetMeasure());
    measure.append(new ChebyshevMeasure());
    measure.append(new PeakDistanceMeasure());
}

ClusterMeasure *QMeasureList::GetMeasureFromIndex(int index)
{
    return measure[index];
}

ClusterMeasure *QMeasureList::GetMeasure()
{
    return measure[CurrenIndex];
}

int QMeasureList::GetCountMeasure()
{
    return measure.count();
}

int QMeasureList::GetIndex()
{
    return CurrenIndex;
}

void QMeasureList::SetIndex(int index)
{
    CurrenIndex = index;
}

//====================================================

float EuclideanMeasure::GetDistanceMeasure(QPoint p1, QPoint p2)
{
    return static_cast<float>(sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) +
                (p1.y() - p2.y()) * (p1.y() - p2.y())));
}

QString EuclideanMeasure::GetNameMeasure()
{
    return tr("Euclid's Measure");
}

float HemetMeasure::GetDistanceMeasure(QPoint p1, QPoint p2)
{
    return abs((p1.x() - p2.x()) + (p1.y() - p2.y()));
}

QString HemetMeasure::GetNameMeasure()
{
    return tr("Hamming Measure");
}

float ChebyshevMeasure::GetDistanceMeasure(QPoint p1, QPoint p2)
{
    if (abs(p1.x() - p2.x()) > abs(p1.y() - p2.y())) return abs(p1.x() - p2.x());
    else return abs(p1.y() - p2.y());
}

QString ChebyshevMeasure::GetNameMeasure()
{
    return tr("Chebyshev Measure");
}

float PeakDistanceMeasure::GetDistanceMeasure(QPoint p1, QPoint p2)
{
    return (abs(p1.x() - p2.x())/static_cast<float>((p1.x() + p2.x()) + abs(p1.y() - p2.y())/static_cast<float>(p1.y() + p2.y())));
}

QString PeakDistanceMeasure::GetNameMeasure()
{
    return tr("Peak range");
}

