#ifndef CDDENDROGRAM_H
#define CDDENDROGRAM_H

#include <QWidget>
#include <QtGui>
#include "qmatrixclusters.h"
#include "vcolor.h"

class cdDendrogram : public QWidget
{
    Q_OBJECT
private:
    QMatrixClusters *cMatrix;
    QDrawParametrs DrawParametrs;
    int CutLevel;
    float CutLevelScale;
    bool EnablePaint;
    void PaintBackground(QPainter *p);
    void GetCanvasSize();
    void PaintLine(QPainter *p);
    void PaintCaption(QPainter *p);
    void SetCutLevel(int level);
    void SetClusterSelect(QAbstractCluster *cls);
    void Select(QPoint point);

    void StatisticClear();
    void PaintClusterInfo(QPainter *p);
    void RedrawDenragram();
    void BeginUpdate();
    void EndUpdate();
    void Reset();

public:
    explicit cdDendrogram(QMatrixClusters *matrix, QWidget *parent = 0);
    bool GetEnableLine();
    int GetLinkRatioInPercent();
    void SetEnableLine(bool enabled);
    void ApplyChanges();
    QString GetMethodName();
    
signals:
    void DendrogramUpdate();
    void PreSetScale(int);
    void PreSetRatio(int);

public slots:
    void ChangeDatagram(bool EnableView);
    void SaveSetting(QSettings *settings);
    void LoadSetting(QSettings *settings);
    void SetScale(int scale);
    void SetLinkRatio(int ratio);
    void ResetSelect();

protected:
    virtual void paintEvent(QPaintEvent* pe);
    void mousePressEvent( QMouseEvent *mouseEvent );
};

#endif // CDDENDROGRAM_H
