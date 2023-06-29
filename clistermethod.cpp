#include "clistermethod.h"
#include <math.h>

ClisterMethod::ClisterMethod()
{
}

float ClisterMethod::GetDistanceMethod(float , float , float , float , float )
{
    return 1;
}

QString ClisterMethod::GetNameMethod()
{
    return QString("name");
}

//========================================


QMethodsList::QMethodsList()
{
    CurrenIndex = 0;
    methods.append(new NearestComMethod());
    methods.append(new MethodLongDistance());
    methods.append(new MethodMedian());
    methods.append(new MethodBetweenAcluster());
    methods.append(new MethodAverageIntra());
    methods.append(new MethodCentroid());
    methods.append(new MethodWard());


}

int QMethodsList::GetCountMethods()
{
    return methods.count();
}

ClisterMethod *QMethodsList::GetMethodFromIndex(int index)
{
    return methods[index];
}

ClisterMethod *QMethodsList::GetMethod()
{
    return methods[CurrenIndex];
}

int QMethodsList::GetIndex()
{
    return CurrenIndex;
}

void QMethodsList::SetIndex(int index)
{
   CurrenIndex = index;
}

// == лерндш=====================================================================

float NearestComMethod::GetDistanceMethod(float d1, float d2, float , float , float )
{ 
    return static_cast<float>(0.5 * static_cast<double>(d1) + 0.5 * static_cast<double>(d2) - 0.5 * abs(static_cast<int>(d1 - d2)));
}

QString NearestComMethod::GetNameMethod()
{
    return tr("The method of near field communication");
}

//===========================================================================
float MethodLongDistance::GetDistanceMethod(float d1, float d2, float , float , float )
{
    return static_cast<float>(0.5 * static_cast<double>(d1) + 0.5 * static_cast<double>(d2) + 0.5 * abs(static_cast<int>(d1 - d2)));
}

QString MethodLongDistance::GetNameMethod()
{
    return tr("The method of long-distance communication");
}

//===========================================================================
float MethodMedian::GetDistanceMethod(float d1, float d2, float dc, float , float )
{
    return static_cast<float>(0.5 * static_cast<double>(d1) + 0.5 * static_cast<double>(d2) + 0.25 * static_cast<double>(dc));
}

QString MethodMedian::GetNameMethod()
{
    return tr("Median method");
}

//===========================================================================
float MethodBetweenAcluster::GetDistanceMethod(float d1, float d2, float , float , float )
{
    return static_cast<float>(0.5 * static_cast<double>(d1) + 0.5 * static_cast<double>(d2));
}

QString MethodBetweenAcluster::GetNameMethod()
{
    return tr("Mean between clusters method");
}

//===========================================================================
float MethodAverageIntra::GetDistanceMethod(float d1, float d2, float , float c1, float c2)
{
    return c1 / (c1 + c2) * d1 + c2 / (c1 + c2) * d2;
}

QString MethodAverageIntra::GetNameMethod()
{
    return tr("Intra-group average method");
}

//===========================================================================
float MethodCentroid::GetDistanceMethod(float d1, float d2, float dc, float c1, float c2)
{
    return static_cast<float>(abs(static_cast<int>(c1 / (c1 + c2) * d1 + c2 / (c1 + c2) * d2 - c1 * c2 / (c1 +c2) * dc)));
}

QString MethodCentroid::GetNameMethod()
{
    return tr("Centroid method");
}

//===========================================================================
float MethodWard::GetDistanceMethod(float d1, float d2, float dc, float c1, float c2)
{
    return (c1 + c2 + c1) / (2 * (c1 + c2)) * d1 +
            (c1 + c2 + c2) / (2 * (c1 + c2)) * d2 -
            (c1 + c2) / (2 * (c1 + c2)) * dc;
}

QString MethodWard::GetNameMethod()
{
    return tr("Ward's Method");
}

