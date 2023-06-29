#ifndef CLISTERMETHOD_H
#define CLISTERMETHOD_H

#include <QtCore>

class ClisterMethod
{
public:
    ClisterMethod();
    virtual float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    virtual QString GetNameMethod();
};

class QMethodsList
{
private:
    QVector<ClisterMethod *> methods;
    int CurrenIndex;

public:
    QMethodsList();
    int GetCountMethods();
    ClisterMethod *GetMethodFromIndex(int index);
    ClisterMethod *GetMethod();
    int GetIndex();
    void SetIndex(int index);

};

// == ÌÅÒÎÄÛ=====================================================================
//====================Áëèæ ñâÿçè==============

class NearestComMethod : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};

class MethodLongDistance : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};

class MethodMedian : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();

};

class MethodBetweenAcluster : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};

class MethodAverageIntra : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};

class MethodCentroid : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};

class MethodWard : public ClisterMethod
{
    Q_DECLARE_TR_FUNCTIONS(NearestComMethod)
public:
    float GetDistanceMethod(float d1, float d2, float dc, float c1, float c2);
    QString GetNameMethod();
};


#endif // CLISTERMETHOD_H
