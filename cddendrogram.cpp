#include "cddendrogram.h"

cdDendrogram::cdDendrogram(QMatrixClusters *matrix, QWidget *parent) :
    QWidget(parent)
{
    cMatrix = matrix;
    CutLevel = 0;
    EnablePaint = true;
    DrawParametrs.CanvasHeight = 100.0;
    DrawParametrs.CanvasWidth = 100.0;
    DrawParametrs.ClusterHeight = 8.0;
    DrawParametrs.ClusterWidtht = 8.0;
    DrawParametrs.PointHeight = 8.0;
    DrawParametrs.PointWidtht = 8.0;
    DrawParametrs.SpaceHeight = 10.0;
    DrawParametrs.SpaceWidtht = 6.0;
    DrawParametrs.LinkRatio = 1.0;
    DrawParametrs.LinkScale = 1.0;
    DrawParametrs.EnableLine = true;
    DrawParametrs.DMode = 0;
    setVisible(false);
    QObject::connect(cMatrix, SIGNAL(ChangeDatagram(bool)), this, SLOT(ChangeDatagram(bool)));

}

bool cdDendrogram::GetEnableLine()
{
    return DrawParametrs.EnableLine;
}

int cdDendrogram::GetLinkRatioInPercent()
{
    return static_cast<int>(DrawParametrs.LinkRatio * 100);
}

void cdDendrogram::SetEnableLine(bool enabled)
{
    DrawParametrs.EnableLine = enabled;
}


void cdDendrogram::RedrawDenragram()
{
    GetCanvasSize();
    this->setMinimumWidth(static_cast<int>(DrawParametrs.CanvasWidth));
    this->setMinimumHeight(static_cast<int>(DrawParametrs.CanvasHeight));
    EndUpdate();
}

void cdDendrogram::BeginUpdate()
{
    EnablePaint = false;
}

void cdDendrogram::EndUpdate()
{
    EnablePaint = true;
    repaint();
}

void cdDendrogram::Reset()
{
    DrawParametrs.DMode = 0;
    StatisticClear();
    if (DrawParametrs.EnableLine) cMatrix->GetRootCluster()->ClearLinePoint();
    cMatrix->GetRootCluster()->SetClusterColor(Qt::black);
    DendrogramUpdate();
}

QString cdDendrogram::GetMethodName()
{
    return cMatrix->GetDistanceMethod()->GetNameMethod();
}

void cdDendrogram::SetScale(int scale)
{
    BeginUpdate();
    Reset();
    DrawParametrs.ClusterHeight = static_cast<float>(8.0 / 100.0 * scale);
    DrawParametrs.ClusterWidtht = static_cast<float>(8.0 / 100.0 * scale);
    DrawParametrs.PointHeight = static_cast<float>(8.0 / 100.0 * scale);
    DrawParametrs.PointWidtht = static_cast<float>(8.0 / 100.0 * scale);
    DrawParametrs.SpaceHeight = static_cast<float>(10.0 / 100.0 * scale);
    DrawParametrs.SpaceWidtht = static_cast<float>(6.0 / 100.0 * scale);
    DrawParametrs.LinkScale = static_cast<float>(1.0 / 100.0 * scale);
    CutLevelScale = static_cast<float>(1.0 / 100.0 * scale);
    GetCanvasSize();
    this->setMinimumWidth(static_cast<int>(DrawParametrs.CanvasWidth));
    this->setMinimumHeight(static_cast<int>(DrawParametrs.CanvasHeight));
    EndUpdate();
}

void cdDendrogram::SetLinkRatio(int ratio)
{
    BeginUpdate();
    Reset();
    DrawParametrs.LinkRatio = static_cast<float>(1.0 / 100.0 * ratio);
    GetCanvasSize();
    this->setMinimumWidth(static_cast<int>(DrawParametrs.CanvasWidth));
    this->setMinimumHeight(static_cast<int>(DrawParametrs.CanvasHeight));
    EndUpdate();
}

void cdDendrogram::ApplyChanges()
{
    BeginUpdate();
    GetCanvasSize();
    EndUpdate();
}

void cdDendrogram::ChangeDatagram(bool EnableView)
{
    if (EnableView) {
        BeginUpdate();
        GetCanvasSize();

        this->setMinimumWidth(static_cast<int>(round(static_cast<double>(DrawParametrs.CanvasWidth))));
        this->setMinimumHeight(static_cast<int>(round(static_cast<double>(DrawParametrs.CanvasHeight))));
        this->setVisible(true);
        Reset();
        PreSetRatio(static_cast<int>(DrawParametrs.LinkRatio * 100));
        EndUpdate();
    }
    else
    {
        setVisible(false);
        DendrogramUpdate();
    }
}

void cdDendrogram::paintEvent(QPaintEvent *)
{
    if (!EnablePaint) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    DrawParametrs.painter = &painter;
    if (DrawParametrs.CanvasHeight < height() - 2) DrawParametrs.CanvasTop = (height() - DrawParametrs.CanvasHeight) / 2;
    else DrawParametrs.CanvasTop = 0;
    if (DrawParametrs.CanvasWidth < width() - 2) DrawParametrs.CanvasLeft = (width() - DrawParametrs.CanvasWidth) / 2;
    else DrawParametrs.CanvasLeft = 0;

    //=========
    GetCanvasSize();

    PaintBackground(&painter);
    if (cMatrix->GetRootCluster() == Q_NULLPTR) return;
    cMatrix->GetRootCluster()->DenPaint(&DrawParametrs, 0, 0);
    // PaintCaption(&painter);
    PaintLine(&painter);
    PaintClusterInfo(&painter);
}

