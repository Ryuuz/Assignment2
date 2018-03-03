#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "objectinstance.h"
#include <QVector3D>

class QKeyEvent;

class PhysicsObject : public ObjectInstance
{
    public:
        PhysicsObject(SceneObject *a, Shader *s);
        void physicsUpdate();
        void setVelocity(QKeyEvent *event);
        void setVelocity(QVector3D vel);
        QVector3D getVelocity() {return mVelocity;}

    private:
        QVector3D mVelocity;
        float mFriction;
        float mSpeed;
};

#endif // PHYSICSOBJECT_H
