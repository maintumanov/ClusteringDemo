#ifndef CLUSTERMEASURE_H
#define CLUSTERMEASURE_H

#include <QtCore>

class ClusterMeasure
{
public:
    ClusterMeasure();
    virtual float GetDistanceMeasure(QPoint p1, QPoint p2);
    virtual QString GetNameMeasure();
};

class QMeasureList
{
private:
    QVector<ClusterMeasure *> measure;
    int CurrenIndex;

public:
    QMeasureList();
    int GetCountMeasure();
    ClusterMeasure *GetMeasureFromIndex(int index);
    ClusterMeasure *GetMeasure();
    int GetIndex();
    void SetIndex(int index);

};

// == Ã≈–€=====================================================================

class EuclideanMeasure : public ClusterMeasure
{
    Q_DECLARE_TR_FUNCTIONS(EuclideanMeasure)
public:
    float GetDistanceMeasure(QPoint p1, QPoint p2);
    QString GetNameMeasure();
};

class HemetMeasure : public ClusterMeasure
{
    Q_DECLARE_TR_FUNCTIONS(HemetMeasure)
public:
    float GetDistanceMeasure(QPoint p1, QPoint p2);
    QString GetNameMeasure();
};

class ChebyshevMeasure : public ClusterMeasure
{
    Q_DECLARE_TR_FUNCTIONS(ChebyshevMeasure)
public:
    float GetDistanceMeasure(QPoint p1, QPoint p2);
    QString GetNameMeasure();
};

class PeakDistanceMeasure : public ClusterMeasure
{
    Q_DECLARE_TR_FUNCTIONS(PeakDistanceMeasure)
public:
    float GetDistanceMeasure(QPoint p1, QPoint p2);
    QString GetNameMeasure();
};


#endif // CLUSTERMEASURE_H
