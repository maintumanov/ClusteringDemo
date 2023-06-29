#ifndef CDCANVAS_H
#define CDCANVAS_H

#include <QWidget>
#include <QtGui>
#include "vcolor.h"
#include "clistermethod.h"
#include "qcluster.h"
#include "qcpoint.h"
#include "qabstractcluster.h"
#include "qmatrixclusters.h"


class cdCanvas : public QWidget
{
    Q_OBJECT
private:
    bool EnabledLines;
    bool EnabledGrid;
    int MaxItemY;
    int MaxItemX;
    int PointRadius;
    qreal ratio,  ratioR;
    qreal TopSpacer, LeftSpacer;
    QVector<QCPoint *> MapPoints;
    VColor vcolor;
    QMatrixClusters matrix;
    int PointNameIncrement;
    QPoint ReferencePoint;
    QPoint DestinationPoint;
    bool MeasuringDistance;

    void SetBackColore(QPainter *p);
    void DrawPoint(QPainter *p,QCPoint *item);
    void DrawLink(QPainter *p, QAbstractCluster *point1, QAbstractCluster *point2);
    void DrawLineSize(QPainter *p);
    void DrawGrid(QPainter *p);
    void ChangeRatio();
    QPoint GetRealPoint(QPoint point);
    void NewPoint(int x, int y);


public:
    explicit cdCanvas(QWidget *parent = 0);
    QMatrixClusters *GetMatrixModel();
    int GetHolstWidht();
    int GetHolstHeight();
    int GetHolstPointR();
    void SetHolstWitdht(int vol);
    void SetHolstHeight(int vol);
    void SetHolstPointR(int vol);
    QPoint GetReferencePoint();
    void AutoFill(int count);

public slots:
    void StartClustering();
    void AutoClustering();
    void SetClusterMethod(ClisterMethod *clmethod);
    void SetClusterMeasure(ClusterMeasure *clmeasure);
    void MatrixInitial();
    void Clear();
    void SaveToFile(QFile *file);
    void LoadFromFile(QFile *file);
    void SaveSetting(QSettings *settings);
    void LoadSetting(QSettings *settings);
    void SetEnableLines(bool en);
    void SetEnableGrid(bool en);


protected:
    virtual void paintEvent(QPaintEvent* pe);
    virtual void resizeEvent(QResizeEvent *re);
    void mousePressEvent( QMouseEvent *mouseEvent );
    void mouseMoveEvent( QMouseEvent *mouseEvent );
    void mouseReleaseEvent( QMouseEvent *mouseEvent );

signals:
    void ReferencePointChange(QPoint RPoint);
    void CursorChangeDistance(float Distance);
    void CursorNoDistance();


public slots:

};

#endif // CDCANVAS_H
