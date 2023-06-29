#include "vcolor.h"
#include <QDebug>
VColor::VColor(QObject *parent) :
    QObject(parent)
{
    ColorInit();
}

QColor VColor::GetNewColor()
{
    QColor ResColor;
    if (GetLCl(&LevelRed) == GetLCl(&LevelGreen)
            && GetLCl(&LevelRed) == GetLCl(&LevelBlue)
            && GetLCl(&LevelGreen) ==  GetLCl(&LevelBlue)) ChangeLevels();
    ResColor  = QColor(GetLCl(&LevelRed),GetLCl(&LevelGreen),GetLCl(&LevelBlue));
    ChangeLevels();
    return ResColor;
}

void VColor::ColorInit()
{
    LevelStep = 20;
    swColor = 0;
    LevelMax = 200;
    LevelMin = 0;
    LevelInit(&LevelRed);
    LevelInit(&LevelGreen);
    LevelInit(&LevelBlue);
}

void VColor::ColorInit(int count)
{
    ColorInit();
    int clc = (LevelMax - LevelMin);
    LevelStep = static_cast<quint8>(clc / (((clc ^ 3) / count / 3) ^ (1/3)));
}

void VColor::LevelInit(VColor::LevelColor *Level)
{
    Level->LevelHi = LevelMax;
    Level->LevelLow = LevelMin;
    Level->Trig = false;
}

quint8 VColor::GetLCl(VColor::LevelColor *Level)
{
    if (Level->Trig)
        return Level->LevelHi;
    else
        return Level->LevelLow;
}

void VColor::ChangeLevels()
{
    VColor::LevelColor *lv;
    lv = &LevelRed;
    switch (swColor)
    {
    case 0: lv = &LevelRed;  break;
    case 1: lv = &LevelGreen;  break;
    case 2: lv = &LevelBlue;  break;
    }

    if (lv->Trig)
    {
        lv->LevelHi = lv->LevelHi - LevelStep;
        if (lv->LevelHi < LevelMin) lv->LevelHi = LevelMax;
        if (lv->LevelHi > LevelMax) lv->LevelHi = LevelMax;
    }
    else
    {
        lv->LevelLow = lv->LevelLow + LevelStep;
        if (lv->LevelLow > LevelMax) lv->LevelLow = LevelMin;
    }
    lv->Trig = !(lv->Trig);
    swColor ++;
    if (swColor > 2) swColor = 0;

}

