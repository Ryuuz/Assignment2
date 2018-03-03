#include "boundingvolume.h"
#include "objectinstance.h"
#include <QVector4D>
#include <QMatrix4x4>


BoundingVolume::BoundingVolume(QVector3D a, QVector3D b, BoundType t, ObjectInstance *o) : mMax(a), mMin(b), mType(t), mOwner(o)
{

}


BoundingVolume::~BoundingVolume()
{
    mOwner = nullptr;
}


QVector3D BoundingVolume::getMax()
{
    QVector4D temp(mMax, 1.f);
    temp = (*mOwner->getModelMatrix()) * temp;

    return temp.toVector3D();
}


QVector3D BoundingVolume::getMin()
{
    QVector4D temp(mMin, 1.f);
    temp = (*mOwner->getModelMatrix()) * temp;

    return temp.toVector3D();
}
