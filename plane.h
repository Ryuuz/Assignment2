#ifndef PLANE_H
#define PLANE_H

#include "sceneobject.h"
#include <QVector3D>

class Plane : public SceneObject
{
    public:
        Plane();
        ~Plane();

    private:
        void init() override;
};

#endif // PLANE_H
