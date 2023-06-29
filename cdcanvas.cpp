#include "cdcanvas.h"


//=============================================================================

cdCanvas::cdCanvas(QWidget *parent) :
    QWidget(parent)
{
    PointNameIncrement = 0;
    MaxItemY = 200;
    MaxItemX = 300;
    PointRadius = 2;
    ReferencePoint = QPoint(0, 0);
    MeasuringDistance = false;
}

QMatrixClusters *cdCanvas::GetMatrixModel()
{
    return &matrix;
}

int cdCanvas::GetHolstWidht()
{
    return MaxItemX;
}

int cdCanvas::GetHolstHeight()
{
    return MaxItemY;
}

int cdCanvas::GetHolstPointR()
{
    return PointRadius;
}

void cdCanvas::SetHolstWitdht(int vol)
{
    MaxItemX = vol;
}

void cdCanvas::SetHolstHeight(int vol)
{
    MaxItemY = vol;
}

void cdCanvas::SetHolstPointR(int vol)
{
    PointRadius = vol;
}

QPoint cdCanvas::GetReferencePoint()
{
    return ReferencePoint;
}

void cdCanvas::AutoFill(int count)
{
    int rx, ry;
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    for(int i = 0; i < count; i ++)
    {
        rx = qrand()%(MaxItemX+1);
        ry = qrand()%(MaxItemY+1);
        MapPoints.append(new QCPoint(rx,ry,QString("P%1").arg(PointNameIncrement++)));
    }
    repaint();
}

void cdCanvas::paintEvent(QPaintEvent*)
{
    ChangeRatio();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    SetBackColore(&painter);
    DrawGrid(&painter);
    for (int i = 0; i < MapPoints.count(); i ++)
    {
        DrawPoint(&painter, MapPoints.at(i));
        DrawLink(&painter, MapPoints.at(i), MapPoints.at(i)->GetLinePoint());
    }
    DrawLineSize(&painter);

}

void cdCanvas::resizeEvent(QResizeEvent*)
{
    repaint();
}

void cdCanvas::SetBackColore(QPainter *p)
{
    p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    p->setPen(QPen(Qt::green, 0, Qt::SolidLine));
    p->drawRect(static_cast<int>(LeftSpacer), static_cast<int>(TopSpacer), static_cast<int>(ratio * MaxItemX - 1), static_cast<int>(ratio * MaxItemY - 1));
}

void cdCanvas::DrawPoint(QPainter *p,QCPoint *item)
{
    int rx, ry;

    rx = static_cast<int>(round(item->x() * ratio + LeftSpacer));
    ry = static_cast<int>(round(item->y() * ratio + TopSpacer));

    p->setPen(QPen(item->GetColor(), 1, Qt::SolidLine));
    p->setBrush(QBrush(item->GetColor(), Qt::SolidPattern));

    if (PointRadius == 1) p->drawPoint(rx,ry);
    else p->drawEllipse(QPoint(rx,ry),PointRadius,PointRadius);
}

void cdCanvas::DrawLink(QPainter *p, QAbstractCluster *point1, QAbstractCluster *point2)
{
    if (!EnabledLines) return;
    if (point2 == Q_NULLPTR) return;
  //  if (!point2->PDraw.GP->EnableLine) return;
    int rx1, ry1, rx2, ry2;

    rx1 = static_cast<int>(round(point1->x() * ratio + LeftSpacer));
    ry1 = static_cast<int>(round(point1->y() * ratio + TopSpacer));
    rx2 = static_cast<int>(round(point2->x() * ratio + LeftSpacer));
    ry2 = static_cast<int>(round(point2->y() * ratio + TopSpacer));

    p->drawLine(rx1,ry1,rx2,ry2);
}

void cdCanvas::DrawLineSize(QPainter *p)
{
    if (!MeasuringDistance) return;
    p->setPen(QPen(Qt::red, 4, Qt::SolidLine));
    p->drawLine(GetRealPoint(DestinationPoint),GetRealPoint(ReferencePoint));
}

void cdCanvas::DrawGrid(QPainter *p)
{
    if (!EnabledGrid) return;
    p->setPen(QPen(Qt::gray, 0, Qt::SolidLine));
    int rx1, ry1, rx2, ry2, cs;
    cs = static_cast<int>(round(round(10.0 / ratio) / 10) * 10);
    if (cs == 0) cs = 5;
    for (int i = 0; i < MaxItemY; i = i + cs)
    {
        rx1 = static_cast<int>(round(0 * ratio + LeftSpacer));
        ry1 = static_cast<int>(round(i * ratio + TopSpacer));
        rx2 = static_cast<int>(round(MaxItemX * ratio + LeftSpacer - 5));
        ry2 = static_cast<int>(round(i * ratio + TopSpacer));
        p->drawLine(rx1,ry1,rx2,ry2);
    }

    for (int i = 0; i < MaxItemX; i = i + cs)
    {
        rx1 = static_cast<int>(round(i * ratio + LeftSpacer));
        ry1 = static_cast<int>(round(0 * ratio + TopSpacer));
        rx2 = static_cast<int>(round(i * ratio + LeftSpacer));
        ry2 = static_cast<int>(round(MaxItemY * ratio + TopSpacer - 5));
        p->drawLine(rx1,ry1,rx2,ry2);
    }

    QString s = QString(tr("Cell %1x%1")).arg(cs);
    //.arg(matrix.GetDistanceMeasure()->GetDistanceMeasure(QPoint(1,1),QPoint(1,1+cs)));

    p->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    p->setPen(QPen(Qt::gray, 0, Qt::SolidLine));
    p->drawRect(static_cast<int>(LeftSpacer + 2), static_cast<int>(TopSpacer + ratio * MaxItemY - 5 - p->fontMetrics().height()),
                static_cast<int>(p->fontMetrics().width(s) + 5), static_cast<int>(2 + p->fontMetrics().height()));
    p->setPen(QPen(Qt::white, 0, Qt::SolidLine));
    p->drawText(static_cast<int>(LeftSpacer + 2), static_cast<int>(TopSpacer + ratio * MaxItemY - 6), s);

}

