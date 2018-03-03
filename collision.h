#ifndef COLLISION_H
#define COLLISION_H

class BoundingVolume;
class ObjectInstance;
class PhysicsObject;
class QVector3D;

class Collision
{
    public:
        Collision();
        ~Collision();

        bool collisionDetection(BoundingVolume *obj1, BoundingVolume *obj2, QVector3D vel);
        void collisionHandling(PhysicsObject *obj1);
        void collisionHandling(PhysicsObject *obj1, PhysicsObject *obj2);

    private:

};

#endif // COLLISION_H
