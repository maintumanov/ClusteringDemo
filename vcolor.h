#ifndef VCOLOR_H
#define VCOLOR_H

#include <QObject>
#include <QColor>

class VColor : public QObject
{
    Q_OBJECT
    struct LevelColor {
      quint8 LevelHi;
      quint8 LevelLow;
      bool Trig;
    };

public:
    explicit VColor(QObject *parent = 0);
    QColor GetNewColor();
    
signals:
    
public slots:
    void ColorInit();
    void ColorInit(int count);

private:
    LevelColor LevelRed;
    LevelColor LevelGreen;
    LevelColor LevelBlue;
    quint8 LevelMax;
    quint8 LevelMin;
    quint8 LevelStep;
    quint8 swColor;

    void LevelInit(LevelColor *Level);
    quint8 GetLCl(LevelColor *Level);
    void ChangeLevels();

};

#endif // VCOLOR_H