QPoint cdCanvas::GetRealPoint(QPoint point)
{
    return QPoint(static_cast<int>(round(point.x() * ratio + LeftSpacer)), static_cast<int>(round(point.y() * ratio + TopSpacer)));
}

void cdCanvas::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->x() < LeftSpacer
            || mouseEvent->x() > (qreal(MaxItemX) * ratio + LeftSpacer)
            || mouseEvent->y() < TopSpacer
            || mouseEvent->y() > (qreal(MaxItemY) * ratio + TopSpacer)) return;

    if ( mouseEvent->button() == Qt::LeftButton )
        NewPoint(static_cast<int>(round((mouseEvent->x() - LeftSpacer)/ratio)),
                 static_cast<int>(round((mouseEvent->y() - TopSpacer)/ratio)));

    if ( mouseEvent->button() == Qt::RightButton )
    {
        ReferencePoint = QPoint(static_cast<int>(round((mouseEvent->x() - LeftSpacer)/ratio)),
                                static_cast<int>(round((mouseEvent->y() - TopSpacer)/ratio)));
        DestinationPoint = ReferencePoint;
        ReferencePointChange(ReferencePoint);
        MeasuringDistance = true;
    }
}

void cdCanvas::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if ( mouseEvent->button() == Qt::RightButton )
    {
        MeasuringDistance = false;
        CursorNoDistance();
        repaint();
    }
}

void cdCanvas::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (!MeasuringDistance) return;
    DestinationPoint = QPoint(static_cast<int>(round((mouseEvent->x() - LeftSpacer)/ratio)),
                              static_cast<int>(round((mouseEvent->y() - TopSpacer)/ratio)));
    CursorChangeDistance(matrix.GetDistanceMeasure()->GetDistanceMeasure(ReferencePoint, DestinationPoint));
    repaint();

}

void cdCanvas::ChangeRatio()
{
    float ratioX = static_cast<float>(width())/static_cast<float>(MaxItemX);
    float ratioY = static_cast<float>(height())/static_cast<float>(MaxItemY);

    if (ratioX < ratioY) ratio = static_cast<qreal>(ratioX);
    else ratio = static_cast<qreal>(ratioY);
    TopSpacer = (height() - qreal(MaxItemY) * ratio) / 2;
    LeftSpacer = (width() - qreal(MaxItemX) * ratio) / 2;
    if ((TopSpacer) < 0) TopSpacer = 0;
    if ((LeftSpacer) < 0) LeftSpacer = 0;
}

void cdCanvas::NewPoint(int x, int y)
{
    QCPoint *point = new QCPoint(x,y,QString("P%1").arg(PointNameIncrement++));
    MapPoints.append(point);
    repaint();
}

void cdCanvas::StartClustering()
{
    MatrixInitial();
}

void cdCanvas::AutoClustering()
{
    matrix.AutoClustering(&MapPoints);
}

void cdCanvas::SetClusterMethod(ClisterMethod *clmethod)
{
    matrix.SetDistanceMetod(clmethod);
}

void cdCanvas::SetClusterMeasure(ClusterMeasure *clmeasure)
{
    matrix.SetDistanceMeasure(clmeasure);
}

void cdCanvas::MatrixInitial()
{
    matrix.IntMatrix(&MapPoints);
}

void cdCanvas::Clear()
{
    matrix.Clear();
    for (int i = 0; i < MapPoints.count(); i ++)
        delete MapPoints[i];
    MapPoints.clear();
    repaint();
}

void cdCanvas::SaveToFile(QFile *file)
{
    QDataStream stream(file);
    stream.setVersion(QDataStream::Qt_4_7);
    stream << QString("CLU");

    stream << MaxItemY;
    stream << MaxItemX;
    stream << PointRadius;
    stream << MapPoints.count();
    for (int i = 0; i < MapPoints.count(); i ++)
    {
        stream << MapPoints[i]->x();
        stream << MapPoints[i]->y();
    }
}

void cdCanvas::LoadFromFile(QFile *file)
{
    QDataStream stream(file);
    stream.setVersion(QDataStream::Qt_4_7);
    QString name;
    int x, y, count;

    stream >> name;
    if (name != QString("CLU")) return;
    Clear();

    stream >> MaxItemY;
    stream >> MaxItemX;
    stream >> PointRadius;
    stream >> count;
    PointNameIncrement = 0;
    for (int i = 0; i < count; i ++)
    {
        stream >> x;
        stream >> y;
        MapPoints.append(new QCPoint(x,y,QString("P%1").arg(PointNameIncrement++)));
    }
    repaint();
}

void cdCanvas::SaveSetting(QSettings *settings)
{
    settings->setValue(QLatin1String("MaxPointWidth"), MaxItemX);
    settings->setValue(QLatin1String("MaxPointHeight"), MaxItemY);
    settings->setValue(QLatin1String("PointRadius"), PointRadius);
}

void cdCanvas::LoadSetting(QSettings *settings)
{
    MaxItemX = settings->value(QLatin1String("MaxPointWidth"), 600).toInt();
    MaxItemY = settings->value(QLatin1String("MaxPointHeight"), 400).toInt();
    PointRadius = settings->value(QLatin1String("PointRadius"), 2).toInt();
}

void cdCanvas::SetEnableLines(bool en)
{
    EnabledLines = en;
    repaint();
}

void cdCanvas::SetEnableGrid(bool en)
{
    EnabledGrid = en;
    repaint();
}




