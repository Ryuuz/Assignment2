#include "door.h"
#include "transform.h"
#include "sceneobject.h"
#include <QDebug>
#include <cmath>


Door::Door(SceneObject *a, Shader *s, GLuint t, Texture *tex) : PhysicsObject(a, s, t, tex), mSetup(false), mOpening(false), mAngle(0), mMaxAngle(90.f), mAngleStep(0.4f)
{

}


Door::~Door()
{

}


void Door::physicsUpdate()
{
    if(!mSetup)
    {
        findPositions();
        mSetup = true;
    }

    if(mOpening)
    {
        openDoor();
    }
    else
    {
        closeDoor();
    }

}


void Door::setDoorStatus()
{
    mOpening = !mOpening;
}


void Door::findPositions()
{
    mClosedPosition = mTransform->getTranslation();

    //Find out if it's horizontal or vertical
    if(std::abs(mBoundingObject->getMax().x() - mBoundingObject->getMin().x()) > std::abs(mBoundingObject->getMax().z() - mBoundingObject->getMin().z()))
    {
        mRadius = std::abs(mBoundingObject->getMax().x() - mBoundingObject->getMin().x()) / 2;
        float zMiddle = ((mBoundingObject->getMax().z() - mBoundingObject->getMin().z()) / 2);

        //Calculate the x and z for when the door is open
        mOpenPosition = mClosedPosition;
        mOpenPosition.setX((mOpenPosition.x() - mRadius) + zMiddle);
        mOpenPosition.setZ((mOpenPosition.z() - mRadius) + zMiddle);
    }
    else
    {
        mRadius = std::abs(mBoundingObject->getMax().z() - mBoundingObject->getMin().z()) / 2;
        float xMiddle = ((mBoundingObject->getMax().x() - mBoundingObject->getMin().x()) / 2);

        //Calculate the x and z for when the door is open
        mOpenPosition = mClosedPosition;
        mOpenPosition.setZ((mOpenPosition.z() + mRadius) - xMiddle);
        mOpenPosition.setX((mOpenPosition.x() + mRadius) - xMiddle);
    }

    //Number of steps before the rotation is done
    float steps = (mMaxAngle / mAngleStep);

    //The amount to translate for each step
    mPosition = (mOpenPosition - mClosedPosition)/steps;
}


void Door::openDoor()
{
    mAngle += mAngleStep;

    if(mAngle < 90.f)
    {
        mTransform->setRotation(0.f, mAngle, 0.f);
        mTransform->translate(mPosition.x(), mPosition.y(), mPosition.z());
    }
    else
    {
        //Make sure everything is ready for closing the door
        mAngle = mMaxAngle;

        mTransform->setRotation(0.f, mAngle, 0.f);
        mTransform->setPosition(mOpenPosition.x(), mOpenPosition.y(), mOpenPosition.z());
    }
}


void Door::closeDoor()
{
    mAngle -= mAngleStep;

    if(mAngle > 0.f)
    {
        mTransform->setRotation(0.f, mAngle, 0.f);
        mTransform->translate(-mPosition.x(), -mPosition.y(), -mPosition.z());
    }
    else
    {
        //Make sure everything is ready for opening the door
        mAngle = 0.f;

        mTransform->setRotation(0.f, mAngle, 0.f);
        mTransform->setPosition(mClosedPosition.x(), mClosedPosition.y(), mClosedPosition.z());
    }
}
