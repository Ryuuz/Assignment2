#include "physicsobject.h"
#include "transform.h"
#include <QKeyEvent>
#include <QDebug>


PhysicsObject::PhysicsObject(SceneObject *a, Shader *s, GLuint t, Texture *tex) : ObjectInstance(a, s, t, tex)
{
    mVelocity = QVector3D(0.f, 0.f, 0.f);
    mFriction = 0.97;
    mSpeed = 0.02f;
}


//Moves the object based on the velocity after taking friction into consideration
void PhysicsObject::physicsUpdate()
{
    //Not a very good way to add friction, but it will do for this program
    mVelocity = mVelocity*mFriction;

    if(mVelocity.length() < 0.002f)
    {
        mVelocity = QVector3D(0.f, 0.f, 0.f);
    }

    mTransform->translate(mVelocity.x(), mVelocity.y(), mVelocity.z());
}


//Sets velocity based on the pressed key
void PhysicsObject::setVelocity(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        mVelocity.setZ(-1.f);
    }
    else if(event->key() == Qt::Key_S)
    {
        mVelocity.setZ(1.f);
    }

    if(event->key() == Qt::Key_A)
    {
        mVelocity.setX(-1.f);
    }
    else if(event->key() == Qt::Key_D)
    {
        mVelocity.setX(1.f);
    }

    //Makes sure it doesn't go faster than 'mSpeed'
    if(mVelocity.length() > mSpeed*2)
    {
        mVelocity.normalize();
        mVelocity *= mSpeed;
    }

}


//Sets the velocity to be 'vel' and clamps the speed
void PhysicsObject::setVelocity(QVector3D vel)
{
    mVelocity = vel;

    if(mVelocity.length() > mSpeed*2)
    {
        mVelocity.normalize();
        mVelocity *= mSpeed;
    }
}