void cdDendrogram::PaintClusterInfo(QPainter *p)
{
    if (DrawParametrs.DMode != 2) return;
    p->setPen(QPen(Qt::blue, 0, Qt::SolidLine));
    p->drawText(DrawParametrs.ClusterInfoPoint.x(), DrawParametrs.ClusterInfoPoint.y() - 2,
                QString(tr("Dist: %1"))
                .arg(static_cast<double>(DrawParametrs.ClusterDistance)));
    p->drawText(DrawParametrs.ClusterInfoPoint.x(), DrawParametrs.ClusterInfoPoint.y() - p->fontMetrics().height(),
                QString(tr("Points: %1"))
                .arg(DrawParametrs.StatPointsCount));
}

void cdDendrogram::PaintBackground(QPainter *p)
{
    p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    p->setPen(QPen(Qt::white, 0, Qt::SolidLine));
    p->drawRect(0,0,width()- 1,height()- 1);
}

void cdDendrogram::PaintLine(QPainter *p)
{
    if (DrawParametrs.DMode != 1) return;
    p->setPen(QPen(Qt::red, 2, Qt::DashLine));
    p->drawText(2, static_cast<int>(DrawParametrs.CanvasTop + CutLevel - 4), QString(tr("Clusters: %1, Points: %2"))
                .arg(DrawParametrs.StatClustersCount)
                .arg(DrawParametrs.StatPointsCount));
    p->drawLine(2, static_cast<int>(DrawParametrs.CanvasTop + CutLevel), width() - 3, static_cast<int>(DrawParametrs.CanvasTop + CutLevel));
}

void cdDendrogram::PaintCaption(QPainter *p)
{
    p->setPen(QPen(Qt::blue, 0, Qt::SolidLine));
    p->drawText(2, p->fontMetrics().height(), cMatrix->GetDistanceMethod()->GetNameMethod());
}

void cdDendrogram::SetCutLevel(int level)
{
    BeginUpdate();
    if (level > DrawParametrs.CanvasHeight + DrawParametrs.CanvasTop) return;
    if (level < DrawParametrs.CanvasTop) return;
    DrawParametrs.DMode = 1;
    StatisticClear();
    CutLevel = static_cast<int>(level - DrawParametrs.CanvasTop);
    VColor vcolor;
    //vcolor.ColorInit(30);
    if (DrawParametrs.EnableLine) cMatrix->GetRootCluster()->ClearLinePoint();
    cMatrix->GetRootCluster()->SetCutClusterColor(level, &vcolor, QColor(230,230,230));
    DendrogramUpdate();
    EndUpdate();
}

void cdDendrogram::SetClusterSelect(QAbstractCluster *cls)
{
    BeginUpdate();
    DrawParametrs.DMode = 2;
    StatisticClear();
    cMatrix->GetRootCluster()->SetClusterColor(QColor(210,210,210));
    if (DrawParametrs.EnableLine) cMatrix->GetRootCluster()->ClearLinePoint();
    cls->SetClusterColor(Qt::blue);
    cls->SetEnableCaption();
    if (DrawParametrs.EnableLine) cls->LineClustering();
    DendrogramUpdate();
    EndUpdate();
}

void cdDendrogram::Select(QPoint point)
{
    QAbstractCluster *cls = cMatrix->GetClusterFromPoint(point);
    if (cls == Q_NULLPTR)  SetCutLevel(point.y());
    else
        SetClusterSelect(cls);
}

void cdDendrogram::ResetSelect()
{
    BeginUpdate();
    Reset();
    EndUpdate();
}

void cdDendrogram::StatisticClear()
{
    DrawParametrs.StatClustersCount = 0;
    DrawParametrs.StatPointsCount = 0;
    DrawParametrs.StatClustersDistants = 0;
}

void cdDendrogram::SaveSetting(QSettings *settings)
{
    settings->setValue(QLatin1String("LinkRatio"), DrawParametrs.LinkRatio);
}

void cdDendrogram::LoadSetting(QSettings *settings)
{
    DrawParametrs.LinkRatio = settings->value(QLatin1String("LinkRatio"), 1).toFloat();
}

void cdDendrogram::mousePressEvent(QMouseEvent *mouseEvent)
{
    if ( mouseEvent->button() == Qt::LeftButton )
        Select(QPoint(mouseEvent->x(), mouseEvent->y()));
    if ( mouseEvent->button() == Qt::RightButton ) ResetSelect();
}

void cdDendrogram::GetCanvasSize()
{
    if (cMatrix->GetRootCluster() == Q_NULLPTR) return;
    DrawParametrs.CanvasHeight = cMatrix->GetRootCluster()->GetMaxHeight(&DrawParametrs, 0) +
            DrawParametrs.SpaceHeight;
    DrawParametrs.CanvasWidth = static_cast<float>(cMatrix->GetRootCluster()->GetPointCount() *
            (DrawParametrs.PointWidtht + DrawParametrs.SpaceWidtht));
}
