#include "collision.h"
#include "boundingvolume.h"
#include "objectinstance.h"
#include "physicsobject.h"
#include <QVector3D>
#include <QDebug>


Collision::Collision()
{

}


Collision::~Collision()
{

}


//One dynamic object and one static
bool Collision::collisionDetection(BoundingVolume *obj1, BoundingVolume *obj2, QVector3D vel)
{
    //If sphere vs box
    if(obj1->getType() == BoundType::sphere && (obj2->getType() == BoundType::box || obj2->getType() == BoundType::trigger))
    {
        //Center and radius of sphere
        QVector3D sphereCenter = ((obj1->getMax() + obj1->getMin()) / 2.f);
        float sphereRadius = (obj1->getMax() - sphereCenter).length();

        //Point on sphere closest to the the box
        QVector3D collisionPoint = sphereCenter + (vel.normalized() * sphereRadius);

        //http://www.miguelcasillas.com/?p=24
        if(collisionPoint.x() > obj2->getMin().x() && collisionPoint.x() < obj2->getMax().x()
           && collisionPoint.y() > obj2->getMin().y() && collisionPoint.y() < obj2->getMax().y()
           && collisionPoint.z() > obj2->getMin().z() && collisionPoint.z() < obj2->getMax().z())
        {
            return true;
        }
    }
    else if(obj1->getType() == BoundType::sphere && obj2->getType() == BoundType::sphere)
    {
        QVector3D sphereCenter1 = ((obj1->getMax() + obj1->getMin()) / 2.f);
        float sphereRadius1 = (obj1->getMax() - sphereCenter1).length();

        QVector3D sphereCenter2 = ((obj2->getMax() + obj2->getMin()) / 2.f);
        float sphereRadius2 = (obj2->getMax() - sphereCenter2).length();

        if((sphereCenter2 - sphereCenter1).length() <= (sphereRadius1 + sphereRadius2))
        {
            return true;
        }
    }

    return false;
}


void Collision::collisionHandling(PhysicsObject *obj1)
{
    QVector3D vel = obj1->getVelocity();
    obj1->setVelocity(vel*(-0.5f));
}


void Collision::collisionHandling(PhysicsObject *obj1, PhysicsObject *obj2)
{
    QVector3D vel = obj1->getVelocity();
    obj1->setVelocity(obj2->getVelocity());
    obj2->setVelocity(vel);

}
