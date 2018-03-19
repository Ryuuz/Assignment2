#include "ball.h"
#include "transform.h"


Ball::Ball(SceneObject *a, Shader *s, GLuint t, Texture *tex) : PhysicsObject(a, s, t, tex)
{

}


Ball::~Ball()
{

}


void Ball::physicsUpdate()
{
    PhysicsObject::physicsUpdate();

    //Rotation to make it seem like the ball is rolling
    //Angle = length of velocity / radius of the ball
    float angle = mVelocity.length() / ((mBoundingObject->getMax() - mBoundingObject->getMin()).length()/2);
    angle *= (180.f/3.14f);

    QVector3D rot(0.f, 0.f, 0.f);

    //The direction the ball is moving in
    if(mVelocity.x() > 0.f)
    {
        rot.setX(-1.f);
    }
    else if(mVelocity.x() < 0.f)
    {
        rot.setX(1.f);
    }
    if(mVelocity.z() > 0.f)
    {
        rot.setZ(1.f);
    }
    else if(mVelocity.z() < 0.f)
    {
        rot.setZ(-1.f);
    }

    rot = rot*angle;

    //Rotate around x for movement in z direction and vice versa
    mTransform->rotate(rot.z(), rot.y(), rot.x());
}
