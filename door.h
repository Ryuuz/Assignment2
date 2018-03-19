#ifndef DOOR_H
#define DOOR_H

#include "physicsobject.h"

class Door : public PhysicsObject
{
public:
    Door(SceneObject *a, Shader *s, GLuint t = 0, Texture *tex = nullptr);
    ~Door();

    void physicsUpdate() override;    
    void setDoorStatus();

private:
    void findPositions();
    void openDoor();
    void closeDoor();

    bool mSetup;
    bool mOpening;

    QVector3D mPosition;
    QVector3D mClosedPosition;
    QVector3D mOpenPosition;

    float mAngle;
    float mMaxAngle;
    float mAngleStep;

    float mRadius;
};

#endif // DOOR_H
